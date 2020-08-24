#pragma once
#include "pch.h"

namespace Tensor_utils {
	void print_opt(at::Tensor t);

	void print_opt(torch::Device device, torch::Dtype dtype);
}
