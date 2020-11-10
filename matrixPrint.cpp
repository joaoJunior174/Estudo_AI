#include <iostream>
#include <vector>
#include <string>

void printMatrix(std::vector<std::vector<double>> mat)
{
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++)
        {
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"----------------------------"<<std::endl;
}
void printMatrix(std::vector<std::vector<std::string>> mat)
{
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++)
        {
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
    std::cout<<"----------------------------"<<std::endl;
}

void printMatrixKmeans(std::vector<std::vector<double>> mat)
{
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++)
        {
            if(j!=mat[i].size()-1)
                std::cout<<mat[i][j]<<" ";
            else
                std::cout<<" index in data -> "<<mat[i][j];
        }
        std::cout<<std::endl;
    }
    std::cout<<"----------------------------"<<std::endl;
}


void printMatrixWithLabel(std::vector<std::vector<double>> mat, std::vector<double> label)
{
    for(int i=0;i<mat.size();i++){
        for(int j=0;j<mat[i].size();j++)
        {
            std::cout<<mat[i][j]<<" ";   
        }
        std::cout<<" -> "<<label[i]<<std::endl;
    }
    std::cout<<"----------------------------"<<std::endl;
}

