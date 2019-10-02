#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<unordered_map>
#include<initializer_list>
#include "dataset.h"


void DataSet::ReadCSVFile(std::string file_name) {

	std::ifstream file(file_name.c_str());

	if (!file)
	{
		file.open(file_name.c_str());
	}
	if (!file) {
		std::cerr << "Error: No " << file_name << " found ." << std::endl;

	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string line;
	
	std::vector<std::string>lines;
		while (getline(buffer, line,'\n')) {
			//std::cout << line << std::endl;
			//std::cout << "ses" << std::endl;
			lines.push_back(line);
	}


		//std::cout<<"lines-size "<< lines.size() << std::endl;
		///the other lines contain the features for each flower

		for (int i = 1; i < lines.size(); ++i) {

			//std::cout << lines[i] << std::endl;
			std::vector<float>features = ReadCSVLine(lines[i]);

			

			mean_.push_back(features[0]);
			stdev_.push_back(features[1]);
			kurtosis_.push_back(features[2]);
			skewness_.push_back(features[3]);
			snr_.push_back(features[4]);
			dmsnr_.push_back(features[5]);
			kurtosissnr_.push_back(features[6]);
			skewsnr_.push_back(features[7]);
			class_.push_back(features[8]);

	}

}


std::vector<float> DataSet::ReadCSVLine(std::string line) {
	std::vector<float> line_data;
	std::stringstream lineStream(line);
	std::string cell;
	while (std::getline(lineStream, cell, ','))
	{
		if (cell != "setosa" && cell != "versicolor" && cell != "virginica") {
			line_data.push_back(std::stod(cell.c_str()));
		}
		
	}

	//std::cout << "Line data size: " << line_data.size() << std::endl;
	return line_data;
}
