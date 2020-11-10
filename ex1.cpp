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
    vector<double> weights;
   
    //aqui é encontrada a saida de acordo com uma entrada e os pesos calculados
    double findOutput(vector<double> ip)
    {

        double soma = 0;


        for (int i = 0; i < ip.size(); i++)
        {
            soma += ip[i] * this->weights[i];
        }
    
        return soma;
    }
     //aqui os pesos são atualizados
    void updateWeights(vector<double> x, double y, double t)
    {

        for (int i = 0; i < x.size(); i++)
        {
            //aqui é feita equação mostrada na aula
            //o valor da taxa de aprendizado foi escolhida de
            //forma empirica
            this->weights[i] += 0.03 * x[i] * (t - y);
        }
    }

    //função pai que chama as outras anteriores
    void findOptimalWeights(vector<vector<double>> data, vector<double> label)
    {

        for (int i = 0; i < data.size(); i++)
        {
            
            double y = this->findOutput(data[i]);

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
    vector<double> label_output;

    //transforma as labels em código binário para cada classe
    void fillOutputLabel()
    {
        for (int i = 0; i < this->label_string.size(); i++)
        {
            if (this->label_string[i] == "Iris-setosa")
            {
                this->label_output.push_back(0);
            }
            else if (this->label_string[i] == "Iris-versicolor")
            {
                this->label_output.push_back(1);
            }
        }
    }
};

int main()
{

    //nome das bases de dados
    string file_data = "iris-data.txt";
    string file_label = "iris-label.txt";

    //semente resposável por embaralhar os dados. Dependendo dessa semente
    //o treinamento sai pior ou melhor
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    Flower container = Flower();

    //aqui os dados são carregados
    container.data = readFile(file_data);
    container.label_string = readFileLabel(file_label);

    container.fillOutputLabel();

     //ambaralha os dados
    shuffle(container.data.begin(), container.data.end(), std::default_random_engine(seed));
    shuffle(container.label_output.begin(), container.label_output.end(), std::default_random_engine(seed));

    // printMatrixWithLabel(container.data,container.label_output);

    Perceptron p = Perceptron();

    //inicializando os pesos
    p.weights.push_back(0.5);
    p.weights.push_back(0.5);
    p.weights.push_back(0.5);
    p.weights.push_back(0.5);


    // for(int i=0;i<10;i++)
        p.findOptimalWeights(container.data, container.label_output);

    for (int i = 0; i < p.weights.size(); i++)
    {
        cout<<p.weights[i]<<endl;
    }

    //lê os dados da base de dados de teste
    vector<vector<double>> input_test = readFile("test-iris-data.txt");
    vector<string> input_test_label = readFileLabel("test-iris-data-label.txt");

    double total=0;

    for (int i = 0; i < input_test.size(); i++)
    {

        string resp;

        double output = p.findOutput(input_test[i]);

        if (output <= 0)
        {
            resp="Iris-setosa";
        }
        else if (output > 0)
        {
            resp="Iris-versicolor";
        }

        if(resp==input_test_label[i])
            total++;

        cout<<resp<<endl;

    }

    cout<<"O total de porcentgem de acerto foi de "<<total*100/input_test.size()<<endl;

    return 0;
}