#pragma once
#include "cmdlineopt.h"
#include "CVNet.h"

class Trainer
{
public:
	Trainer();

	float Test(
		torch::Tensor& IMG,
		torch::Tensor& TRG
	);

	void Train(
		const uint32_t& EPOCH,
		torch::optim::Optimizer& OPT,
		torch::Tensor& IMG,
		torch::Tensor& TRG
	);

private:
	Network NET;
	torch::Tensor _image, _target; 
};

