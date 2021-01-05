#include "Neuro.h"
#include "parsing.h"

int main()
{

    const int examples = 143;
    const int elements_in_example = 119;
    double learning_rate = 0.04;
    bool learning_rate_first_change = true;
    int counter = 0;
    int data_name_number = 0;

    double percent = 0.0;
    Neuro neuro(counter);

    string Path_to_data1 = "Datas/parsingdata", Path_to_data2 = ".txt";
    string Path_to_weights = "Weights/weights.txt";
    string Path_to_answer1 = "Answers/parsinganswers", Path_to_answer2 = ".txt";
    string path_to_predict = "test.txt";
    bool learn_or_predict;
    cout << "input  1  to learning or 0 to predict" << endl;
    cin >> learn_or_predict;
    double percent_max = 0;

    double** array_for_input_data = new double*[examples];
    for (int i = 0; i < examples; i++) {
        array_for_input_data[i] = new double[elements_in_example];
    }

    if (learn_or_predict) {
        short* array_for_answers = new short[examples];

        for (int i = 0; i < examples; i++) {

            neuro.input(i, Path_to_data1, Path_to_data2);
            neuro.get_input_data(i, array_for_input_data);
            array_for_answers[i] = neuro.compare(i, Path_to_answer1, Path_to_answer2);
        }

        neuro.creating_layers();

        short counter_after_parse = 0;

        int epoch = 0;
        short counter_cout = 0;
        double max = 0;
        short weights_epoch = 0;
        double rightanswer = 0.0;
        while (5000) {
            rightanswer = 0.0;

            for (int i = 0; i < examples; i++) {
                neuro.get_input_data_to_class(i, array_for_input_data);
                neuro.input_first_layer();
                short prediction = neuro.forwardfeed();

                if (prediction == array_for_answers[i]) {
                    rightanswer++;
                } else {
                    neuro.backpropogation(prediction, array_for_answers[i], learning_rate);
                }
            }

            weights_epoch++;

            percent = (rightanswer / examples) * 100;
            counter_cout++;
            epoch++;
            if (counter_cout == 100) {
                cout << "Epoch" << epoch << "   "
                     << " percent  " << percent << endl;
                counter_cout = 0;
            }

            if (weights_epoch == 1000) {
                weights_epoch = 0;
                neuro.saveweights(Path_to_weights);
            }
        }

        neuro.saveweights(Path_to_weights);
        cout << "Weights  saved   and  learining is succesfull !!!" << endl;

    } else {

        neuro.creating_layers_for_predict(Path_to_weights);
        neuro.input_data_to_test(path_to_predict);
        neuro.input_first_layer();

        short predict_answer = neuro.forwardfeed();
        neuro.printlayersout();

        if (predict_answer == 1) {
            cout << "Not  CHANGED! " << endl;
        } else if (predict_answer == 0) {
            cout << "DOWN! " << endl;
        } else if (predict_answer == 2) {
            cout << "UP!" << endl;
        }
    }
    return 0;
}
