#pragma once
#include "Config.h"

class Serialize {
public:
	Serialize(const std::string& input_folder, const std::string& output_folder, bool verbose_mode = false);
	bool Verbose;

private:
	std::vector<std::string> Get_structure_from_directory(const std::string& ADDRESS);
	void Proccess_picture();

	bool Directory_exists(const std::string& DIRNAME);
	std::vector<cv::Mat> Augmentation(const cv::Mat& SRC, bool FLIP, bool ROTATE);

private:
	std::vector<std::string> IMG;
	std::vector<std::string> MASK;

	const std::string Folder_with_RAW_pictures;
	const std::string Folder_with_Procceced_pictures;

};
