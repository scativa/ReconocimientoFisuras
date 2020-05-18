#pragma once

#ifndef CMDLINEOPT_H_INCLUDED
#define CMDLINEOPT_H_INCLUDED

#include <iostream>
#include "cxxopts.hpp"
#include "pch.h"

class CmdLineOpt {
public:
	CmdLineOpt(int argc, char* argv[]);

	inline bool Verbose() { return verbose; };

	inline bool NewModel() { return new_model; };
	inline std::string ModelFN() { return model_fn; };
	inline int EpochCount() { return epoch_count; };

	inline bool OverwriteDataset() { return overwrite_dataset; };
	inline std::string DatasetPrefix() { return dataset_prefix; };
	inline float PercentToTrain() {	return percent_to_train; }

private:
	bool verbose = false;

	bool new_model = false;
	std::string model_fn = "model.pt";
	std::string model_path;
	int epoch_count = 10;
	
	bool overwrite_dataset = false;
	std::string dataset_path;
	std::string dataset_prefix = "";
	float percent_to_train = 0.75f;
};

#endif
