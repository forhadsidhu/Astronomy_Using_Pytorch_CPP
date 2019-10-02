#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<unordered_map>
#include<initializer_list>
#include "dataset.h"


void DataSet::ReadCSVFile(std::string file_name) {

	std::ifstream file(file_name.c_str());
	if (!file) {
		file.open(file_name.c_str());
	}
	if (!file) {
		std::cerr << "Error No" << file_name << " found. " << std::endl;

	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string line;
	std::vector<std::string>lines;
	while (getline(buffer, line, '\n')) {
		lines.push_back(line);
	}

	//the other lines contain the features for each floaer

	for (int i = 1; i < lines.size(); ++i) {
		std::vector<float>features =ReadCSVLine(lines[i]);
		x1_.push_back(features[0]);
		x2_.push_back(features[1]);
		x3_.push_back(features[2]);
		x4_.push_back(features[3]);
		y_.push_back(features[4]);

	}
}

std::vector<float>DataSet::ReadCSVLine(std::string line) {
	std::vector<float> line_data;
	std::stringstream lineStream(line);
	std::string cell;
	while (std::getline(lineStream, cell, ','))
	{
		if (cell != "setosa" && cell != "versicolor" && cell != "virginica") {
			line_data.push_back(std::stod(cell.c_str()));
		}
		else {
			if (cell == "setosa") {
				line_data.push_back(0.0f);
			}
			else if (cell == "versicolor") {
				line_data.push_back(1.0f);
			}
			else {
				line_data.push_back(2.0f);
			}
		}
	}
	return line_data;

}


std::initializer_list<float> DataSet::input(float petal_length, float petal_width, float sepal_length, float sepal_width) {
	return { petal_length,petal_width,sepal_length,sepal_width };
}

std::string DataSet::output(std::vector<float> one_hot_encoding_species) {
	if (one_hot_encoding_species[0] == 1) {
		return "setosa";
	}
	else if (one_hot_encoding_species[1] == 1) {
		return "versicolor";
	}
	else {
		return "virginica";
	}
}

