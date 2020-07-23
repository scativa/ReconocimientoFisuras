#pragma once
#include "Config.h"

class Serialize {
public:
	Serialize(const std::string& ADRESS);
	std::vector<std::string> Get_structure_from_directory(const std::string& ADDRESS);
	bool Directory_exists(const std::string& DIRNAME);
	std::vector<cv::Mat> Augmentation(const cv::Mat& SRC, bool FLIP, bool ROTATE);

	void Process_picture();
private:
	std::vector<std::string> IMG;
	std::vector<std::string> MASK;
};
