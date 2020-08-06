//
// Antes llamadoa "Text.txt"
// Aparente implementación de Convolutional Neural Networks (CNNs / ConvNets)
// Applying Transfer Learning on Dogs vs Cats Dataset (ResNet18) using PyTorch C++ API
// https://cs231n.github.io/convolutional-networks/
// https://cs231n.github.io/transfer-learning/
// https://krshrimali.github.io/Applying-Transfer-Learning-Dogs-Cats/
//

constexpr int IN_CHANNEL = 1;
constexpr int OUT_CHANNEL = 1;
constexpr int KERNEL3_3 = 3;
constexpr int LAYERS = 3;

auto BBB = nn::MaxPool2d(
	nn::MaxPool2dOptions(2)
	.stride(2)
);//B->forward_with_indices(IN_1);

auto C = nn::Conv2d(
	nn::Conv2dOptions(1, 1, 3)
	.stride(1)
	.padding(1)
	.bias(false)
);

auto D = nn::Upsample(
	nn::UpsampleOptions()
	.size(std::vector<int64_t>({ 2 }, { 4 }))
	//.scale_factor(std::vector<double>({ 2 }, { 3 }))
	//.mode(torch::kNearest)
	//.align_corners(false)
);

auto E = nn::MaxUnpool2d(
	nn::MaxUnpool2dOptions(2).stride(2)
);

auto C3 = torch::nn::Sequential(
	nn::MaxPool2d(nn::MaxPool2dOptions(2).stride(2))
);

torch::Device device(torch::cuda::is_available() ? torch::kCUDA : torch::kCPU);

torch::nn::Conv2dOptions conv_options(int64_t in_planes, int64_t out_planes, int64_t kerner_size,
	int64_t stride = 1, int64_t padding = 1, int64_t groups = 1, bool with_bias = false) {
	return (
		torch::nn::Conv2dOptions(in_planes, out_planes, kerner_size)
		.stride(stride)
		.padding(padding)
		.groups(groups)
		.bias(with_bias)
		);
}

torch::nn::BatchNormOptions bn_options(int64_t features) {
	return (torch::nn::BatchNormOptions(features).affine(true).track_running_stats(true));
}

auto BN_ReLU_Conv(const size_t& CHANNEL_IN, const size_t& CHANNEL_OUT, const size_t& KERNEL, const float& DROPOUT = 0.0f) {
	if (DROPOUT > 0.0f)
		return torch::nn::Sequential(
			torch::nn::BatchNorm2d(CHANNEL_IN),
			torch::nn::Functional(torch::relu),
			torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_IN, CHANNEL_OUT, KERNEL).padding(1).bias(true)),
			torch::nn::Dropout(DROPOUT)
		);
	return torch::nn::Sequential(
		torch::nn::BatchNorm2d(CHANNEL_IN),
		torch::nn::Functional(torch::relu),
		torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_IN, CHANNEL_OUT, KERNEL).padding(1).bias(true))
	);
};

auto Transition_Down(const size_t& CHANNEL_IN, const size_t& CHANNEL__OUT, const float& DROPOUT = 0) {
	torch::nn::Sequential RET = BN_ReLU_Conv(CHANNEL_IN, CHANNEL__OUT, 1 /*KERNEL_SIZE*/, DROPOUT);
	RET->push_back(torch::nn::MaxPool2d(2));
	return RET;
};
auto Transition_Up() {
	return
		nn::ConvTranspose2d(
			nn::ConvTranspose2dOptions(1, 1, 2)
			.stride(2)
			.padding(0)
			.bias(false));
};

auto FF = torch::nn::Sequential(
	nn::AvgPool2d(2)
);

const size_t BACH_SIZE = 32;
const size_t DATASIZE = 25000;
const size_t DATASIZE_TEST = 1000;
const size_t HEIGTH = 224;
const size_t WIDTH = 224;
const size_t CHANNEL = 3;

torch::nn::Sequential MODEL(
	// Layer 1
	torch::nn::Conv2d(torch::nn::Conv2dOptions(3 /*channel_in */, 32 /*channel_out */, 3 /*kernel_size=*/)),
	//torch::nn::BatchNorm2d(32),
	torch::nn::MaxPool2d(2),
	torch::nn::Functional(torch::relu),
	// Layer 2
	torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3)),
	//torch::nn::BatchNorm2d(32),
	torch::nn::MaxPool2d(2),
	torch::nn::Functional(torch::relu),
	// Layer 3
	torch::nn::Conv2d(torch::nn::Conv2dOptions(32, 32, 3)),
	torch::nn::Dropout(0.5),
	torch::nn::BatchNorm2d(32),
	torch::nn::MaxPool2d(2),
	torch::nn::Functional(torch::relu),
	// Layer 4
	torch::nn::Flatten(),
	torch::nn::Linear(torch::nn::LinearOptions(1152, 100)),
	torch::nn::Functional(torch::relu),
	// Layer 6
	torch::nn::Linear(torch::nn::LinearOptions(100, 2)),
	torch::nn::LogSoftmax(1)
);

template <typename DataLoader>
void test(DataLoader& data_loader, size_t dataset_size) {
	MODEL->eval();

	float Acc = 0.0;
	int64_t correct = 0;
	for (auto& batch : *data_loader) {
		auto data = batch.data;
		auto target = batch.target.squeeze();

		// Should be of length: batch_size
		data = data.to(torch::kFloat).div_(255);
		target = target.to(torch::kInt64);

		auto output = MODEL->forward(data);

		Acc += output.argmax(1).eq(target).sum().template item<float>();
	}

	std::cout << "TEST Accuracy: " << Acc / (float)dataset_size << std::endl;
};

template <typename DataLoader>
void train(torch::jit::script::Module net, torch::nn::Linear lin, DataLoader& data_loader, torch::optim::Optimizer& optimizer, size_t dataset_size, int epoch) {
	/*
	Parameters
	 ==================
	 torch::jit::script::Module net: Pre-trained model
	 torch::nn::Linear lin: Linear layer
	 DataLoader& data_loader: Training data loader
	 torch::optim::Optimizer& optimizer: Optimizer like Adam, SGD etc.
	 size_t dataset_size: Size of training dataset
	 */

	float mse = 0;
	float Acc = 0.0;
	size_t batch_idx = 0;

	for (auto& batch : *data_loader) {
		auto data = batch.data;
		auto target = batch.target.squeeze();

		// Should be of length: batch_size
		data = data.to(torch::kFloat).div_(255);
		target = target.to(torch::kInt64);

		std::vector<torch::jit::IValue> input;
		input.push_back(data);

		optimizer.zero_grad();
			auto output = net.forward(input).toTensor();
			// For transfer learning
			output = output.view({ output.size(0), -1 });

			output = lin(output);
			// Explicitly calculate torch::log_softmax of output from the FC Layer
			auto loss = torch::nll_loss(torch::log_softmax(output, 1), target);

			loss.backward();
		optimizer.step();

		auto acc = output.argmax(1).eq(target).sum();

		Acc += acc.template item<float>();
		mse += loss.template item<float>();

		std::printf("\rTrain Epoch: %ld [%5ld/%5ld] Loss: %.4f ", epoch, batch_idx++ * BACH_SIZE, DATASIZE_TEST, loss.template item<float>());
	}

	mse = mse / float(BACH_SIZE); // Take mean of loss
	std::cout << "Epoch: " << epoch << ", " << "Accuracy: " << Acc / dataset_size << ", " << "MSE: " << mse << std::endl;
	net.save("model_resnet18.pt");
}

int main()
{
	//---------------------------------------------------------------------------------------------------------------------------------------
	// TRAIN
	//---------------------------------------------------------------------------------------------------------------------------------------
	std::pair<std::vector<std::string>, std::vector<size_t>> pair_images_labels = load_data_from_folder("C:\\Repositories\\CatsAndDogs_TEST");

	auto custom_dataset = CustomDataset(pair_images_labels.first, pair_images_labels.second).map(torch::data::transforms::Stack<>());

	auto data_loader = torch::data::make_data_loader<torch::data::samplers::RandomSampler>(
		std::move(custom_dataset),
		torch::data::DataLoaderOptions().batch_size(BACH_SIZE).workers(2));

	////---------------------------------------------------------------------------------------------------------------------------------------
	//// TEST
	////---------------------------------------------------------------------------------------------------------------------------------------
	//std::pair<std::vector<std::string>, std::vector<size_t>> images_test = load_data_from_folder("C:\\Repositories\\CatsAndDogs_TEST");
	//
	//auto dataset_test = CustomDataset(images_test.first, images_test.second).map(torch::data::transforms::Stack<>());
	//
	//auto data_test = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
	//	std::move(dataset_test),
	//	torch::data::DataLoaderOptions().batch_size(BACH_SIZE).workers(2));

	//torch::optim::Adam optimizer(MODEL->parameters(), torch::optim::AdamOptions(1e-3));
	//size_t N_EPOCH_TO_TRAIN = 100;
	//for (int epoch = 0;; epoch++)
	//{
	//	test(data_test, DATASIZE_TEST);
	//	train(data_loader, optimizer, DATASIZE, epoch);
	//};

	torch::jit::script::Module module;
	module = torch::jit::load("C:\\Repositories\\resnet18_without_last_layer.pt");

	///* We need to convert last layer input and output features from (512, 1000) to (512, 2) since we only have 2 classes */
	torch::nn::Linear linear_layer(512, 2);

	//// Define the optimizer on parameters of linear_layer with learning_rate = 1e-3
	torch::optim::Adam optimizer(linear_layer->parameters(), torch::optim::AdamOptions(1e-3));

	//size_t N_EPOCH_TO_TRAIN = 100;
	//for (int epoch = 0;; epoch++)
	//{
	//	train(module, linear_layer, data_loader, optimizer, DATASIZE_TEST, epoch);
	//};

	custom_dataset.
};

template<typename Net>
std::ostream& operator<< (std::ostream& stream, const TiramisuImpl& NET) {
	operator<<(stream, (torch::nn::Module) NET) << endl;

	size_t total_parameters = 0;
	for (auto IDX : NET->named_parameters()) {
		total_parameters += IDX.value().numel();
		stream << IDX.key() << "   " << IDX.value().numel() << endl;
	};
	stream << "Total Parameters: " << total_parameters << endl;

	return stream;
};

at::Tensor Soft_Dice0(const at::Tensor _PREDICTED, const at::Tensor _TARGET) {
	auto intersection = 2 * (_PREDICTED * _TARGET).sum();
	auto sum = (_PREDICTED + _TARGET ).sum();

	return  (intersection + 0.01f) / (sum + 0.01f);
};

at::Tensor Soft_Dice(const at::Tensor _PREDICTED, const at::Tensor _TARGET) {
	auto intersection = 2*(_PREDICTED * _TARGET).sum();
	auto sum = (_PREDICTED*_PREDICTED + _TARGET* _TARGET).sum();

	//float INTER = intersection.template item<float>();
	//float SUM = sum.template item<float>();

	return  (intersection + 0.01f) / (sum + 0.01f);
};

at::Tensor Jaccard(const at::Tensor _PREDICTED, const at::Tensor _TARGET) {
	auto intersection = (_PREDICTED * _TARGET).sum();
	auto sum = (_PREDICTED + _TARGET).sum();
	//
	//float INTER = intersection.template item<float>();
	//float SUM = sum.template item<float>();
	//
	//cout << "INTER " << INTER << endl;
	//cout << "SUM " << SUM << endl;

	//return (_PREDICTED * _TARGET).sum().to(torch::kFloat) / (_PREDICTED + _TARGET).sum().to(torch::kFloat);
	return  (intersection + 0.01f) / (sum - intersection + 0.01f);
};


cv::Mat show_test_result(const at::Tensor& _IN, const at::Tensor& _OUT, const at::Tensor& _TARGET) {
	cv::Mat __IN(image_size * test_batch_size, image_size, CV_8UC1, (void*)_IN.data_ptr());
	cv::Mat __OUT(image_size * test_batch_size, image_size, CV_8UC1, (void*)_OUT.data_ptr());
	cv::Mat __TARGET(image_size * test_batch_size, image_size, CV_8UC1, (void*)_TARGET.data_ptr());

	cv::Mat DST = cv::Mat(image_size * test_batch_size, 3 * image_size, CV_8UC1);

	auto count = 0;
	__IN.copyTo(DST(cv::Rect(count, 0, image_size, image_size * test_batch_size))); count += image_size;
	__OUT.copyTo(DST(cv::Rect(count, 0, image_size, image_size * test_batch_size))); count += image_size;
	__TARGET.copyTo(DST(cv::Rect(count, 0, image_size, image_size * test_batch_size)));

	return DST;
}
