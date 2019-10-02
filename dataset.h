#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<initializer_list>



class DataSetMetaData {

	friend class DataSet;


};



class DataSet {

	

public:

	//read the given csv file and complete x_ and y_

	void ReadCSVFile(std::string file_name);
	

	//Construct a dataset from the given csv file path

	DataSet(std::string file_name) {
		ReadCSVFile(file_name);

		//std::cout << "YES COME" << std::endl;
	}

	//getters

	std::vector<float>mean() { return mean_; };
	std::vector<float>stdev() { return stdev_; };
	std::vector<float>kurtosis() { return kurtosis_; };
	std::vector<float>skewness() { return skewness_; };
	std::vector<float>snr() { return snr_; };
	std::vector<float>dmsnr() { return dmsnr_; };
	std::vector<float>kurtosissnr() { return kurtosissnr_; };
	std::vector<float>skewsnr() { return skewsnr_; };
	std::vector<float>clas() { return class_; };

	


	//convert one csv line to a vector of float

	std::vector<float> ReadCSVLine(std::string line);

	

private:
	DataSetMetaData data_set_metadata;
	std::vector<float>mean_;
	std::vector<float>stdev_;
	std::vector<float>kurtosis_;
	std::vector<float>skewness_;
	std::vector<float>snr_;
	std::vector<float>dmsnr_;
	std::vector<float>kurtosissnr_;
	std::vector<float>skewsnr_;

	std::vector<float>class_;

};