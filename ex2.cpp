#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <random>
#include <chrono>
#include <algorithm>
#include "readFile.cpp"
#include "matrixPrint.cpp"

using namespace std;

//classe reponsavel por estruturar o perceptron
class Perceptron
{
public:

    //peso da rede
    vector<vector<double>> weights;

    //aqui é encontrada a saida de acordo com uma entrada e os pesos calculados
    void findOutput(vector<double> ip,vector<double> &soma)
    {

        
        for (int j = 0; j < this->weights.size(); j++)
        {
            for (int i = 0; i < ip.size(); i++)
            {
                soma[j] += ip[i] * this->weights[j][i];
            }
        }

    }
    //aqui os pesos são atualizados
    void updateWeights(vector<double> x, vector<double> y, vector<double> t)
    {

        for (int j = 0; j < this->weights.size(); j++)
        {
            
            for (int i = 0; i < x.size(); i++)
            {
                //aqui é feita equação mostrada na aula
                //o valor da taxa de aprendizado foi escolhida de
                //forma empirica
                this->weights[j][i] += 0.0095 * x[i] * (t[j] - y[j]);
                
            }
        }
    }

    //função pai que chama as outras anteriores
    void findOptimalWeights(vector<vector<double>> data, vector<vector<double>> label)
    {

        for (int i = 0; i < data.size(); i++)
        {
        
            vector<double> y(3,0);

            this->findOutput(data[i],y);

            this->updateWeights(data[i], y, label[i]);
        
            
        }
        
        
    }
};

//classe que armazena os dados da base de dado
class Flower
{
public:
    vector<vector<double>> data;
    vector<string> label_string;
    vector<vector<double>> label_output;

    //transforma as labels em código binário para cada classe
    void fillOutputLabel()
    {
        for (int i = 0; i < this->label_string.size(); i++)
        {
            if (this->label_string[i] == "Iris-setosa")
            {
                this->label_output.push_back({1, 0, 0});
            }
            else if (this->label_string[i] == "Iris-versicolor")
            {
                this->label_output.push_back({0, 1, 0});
            }
            else if (this->label_string[i] == "Iris-virginica")
            {
                this->label_output.push_back({0, 0, 1});
            }
        }
    }
};

int main()
{
    //nome das bases de dados
    string file_data = "iris-data-3-class.txt";
    string file_label = "iris-data-3-class-label.txt";

    //semente resposável por embaralhar os dados. Dependendo dessa semente
    //o treinamento sai pior ou melhor

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    Flower container = Flower();

    //aqui os dados são carregados
    container.data = readFile(file_data);
    container.label_string = readFileLabel(file_label);

    //transforma as labels em numeros (setosa -> 100, versicolor -> 010, virginica -> 001)
    container.fillOutputLabel();

    //ambaralha os dados
    shuffle(container.data.begin(), container.data.end(), std::default_random_engine(seed));
    shuffle(container.label_output.begin(), container.label_output.end(), std::default_random_engine(seed));

    // printMatrixWithLabel(container.data,container.label_output);
    
    Perceptron p = Perceptron();

    //inicializando os pesos
    p.weights.push_back({0.3, 0.3, 0.3,0.3}); //setosa
    p.weights.push_back({0.3, 0.3, 0.3,0.3}); //versicolor
    p.weights.push_back({0.3, 0.3, 0.3,0.3}); //virginica
    
    
    //fica recalculando os pesos, número selecionado de forma empírica
    for(int i=0;i<200;i++)
        p.findOptimalWeights(container.data, container.label_output);

        
    printMatrix(p.weights);

    // for (int i = 0; i < p.weights.size(); i++)
    // {
    //     cout << p.weights[i] << endl;
    // }

    
    //base de teste
    vector<vector<double>> input_test = readFile("iris-data-3-class-test.txt");
    vector<string> input_test_label = readFileLabel("iris-data-3-class-label-test.txt");

    double total = 0;

    //lê a base de teste
    for (int i = 0; i < input_test.size(); i++)
    {

        string resp;

        vector<double> output(3,0);
        p.findOutput(input_test[i],output);

        // cout<<round(output[0])<<" "<<round(output[1])<<" "<<round(output[2])<<endl;
        //arredonda os valores double
        output[0]=fabs(round(output[0]));
        output[1]=fabs(round(output[1]));
        output[2]=fabs(round(output[2]));

        if (output[0] > 0 && output[1] <= 0 && output[2] <= 0)
        {
            resp = "Iris-setosa";
        }
        else if (output[0] <= 0 && output[1] > 0 && output[2] <= 0)
        {
            resp = "Iris-versicolor";
        }
        else if(output[0] <= 0 && output[1] <= 0 && output[2] > 0){
            resp = "Iris-virginica";
        }

        if (resp == input_test_label[i])
            total++;

        cout << resp << endl;
    }

    cout << "O total de porcentgem de acerto foi de " << total * 100 / input_test.size() << endl;

    return 0;
}