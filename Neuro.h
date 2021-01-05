#pragma once
#include <iostream>
#include <time.h>
#include <random>
#include <string>
#include <math.h>
#include <cmath>
#include <thread>
 
using namespace std;
struct neuron
{
	double value;
	double error;
	void act() {
		value = (1 / (1 + pow(2.71828, -value)));
	}
};
class Neuro
{
public:
	neuron** neurons;
	double*** weights;
	int* size;

	Neuro(int counter);
	void input(int& data_name_number, string Path_to_data1, string Path_to_data2);
	short compare(int& data_name_number, string Path_to_data1, string Path_to_data2);
	void creating_layers();
	void input_first_layer();
	void layers_cleaner(int layer_number);
	void forwardfeeder(int layer_number);
	short forwardfeed();
	void backpropogation(int prediction,short answer_result,double learning_speed );
	double sigm_pro(double x);
	void saveweights(string path_to_weights);
	void input_in_neuron();
	void get_input_data(int start,double** array_to_double );
	void get_input_data_to_class(int start,  double **array_to_double);
	void creating_layers_for_predict(string path_to_weights);
	void input_data_to_test(string path_to_test);
	void printlayersout()
	{
		cout << "Down " << neurons[2][0].value << endl;
		cout << "Neutreal " << neurons[2][1].value << endl;
		cout << "Up " << neurons[2][2].value << endl;
	}
	~Neuro();

private:
	int layers_size_1_2_3[3] = { 119,70,3 };
	double input_data[119];
	int counter=0;
	char answer;
	 
};

