#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<initializer_list>


class DataSetMetaData {

	friend class DataSet;
private:
	float sepal_length;
	float sepal_width;
	float petal_length;
	float petal_width;
	std::string species;
};

class DataSet {

public:

	//read the given csv file and complete_x and y_
	void ReadCSVFile(std::string file_name);


	//Construct a data set from the given csv file path
	DataSet(std::string file_name) {
		ReadCSVFile(file_name);
	}

	///getters

	std::vector<float>& x1() { return x1_; }
	std::vector<float>& x2() { return x2_; }
	std::vector<float>& x3() { return x3_; }
	std::vector<float>& x4() { return x4_;}
	std::vector<float& y() { return y_; }



	///convert one csv line to a vector of float

	std::vector<float>ReadCSVLine(std::string line);
	///normalize a human input using the data set metadata
	std::initializer_list<float>input(float petal_length,float peta_width,float sepal_length,float sepal_width);

	std::string output(std::vector<float>one_hot_encoding_species);

private:
	DataSetMetaData data_set_metadata;
	std::vector<float>x1_;
	std::vector<float>x2_;
	std::vector < float>x3_;
	std::vector<float>x4_;
	std::vector<float>y_;
};

