#include "pch.h"
using namespace cv;

const uint32_t m_batch_size = 64;

struct NetCONV : torch::nn::Module {
    NetCONV()
        : conv1(torch::nn::Conv2dOptions(1, 10, /*kernel_size=*/5)),
        conv2(torch::nn::Conv2dOptions(10, 20, /*kernel_size=*/5)),
        fc1(320, 50),
        fc2(50, 10) {
        register_module("conv1", conv1);
        register_module("conv2", conv2);
        register_module("conv2_drop", conv2_drop);
        register_module("fc1", fc1);
        register_module("fc2", fc2);
    }

    torch::Tensor forward(torch::Tensor x) {
        //{64,1,28,28} dimensin del tensor x.
        x = torch::relu(torch::max_pool2d(conv1->forward(x), 2));
        x = torch::relu(
            torch::max_pool2d(conv2_drop->forward(conv2->forward(x)), 2));
        x = x.view({ -1, 320 });
        x = torch::relu(fc1->forward(x));
        //x = torch::dropout(x, /*p=*/0.5, /*training=*/is_training());
        x = fc2->forward(x);
        return torch::log_softmax(x, /*dim=*/1);
    }

    torch::nn::Conv2d conv1;
    torch::nn::Conv2d conv2;
    torch::nn::Dropout2d conv2_drop;
    torch::nn::Linear fc1;
    torch::nn::Linear fc2;
};

struct Net : torch::nn::Module {
    Net() {
        // Construct and register two Linear submodules.
        fc1 = register_module("fc1", torch::nn::Linear(784, 32));
        fc2 = register_module("fc2", torch::nn::Linear(32, 32));
        fc3 = register_module("fc3", torch::nn::Linear(32, 32));
        fc4 = register_module("fc4", torch::nn::Linear(32, 10));
    }

    // Implement the Net's algorithm.
    torch::Tensor forward(torch::Tensor x) {
        x = torch::relu(fc1->forward(x.reshape({ x.size(0), 784 })));
        x = torch::relu(fc2->forward(x));
        x = torch::relu(fc3->forward(x));
        x = torch::log_softmax(fc4->forward(x), /*dim=*/1);
        return x;
    }
    torch::nn::Linear fc1{ nullptr }, fc2{ nullptr }, fc3{ nullptr }, fc4{ nullptr };
};

template <typename DataLoader>
void test_batch(NetCONV& MODEL, DataLoader& DATA_LOADER, size_t SIZE) {
    MODEL.eval();
    double test_loss = 0;
    int64_t correct = 0;

    for (const auto& batch : DATA_LOADER) {
        auto prediction = MODEL.forward(batch.data);
        correct += prediction.argmax(1).eq(batch.target).sum().template item<int64_t>();
    };

    std::printf("Accuracy: %.3f% \r\n", ((float)correct / (float)SIZE));
};

template <typename DataLoader>
void train_batch(size_t EPOCH, NetCONV& MODEL, DataLoader& DATA_LOADER, torch::optim::Optimizer& optimizer, size_t SIZE) {
    MODEL.train();
    size_t batch_idx = 0;

    for (auto& batch : DATA_LOADER) {
        optimizer.zero_grad();

        auto prediction = MODEL.forward(batch.data);
        auto loss = torch::nll_loss(prediction, batch.target);

        loss.backward();
        optimizer.step();

        std::printf("\rTrain Epoch: %ld [%5ld/%5ld] Loss: %.4f ", EPOCH, batch_idx++ * m_batch_size, SIZE, loss.template item<float>());
    }
    std::printf("\r\n");
 };

auto main() -> int {
    NetCONV net;
    //Net net;// = std::make_shared<Net>();

    // Create a multi-threaded data loader for the MNIST dataset.
    auto m_MNIST_test = torch::data::datasets::MNIST("./data", torch::data::datasets::MNIST::Mode::kTest);
    auto m_data_set_test = m_MNIST_test.map(torch::data::transforms::Stack<>());
    auto m_data_loader_test = torch::data::make_data_loader(m_data_set_test, m_batch_size);

    auto m_MNIST_train = torch::data::datasets::MNIST("./data", torch::data::datasets::MNIST::Mode::kTrain);
    auto m_data_set = m_MNIST_train.map(torch::data::transforms::Stack<>());
    auto m_data_loader = torch::data::make_data_loader(m_data_set, m_batch_size);

    // Instantiate an SGD optimization algorithm to update our Net's parameters.
    torch::optim::SGD optimizer(net.parameters(), torch::optim::SGDOptions(0.01).momentum(0.5));// /*lr=*/0.1);

    size_t epoch = 0;
    for (;;) {
        train_batch(epoch++, net, *m_data_loader, optimizer, m_data_set.size().value());

        // Testing result.
        test_batch(net, *m_data_loader, m_data_set.size().value());
        test_batch(net, *m_data_loader_test, m_data_set_test.size().value());
    }

    return 0;
}