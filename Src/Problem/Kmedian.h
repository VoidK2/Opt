#ifndef KMEDIAN_H
#define KMEDIAN_H

#include "OneMax.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <cmath>
#include <sstream>
#include <vector>
#include <cstdlib>
using namespace std;

class Kmedian
        : public OneMax
{
public:
    Kmedian(): OneMax(){
    }
    Kmedian(const Kmedian& a_k): OneMax(a_k){
        copy(a_k);
    }
    Kmedian& operator=(const Kmedian& a_k){
        if(this != &a_k){
            dest();
            OneMax::operator=(a_k);
            copy(a_k);
        }
        return *this;
    }
    virtual ~ Kmedian(){
        dest();
    }

    virtual void read_in_data(){
//        vector<>;
        string filepath="..\\dataset\\"+ProblemInstance;
        char filepathchar[200]={"\0"};
        memcpy_s(filepathchar,sizeof(filepathchar),filepath.c_str(),filepath.size());
        ifstream fileIn(filepathchar,ios::in);
        if(!fileIn){
            cout<<filepathchar<<" can not open"<<endl;
            exit(1);
        }
        string lineStr;
        while(getline(fileIn,lineStr)){
            stringstream ss(lineStr);
            string str;
            vector<double> lineArrary;
            while(getline(ss,str,',')){
                double tmp;                  //string to double
                stringstream oss;
                oss<<str;
                oss>>tmp;
                lineArrary.push_back(tmp);
            }
            lineArrary.pop_back();
            Data.push_back(lineArrary);
            Demension=lineArrary.size();
        }
        NodeSize=Data.size();
        ClusterSize=2;
        ProblemSize=static_cast<int>(NodeSize);
        fileIn.close();
//        cout<<NodeSize<<endl;
    }

    virtual double evaluation(Solution a_solu){
        double distans=0;
        double cnt1=0,cnt2=0;
        double tmp1[100]={0},tmp2[100]={0};
        for(unsigned int i=0;i<static_cast<unsigned int>(ProblemSize);i++){
            if(a_solu[i]==0){
                for(unsigned int j=0;j<Demension;j++){
                    tmp1[j]+=Data[i][j];
                }
                cnt1++;
            }else if(a_solu[i]==1){
                for(unsigned int j=0;j<Demension;j++){
                    tmp2[j]+=Data[i][j];
                }
                cnt2++;
            }
        }
        for(unsigned int j=0;j<Demension;j++){
            tmp1[j]/=cnt1;
            tmp2[j]/=cnt2;
        }
        for(unsigned int j=0;j<Demension;j++){
            distans+=pow(tmp1[j]-tmp2[j],2.0);
        }
        distans=sqrt(distans);
        return distans;
    }

protected:
    //定义数据结构
    unsigned int ClusterSize;
    unsigned int NodeSize;
    unsigned int Demension;
    std::vector<dvector> Data;

private:
    void copy(const Kmedian& a_k){
        //存储结构复制
        ClusterSize=a_k.ClusterSize;
        NodeSize=a_k.NodeSize;
        Demension=a_k.Demension;
        Data=a_k.Data;
    }

    void dest(){
    }

};

#endif // KMEDIAN_H
