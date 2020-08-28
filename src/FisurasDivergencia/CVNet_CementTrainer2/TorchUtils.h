#pragma once
#include "pch.h"


namespace torch_utils {
	void print_opt(at::Tensor t);
	void print_opt(torch::Device device, torch::Dtype dtype);
	void print_opt(torch::nn::Linear l);

	class ConvOptionsLayer {
	public:
		// Similar a torch::nn::Conv2dOptions? Lo alimenta
		inline ConvOptionsLayer(int64_t in_channels, int64_t out_channels, int64_t kernel_size, int64_t pool_size = 1) :
			in_channels(in_channels), out_channels(out_channels), kernel_size(kernel_size), pool_size(pool_size) {};
		inline ConvOptionsLayer() {};

		torch::nn::Conv2dOptions Conv2dOptions();
	public:
		int64_t in_channels, out_channels;
		int64_t kernel_size; // Podría ser un array también
		int64_t pool_size; // En caso de que sea continuado por un xxx_pool2d(x,pool_size). De no existir pool_size = 1;

		void Print();
	};

	typedef std::vector<int> vint;
	typedef std::vector<ConvOptionsLayer> VConvOptionsLayers;

	class SecConvOptions {
	public:
		VConvOptionsLayers layers_opts;
		uint32_t NextLinearLayer_InputSize(); // Cálculo del tamñano de la entrada la siguente capa lineal. = w * h * size_last_layer;
		inline SecConvOptions(uint32_t img_size) : img_size(img_size) {};

		void Print();
	private:
		inline int64_t Cant_ConvLayers() { return layers_opts.size(); };
		uint32_t recLastLayer_OutputSize(uint32_t in_size, int layer);
		uint32_t img_size;
	};
}
