#include "pch.h"
#include "Config.h"
#include "CementDataset.h"
#include "Tiramisu.h"
#include "Visualize.h"
#include "Serialize.h"

template <typename DataLoader, typename Net>
void train_batch(size_t EPOCH, Net& MODEL, DataLoader& DATA_LOADER, torch::optim::Optimizer& optimizer, size_t SIZE) {
	MODEL->train();
	size_t batch_idx = 0;
	float __loss 	 = 0;

	for (auto& batch : DATA_LOADER) {
		optimizer.zero_grad();

		auto _IN = batch.data.to(at::kFloat) / 255.0f;
		auto _OUT = batch.target.to(at::kFloat) / 255.0f;
		auto _TARGET = MODEL->forward(_IN);

		auto total_loss = /*1- Soft_Dice(_TARGET, _OUT);*/ torch::binary_cross_entropy(_TARGET, _OUT);
		__loss += total_loss.template item<float>();
	
		total_loss.backward();
		optimizer.step();

		std::printf("\rTrain Epoch: %ld [%5ld/%5ld] ", EPOCH, batch_idx++ * train_batch_size, SIZE);
	}
	std::printf(" Loss: %.4f ", __loss / (SIZE / train_batch_size));
};

template <typename DataLoader, typename Net>
void test_batch(Net& MODEL, DataLoader& DATA_LOADER, size_t SIZE) {
	MODEL->eval();
	float __loss = 0;

	for (const auto& batch : DATA_LOADER) {
		auto _IN = batch.data.to(at::kFloat) / 255.0f;
		auto _OUT = batch.target.to(at::kFloat) / 255.0f;
		auto _TARGET = MODEL->forward(_IN);

		__loss += torch::binary_cross_entropy(_TARGET, _OUT).template item<float>();

		//auto _DST = show_test_result(batch.data, batch.target, (_TARGET * 255.0f).to(at::kByte));
	};
	std::printf(" TESTING. Loss: %.4f \r\n", __loss/ (SIZE / test_batch_size));
};

int main() {
	//--------------------------------------------------------------------------------------------------
	// Crea las imagenes con las que va a entrenar la RED.
	// las toma del directorio de origen <Folder_with_RAW_pictures> definida en config.h
	// si ya EXISTE el directorio de destino <Folder_with_Procceced_pictures> definido en config.h da por supuesto que
	// ya estan creadas y pasa de largo.
	Serialize To_disk(Folder_with_RAW_pictures);

	//--------------------------------------------------------------------------------------------------
	// Crea los DATASET de entrenamiento y testeo, cada corrida que se hace del programa crea uno distinto.
	//--------------------------------------------------------------------------------------------------
	auto train_dataset = torch::data::datasets::CementDataset(
		Folder_with_Processed_pictures,
		classes,
		torch::data::datasets::CementDataset::Mode::Train
	);

	auto train_dataset_mapping = train_dataset.map(torch::data::transforms::Stack<>());

	auto train_data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
		std::move(train_dataset_mapping),
		torch::data::DataLoaderOptions().batch_size(train_batch_size).workers(2)
		);

	auto test_dataset = torch::data::datasets::CementDataset(
		Folder_with_Processed_pictures,
		classes,
		torch::data::datasets::CementDataset::Mode::Test
	);

	auto test_dataset_mapping = test_dataset.map(torch::data::transforms::Stack<>());

	auto test_data_loader = torch::data::make_data_loader<torch::data::samplers::SequentialSampler>(
		std::move(test_dataset_mapping),
		torch::data::DataLoaderOptions().batch_size(test_batch_size).workers(2)
		);
	
	//--------------------------------------------------------------------------------------------------
	// Configuracion de la RED, se puede toquetear los FEATURES y los LAYERS
	Tiramisu net(1 /*CHANNEL_IN*/, 3 /*FEATURES*/, 4 /*LAYERS*/);
	torch::optim::Adam optimizer(net->parameters(), torch::optim::AdamOptions(1e-3));
	//torch::optim::SGD optimizer(net->parameters(), torch::optim::SGDOptions(0.1).momentum(0.5));
	//--------------------------------------------------------------------------------------------------
	cout << net << endl;
	//--------------------------------------------------------------------------------------------------
	// Si existe un entrenamiento previo arranca desde ahi, sino empieza desde cero/
	try {
		std::cout << "Try to Load <model.pt> from Disk..." << std::endl;
		torch::load(net, "model.pt");
	}
	catch (...) {
		std::cout << "MODEL Not Found..." << std::endl;
	}
	//--------------------------------------------------------------------------------------------------

	#ifdef TRAIN_NET
	for (;;) {
		static size_t N_EPOCH = 0;
		size_t N_EPOCH_TO_TRAIN = 1;
		size_t m_train = train_dataset.size().value();
		size_t m_test = test_dataset.size().value();
		for (int i = 0; i < N_EPOCH_TO_TRAIN; i++) {
			train_batch(N_EPOCH++, net, *train_data_loader, optimizer, m_train);
			torch::save(net, "model.pt");
		};
		test_batch(net, *test_data_loader, m_test);
	}
	#endif

	#ifndef TRAIN_NET
	Visualize<Tiramisu> VISVISUALIZAR(Folder_with_JPGs, net);
	#endif

	return 0;
}