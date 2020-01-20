#ifndef SAMPLE_H
#define SAMPLE_H

#include <iostream>
#include <list>
#include <cstdlib>
#include "Solution.h"

class Sample
{
public:

    // ===============================================
    // Constructors & destuctor
    // ===============================================
    Sample(){
        SampleSize=0;
        if (static_cast<int>(Data.size()) !=0){
            Data.clear();
        }
    }
    Sample(const Sample& a_sam){
        copy(a_sam);
    }
    Sample& operator=(const Sample& a_sam){
        if (this != &a_sam){
            dest();
            copy(a_sam);
        }
        return *this;
    }
    virtual ~Sample(){
        dest();
    }

    // ==============================================
    // Member functions
    // ==============================================
    void print() const{
        for (std::list<SolutionRecord>::const_iterator it = Data.begin(); it != Data.end(); ++it){
            for (unsigned int i=0; i< it->first.size(); i++){
                std::cout << it->first[i] << " ";
            }
            std::cout << it->second << std::endl;
        }
    }
    SolutionRecord get_ith_solution(int i) const{
        if (i <0 || i>=SampleSize){
            std::cerr << "The index is out of range!\n";
            std::exit(1);
        }
        std::list<SolutionRecord>::const_iterator it=Data.begin();
        std::advance(it,i);
        return *it;
    }
    void change_ith_solution(int i, SolutionRecord a_solu){
        if (i <0 || i>=SampleSize){
            std::cerr << "The index is out of range!\n";
            std::exit(1);
        }
        std::list<SolutionRecord>::iterator it=Data.begin();
        std::advance(it,i);
        *it=a_solu;
    }
    void add_solution_decreasing(SolutionRecord a_solu){
        if (SampleSize<=0){
            Data.push_back(a_solu);
        }else{
            std::list<SolutionRecord>::iterator it=Data.begin();
            while(it->second>a_solu.second && it !=Data.end()){
                ++it;
            }
            Data.insert(it,a_solu);
        }
        SampleSize +=1;
    }
    void add_solution_increasing(SolutionRecord a_solu){
        if (SampleSize<=0){
            Data.push_back(a_solu);
        }else{
            std::list<SolutionRecord>::iterator it=Data.begin();
            while(it->second<a_solu.second && it !=Data.end()){
                ++it;
            }
            Data.insert(it,a_solu);
        }
        SampleSize +=1;
    }
    void push_back(SolutionRecord a_solu){
        Data.push_back(a_solu);
        SampleSize +=1;
    }
    void push_front(SolutionRecord a_solu){
        Data.push_front(a_solu);
        SampleSize +=1;
    }
    void pop_back(){
        Data.pop_back();
        SampleSize -=1;
    }
    void delete_ith_solution(int i){
        if (i <0 || i>=SampleSize){
            std::cerr << "The index is out of range!\n";
            std::exit(1);
        }
        std::list<SolutionRecord>::iterator it=Data.begin();
        std::advance(it,i);
        Data.erase(it);
        SampleSize -=1;
    }
    int get_samplesize() const{
        return SampleSize;
    }
    void clear(){
        Data.clear();
        SampleSize=0;
    }

protected:

    // ===============================================
    // Member variables
    // ===============================================
    int SampleSize;
    std::list<SolutionRecord> Data;

private:

    // ================================================
    // Helpful functions
    // ================================================
    void copy(const Sample& a_sam){
        SampleSize=a_sam.SampleSize;
        Data=a_sam.Data;
    }
    void dest(){
    }
};

#endif // SAMPLE_H
