#pragma once

#include "Neuro.h"
#include <fstream>
#include <string.h>
#include <string>
#include <strings.h>

Neuro::Neuro(int counter)
{
    this->counter = counter;
}

void Neuro::input(int& data_name_number, string Path_to_data1, string Path_to_data2)
{

    string number_name = to_string(data_name_number);
    string temp, line_line, line;
    double result;
    ifstream fin;
    char temp_line[40];
    char temp_line_2[40];
    char* p_temp_line;

    p_temp_line = temp_line;

    fin.open(Path_to_data1 + number_name + Path_to_data2);
    if (!fin)
        exit(1);
    int filt = 0;
    while ((fin) && (filt < 119)) {

        getline(fin, line_line);
        temp = line_line;
        strcpy(p_temp_line, temp.c_str());
        int t = int(p_temp_line[0]);

        if ((t >= 48) && (t <= 57)) {
            p_temp_line[0] = '0';
            p_temp_line[2] = '0';
            result = double(strtod(p_temp_line, NULL));
            result = result * 10;
            input_data[filt++] = result;
        }
        temp = '\0';
    }

    fin.close();
    counter = 0;
}

short Neuro::compare(int& data_name_number, string Path_to_data1, string Path_to_data2)
{
    ifstream fin;
    string temp;
    double result;
    string name_number = to_string(data_name_number);
    int strin;
    fin.open(Path_to_data1 + name_number + Path_to_data2);
    if (!fin)
        exit(1);

    while (fin) {
        getline(fin, temp);
        char temp_line[60];
        char* p_temp_line;
        p_temp_line = temp_line;
        double befresult[20];

        strcpy(p_temp_line, temp.c_str());
        strin = int(p_temp_line[0]);
        if ((strin >= 48) && (strin <= 57)) {
            p_temp_line[2] = '0';
            p_temp_line[0] = '0';
            result = strtod(p_temp_line, NULL);
            result = result * 10;
            break;
        }

        temp_line[0] = '\0';
    }

    fin.close();

    if (input_data[118] == result)
        return 1;
    else if (input_data[118] > result)
        return 0;
    else
        return 2;
}

void Neuro::creating_layers()
{

    srand(time(NULL));
    neurons = new neuron*[3];
    weights = new double**[2];
    size = new int[3];
    for (int i = 0; i < 3; i++) {
        size[i] = layers_size_1_2_3[i];
        neurons[i] = new neuron[layers_size_1_2_3[i]];
        if (i < 2) {
            weights[i] = new double*[layers_size_1_2_3[i]];
            for (int j = 0; j < layers_size_1_2_3[i]; j++) {
                weights[i][j] = new double[layers_size_1_2_3[i + 1]];
                for (int k = 0; k < layers_size_1_2_3[i + 1]; k++) {
                    weights[i][j][k] = ((rand() % 100)) * (0.001 / size[i]);
                }
            }
        }
    }
}

void Neuro::input_first_layer()
{
    for (int i = 0; i < size[0]; i++) {
        neurons[0][i].value = input_data[i];
    }
}

void Neuro::layers_cleaner(int layer_number)
{
    for (int i = 0; i < size[layer_number]; i++) {
        neurons[layer_number][i].value = 0;
    }
}

void Neuro::forwardfeeder(int layer_number)
{

    for (int i = 0; i < layers_size_1_2_3[layer_number]; i++) {
        for (int j = 0; j < layers_size_1_2_3[layer_number - 1]; j++) {
            neurons[layer_number][i].value += neurons[layer_number - 1][j].value * weights[layer_number - 1][j][i];
        }
        neurons[layer_number][i].act();
    }
}

short Neuro::forwardfeed()
{
    for (int i = 1; i < 3; i++) {
        layers_cleaner(i);
        forwardfeeder(i);
    }

    double max = 0;
    short predict;
    for (int i = 0; i < 3; i++) {
        if (neurons[2][i].value > max) {
            max = neurons[2][i].value;
            predict = i;
        }
    }
    return predict;
}

void Neuro::backpropogation(int prediction, short answer_result, double learning_speed)
{
    for (int i = 2; i > 0; i--) {
        if (i == 2) {
            for (int j = 0; j < layers_size_1_2_3[i]; j++) {
                if (j != int(answer_result)) {
                    neurons[i][j].error = -pow(neurons[i][j].value, 2);
                } else {
                    neurons[i][j].error = 1.0 - neurons[i][j].value;
                }
            }
        } else {
            for (int j = 0; j < size[i]; j++) {
                double error = 0.0;
                for (int k = 0; k < size[i + 1]; k++) {
                    error += neurons[i + 1][k].error * weights[i][j][k];
                }
                neurons[i][j].error = error;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < size[i]; j++) {
            for (int k = 0; k < size[i + 1]; k++) {
                weights[i][j][k] += learning_speed * neurons[i + 1][k].error
                    * sigm_pro(neurons[i + 1][k].value) * neurons[i][j].value;
            }
        }
    }
}
double Neuro::sigm_pro(double x)
{
    if ((fabs(x - 1) < 1e-9) || (fabs(x) < 1e-9))
        return 0.0;
    double res = x * (1.0 - x);
    return res;
}

void Neuro::saveweights(string path_to_weights)
{

    ofstream weight_out;
    weight_out.open(path_to_weights);
    if (!weight_out) {
        cout << "Error  saving  weights " << endl;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < layers_size_1_2_3[i]; j++) {
            for (int k = 0; k < layers_size_1_2_3[i + 1]; k++) {
                weight_out << weights[i][j][k] << " ";
            }
        }
    }
    weight_out.close();
}

void Neuro::input_in_neuron()
{

    for (int i = 0; i < layers_size_1_2_3[0]; i++) {
        neurons[0][i].value = input_data[i];
    }
}

void Neuro::get_input_data(int start, double** array_to_double)
{

    for (int j = 0; j < 119; j++) {
        array_to_double[start][j] = input_data[j];
    }
}

void Neuro::get_input_data_to_class(int start, double** array_to_double)
{

    for (int j = 0; j < 119; j++) {
        input_data[j] = array_to_double[start][j];
    }
}

void Neuro::creating_layers_for_predict(string path_to_weights)
{
    srand(time(0));
    ifstream fin_weights;
    fin_weights.open(path_to_weights);
    char fin_line[40];
    char* p_fin_line = fin_line;
    string fin_input;
    if (!fin_weights) {
        cout << "Error to path to predict " << endl;
        exit(1);
    }
    neurons = new neuron*[3];
    weights = new double**[2];
    size = new int[3];
    for (int i = 0; i < 3; i++) {
        size[i] = layers_size_1_2_3[i];
        neurons[i] = new neuron[layers_size_1_2_3[i]];
        if (i < 2) {
            weights[i] = new double*[layers_size_1_2_3[i]];
            for (int j = 0; j < layers_size_1_2_3[i]; j++) {
                weights[i][j] = new double[layers_size_1_2_3[i + 1]];
                for (int k = 0; k < layers_size_1_2_3[i + 1]; k++) {
                    fin_weights >> fin_input;
                    strcpy(p_fin_line, fin_input.c_str());
                    weights[i][j][k] = strtod(p_fin_line, NULL);
                }
            }
        }
    }
}

void Neuro::input_data_to_test(string path_to_test)
{
    ifstream predict_test;
    predict_test.open(path_to_test);

    if (!predict_test) {
        cout << "error opening  test  file " << endl;
        exit(1);
    }

    string fin_predict;
    char ch_fin_predict[40], temp[40];
    char *p_ch_fin_predict = ch_fin_predict, *p_temp_line = temp;
    int pred = 0, filt = 0;
    double res;

    while (predict_test && filt <= 119) {

        getline(predict_test, fin_predict);
        strcpy(p_temp_line, fin_predict.c_str());
        int t = int(p_temp_line[0]);

        if ((t >= 48) && (t <= 57)) {
            p_temp_line[0] = '0';
            p_temp_line[2] = '0';
            res = double(strtod(p_temp_line, NULL));
            res = res * 10;
            input_data[filt++] = res;
        }
    }
}

Neuro::~Neuro()
{
    for (int i = 0; i < 3; i++) {
        delete[] neurons[i];
        if (i < 2) {
            for (int j = 0; j < layers_size_1_2_3[i]; j++) {
                delete[] weights[i][j];
            }
            delete[] weights[i];
        }
    }
    delete neurons;
    delete weights;
    delete size;
}
