#ifndef KNAPSACK_H
#define KNAPSACK_H

#include "OneMax.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

class Knapsack
        : public OneMax
{
public:

    // ========================================================
    // Constructors & destructor
    // ========================================================
    Knapsack(): OneMax(){
    }
    Knapsack(const Knapsack& a_k): OneMax(a_k){
        copy(a_k);
    }
    Knapsack& operator =(const Knapsack& a_k)
    {
        if(this != &a_k)
        {
            dest();
            OneMax::operator =(a_k);
            copy(a_k);
        }
        return *this;
    }
    virtual ~Knapsack()
    {
        dest();
    }

    // ========================================================
    // Overriding
    // Data format:
    // ProblemSize: 545
    // WeightVector:
    // 1 2 4 5564 678 9989 ...
    // ValueVector:
    // 23 54556 7678 8899 ...
    // ========================================================
    virtual void read_in_data()
    {
        //std::cout << "I am here!\n";
        std::vector<double> data;
        double r;
        char s;
        //int i=0;
        //std::string filename = ProblemInstance;
        string filepath="C:\\Users\\13994\\Documents\\Qt_project\\Opt\\Bin\\"+ProblemInstance;
        char filepathchar[200]={'\0'};
        memcpy_s(filepathchar,sizeof(filepathchar),filepath.c_str(),filepath.size());
        ifstream fin(filepathchar,ios::in);
        if(!fin)
        {
            cout<<"File is not open!"<<endl;
            cout<<filepathchar<<endl;
            exit(1);
        }

        //std::cout << "File is ok!\n";

        while(fin.peek()!=EOF){
            fin >> s;
            if( s>=48 && s<=57 ){
                fin.putback(s);
                fin >> r;
                data.push_back(r);
            }
        }

        ProblemSize=static_cast<int>(data[0]);

        //std::cout << "Ok! " << ProblemSize << std::endl;

        //int m=0;
        for(int i=1; i<=ProblemSize; i++)
        {
            Values.push_back(data[i]);
            //m++;
        }

        //int n=0;
        for(int i=ProblemSize+1; i<=2*ProblemSize; i++)
        {
            Weights.push_back(data[i]);
            //n++;
        }

        MaxWeights=data[2*ProblemSize+1];

        fin.close();
    }


    virtual double evaluation(Solution a_solu){
        double MaxValues=0;
        double w=0;
        for(int i=0; i<ProblemSize; i++){
            if( a_solu[i] == 1 ){
                w += Weights[i];
                MaxValues += Values[i];
            }
        }
        if( w > MaxWeights )
        {
            MaxValues=0;
        }
        return MaxValues;
    }

protected:

    // ========================================================
    // Member variables
    // ========================================================
    double MaxWeights;
    std::vector<double> Weights;
    std::vector<double> Values;

private:

    // =========================================================
    // Help functions
    // =========================================================
    void copy(const Knapsack& a_k){
        Weights=a_k.Weights;
        Values=a_k.Values;
        MaxWeights=a_k.MaxWeights;
    }
    void dest(){
    }
};

#endif // KNAPSACK_H
