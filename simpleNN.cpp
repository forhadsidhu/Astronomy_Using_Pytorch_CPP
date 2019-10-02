#include<torch/script.h>
#include<torch/torch.h>
#include<iostream>
#include<vector>
#include "dataset.h"


struct Net : torch::nn::Module {

	Net() {

		///construct and register two linear submodules

		fc1 = register_module("fc1",torch::nn::Linear(8,10));
		fc2 = register_module("fc2",torch::nn::Linear(10,7));


	}


	///Implement the Net's algorithm


	torch::Tensor forward(torch::Tensor x) {

		//use one of many tensor manipulation functions.

		x = torch::relu(fc1->forward(x.view({-1,8})));

		//std::cout << x << std::endl;

		x = torch::log_softmax(fc2->forward(x), 1);


		return x;
	}

	torch::nn::Linear fc1{ nullptr }, fc2{ nullptr };



};


int main()
{

	
	DataSet data_set("pulsar_star.csv");

	at::Tensor input_tensor;
	at::Tensor output_tensor;


	std::vector<float>input_vector;
	std::vector<float>target_output;


	//Iterate the data loader to yield batches from the dataset.

	for (unsigned i = 0; i < 150; i++)
	{

		 ///form a input tensor combined of mean std.deviation 

		
		
		input_vector.push_back(data_set.mean()[i]);
		input_vector.push_back(data_set.stdev()[i]);
		input_vector.push_back(data_set.kurtosis()[i]);
		input_vector.push_back(data_set.skewness()[i]);
		input_vector.push_back(data_set.snr()[i]);
		input_vector.push_back(data_set.dmsnr()[i]);
		input_vector.push_back(data_set.kurtosissnr()[i]);
		input_vector.push_back(data_set.skewsnr()[i]);


		target_output.push_back(float(data_set.clas()[i]));

	}





	


	//std::cout << target_output.size() << std::endl;
	at::TensorOptions options(at::ScalarType::Long);

	input_tensor = torch::from_blob(input_vector.data(), {150 ,8 });
	input_tensor = input_tensor.toType(at::kFloat);

	output_tensor = torch::from_blob(target_output.data(), { long(target_output.size()) });
	output_tensor = output_tensor.toType(at::ScalarType::Long);
	//output_tensor = output_tensor.toType(at::kFloat);

	//std::cout << output_tensor << std::endl;
	

	//std::cout << input_tensor << std::endl;

	//loading the model

	auto net = std::make_shared<Net>();

	//std::cout << net << std::endl;

   ///setting up optimizer

	std::cout <<net->parameters()<< std::endl;


	torch::optim::SGD optimizer(net->parameters(),0.01);


	
	for (size_t epoch = 1; epoch <= 10;epoch++) {


		
		
		//std::cout << "YES" << std::endl;


		optimizer.zero_grad();
		//std::cout << "YES1" << std::endl;

		//execute the model for the input data
		torch::Tensor prediction = net->forward(input_tensor);

		
		//std::cout << "YES2" << std::endl;

		//std::cout << "Output---------Prediciton----------------" << std::endl;

		//std::cout << prediction << std::endl;

		//std::cout << "Output-----------" << std::endl;
		//std::cout << output_tensor << std::endl;

		//std::cout << "Prediction-------------" << std::endl;
		prediction = prediction.toType(at::kFloat);

		//prediction = prediction.toType(at::ScalarType::Long);
		std::cout << prediction << std::endl;

		
		

		

		//Compute a loss value to judge the prediction of our model
	    torch::Tensor  loss = (torch::nll_loss(prediction,output_tensor));

	

		//std::cout << "YES3" << std::endl;
		//compute a gradients of the loss w.r.t the parameters of our model

		loss.backward();


		//std::cout << "YES4" << std::endl;
		//update the parameter based on the calculated gradients

		optimizer.step();
		std::cout << "Epoch : " << epoch << " ! Loss " << loss.item<float>() << std::endl;

		//serialize your model periodically as a checkpoint

		torch::save(net, "net.pt");


	}

	
	/*
	torch::jit::script::Module module;

	try {
		module = torch::jit::load("F://Visual_studio//Pytorch//Pytorch//net.pt");
	}
	catch(const c10::Error & e){
		std::cout << "Model not loaded" << std::endl;
	}
	



	// Create a vector of inputs.
	std::vector<torch::jit::IValue> inputs;

	std::vector<double>test_data;

	test_data.push_back(double(1.1));
	test_data.push_back(double(2.1));
	test_data.push_back(double(3.4));
	test_data.push_back(double(4.5));
	test_data.push_back(double(5.7));
	test_data.push_back(double(6.8));
	test_data.push_back(double(7.9));
	test_data.push_back(double(8.4));


	for (int i = 0; i < test_data.size(); i++)
	{
		std::cout << test_data[i] << std::endl;
	}

	at::Tensor test_tensor = torch::from_blob(test_data.data(), {1 ,8 });
	test_tensor = test_tensor.toType(at::kFloat);

	
	inputs.push_back(test_tensor);

	std::cout << "Test tensor-----------" << std::endl;
	std::cout << inputs << std::endl;

	// Execute the model and turn its output into a tensor.
	
	at::Tensor output = module.forward(inputs).toTensor();

	std::cout << output << std::endl;
	*/

	return	0;

}



