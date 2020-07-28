#pragma once
#include "pch.h"
#include "Config.h"

using namespace std;
using namespace torch;

struct BN_Relu_ConvImpl : public torch::nn::Module{
	BN_Relu_ConvImpl(const size_t& CHANNEL_IN, const size_t& CHANNEL_OUT, const size_t& KERNEL, const float& DROPOUT) {
		//m_block->push_back(torch::nn::BatchNorm2d(CHANNEL_IN));
		m_block->push_back(torch::nn::Functional(torch::relu));
		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_IN, CHANNEL_OUT, KERNEL).padding(1).bias(true)));
		if (DROPOUT > 0.0f) m_block->push_back(torch::nn::Dropout(DROPOUT));

		register_module("BN_Relu_Conv", m_block);
	}

	torch::Tensor forward(torch::Tensor x) {
		return m_block->forward(x);
	};

	torch::nn::Sequential m_block;
};
TORCH_MODULE(BN_Relu_Conv);

struct Inner_blockImpl : public torch::nn::Module {
	Inner_blockImpl(const size_t& CHANNEL_IN, const size_t& CHANNEL_OUT, const size_t& KERNEL, const float& DROPOUT = 0.5f) :
		m_block(BN_Relu_Conv(CHANNEL_IN, CHANNEL_OUT, KERNEL, DROPOUT))
	{
		register_module("InnerBlock", m_block);
	}

	torch::Tensor forward(torch::Tensor _IN) {
		_OUT = m_block->forward(_IN);
		return (torch::cat({ _OUT, _IN }, 1));
	};

	torch::nn::Sequential m_block;
	torch::Tensor _OUT;
};
TORCH_MODULE(Inner_block);

struct Dense_blockImpl : public torch::nn::Module {
	Dense_blockImpl(const size_t CHANNEL_IN, const size_t CHANNEL_OUT, const size_t LAYERS)
	{
		for (size_t i = 0; i < LAYERS-1; i++) {
			m_block->push_back(Inner_block(CHANNEL_IN + i*CHANNEL_OUT, CHANNEL_OUT, 3, 0.3f));
		}

		m_block->push_back(BN_Relu_Conv(CHANNEL_IN + (LAYERS-1)* CHANNEL_OUT, CHANNEL_OUT, 3, 0));
		register_module("DenseBlock", m_block);
	};

	torch::Tensor forward(torch::Tensor x) {

		torch::Tensor OBJ = m_block->forward(x);

		for (size_t i = 0; i < (m_block->size() - 1); i++) {
			auto PTR = std::static_pointer_cast<Inner_blockImpl>(m_block[i]);
			OBJ = torch::cat({ OBJ, PTR->_OUT }, 1);
		}

		return OBJ;
	};

	torch::nn::Sequential m_block;
};
TORCH_MODULE(Dense_block);

struct TiramisuImpl : public torch::nn::Module {
	TiramisuImpl(const size_t CHANNEL_IN, const size_t CHANNEL_OUT, const size_t LAYERS)
	{
		m_block->push_back(Dense_block(CHANNEL_IN, CHANNEL_OUT, LAYERS));
		m_block->push_back(BN_Relu_Conv(LAYERS * CHANNEL_OUT, 1, 3, 0));
		m_block->push_back(torch::nn::Functional(torch::sigmoid));
		register_module("Tiramisu", m_block);
	};

	torch::Tensor forward(torch::Tensor x) {
		return m_block->forward(x);
	};

	torch::nn::Sequential m_block;
};
TORCH_MODULE(Tiramisu);


struct BatchNorm_Relu_ConvolutionImpl : public torch::nn::Module {
	BatchNorm_Relu_ConvolutionImpl(const size_t CHANNEL_IN, const size_t CHANNEL_OUT)
	{
		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_IN, CHANNEL_OUT, 3).stride(1).padding(1).bias(true)));
		//m_block->push_back(torch::nn::BatchNorm2d(CHANNEL_OUT));
		//m_block->push_back(torch::nn::Dropout(0.2));
		m_block->push_back(torch::nn::Functional(torch::relu));

		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_OUT, CHANNEL_OUT, 3).stride(1).padding(1).bias(true)));
		//m_block->push_back(torch::nn::BatchNorm2d(CHANNEL_OUT));
		//m_block->push_back(torch::nn::Dropout(0.2));
		m_block->push_back(torch::nn::Functional(torch::relu));

		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_OUT, CHANNEL_OUT, 3).stride(1).padding(1).bias(true)));
		//m_block->push_back(torch::nn::BatchNorm2d(CHANNEL_OUT));
		//m_block->push_back(torch::nn::Dropout(0.2));
		m_block->push_back(torch::nn::Functional(torch::relu));

		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_OUT, CHANNEL_OUT, 3).stride(1).padding(1).bias(true)));
		//m_block->push_back(torch::nn::BatchNorm2d(CHANNEL_OUT));
		//m_block->push_back(torch::nn::Dropout(0.2));
		m_block->push_back(torch::nn::Functional(torch::relu));

		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_OUT, CHANNEL_IN, 3).stride(1).padding(1).bias(true)));
		//m_block->push_back(torch::nn::BatchNorm2d(CHANNEL_IN));
		//m_block->push_back(torch::nn::Dropout(0.2));
		m_block->push_back(torch::nn::Functional(torch::sigmoid));

		register_module("BatchNorm_Relu_Convolution", m_block);
	};

	torch::Tensor forward(torch::Tensor x) {
		return m_block->forward(x);
	};

	nn::Sequential m_block;
};
TORCH_MODULE(BatchNorm_Relu_Convolution);

struct REDPRUImpl : public torch::nn::Module {
	REDPRUImpl(const size_t CHANNEL_IN, const size_t LAYERS, const size_t K_FEATURES)
	{
		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(CHANNEL_IN, K_FEATURES, 3).stride(1).padding(1).bias(true)));
		m_block->push_back(torch::nn::Functional(torch::relu));
		for (auto i = 0; i < LAYERS; i++) {
			m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(K_FEATURES, K_FEATURES, 3).stride(1).padding(1).bias(true)));
			m_block->push_back(torch::nn::Dropout(0.5));
			m_block->push_back(torch::nn::Functional(torch::relu));
		}
		m_block->push_back(torch::nn::Conv2d(torch::nn::Conv2dOptions(K_FEATURES, CHANNEL_IN, 3).stride(1).padding(1).bias(true)));
		m_block->push_back(torch::nn::Functional(torch::sigmoid));

		register_module("REDPRUImpl", m_block);
	};

	torch::Tensor forward(torch::Tensor x) {
		return m_block->forward(x);
	}

	nn::Sequential m_block;
};
TORCH_MODULE(REDPRU);
