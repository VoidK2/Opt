#ifndef ONEMAX_H
#define ONEMAX_H

#include "Problem.h"
#include <cstdlib>
#include "../RNG/RNG.h"

class OneMax
        : public Problem
{
public:

    // =============================================
    // Constructors & destructor
    // =============================================
    OneMax(): Problem(){
    }
    OneMax(int Psize): Problem(){
        ProblemSize=Psize;
    }
    OneMax(const OneMax& a_o): Problem(a_o){
        copy(a_o);
    }
    OneMax& operator =(const OneMax& a_o){
        if (this != &a_o){
            dest();
            Problem::operator =(a_o);
            copy(a_o);
        }
        return *this;
    }
    virtual ~OneMax(){
        dest();
    }

    // ======================================================
    // For all
    // ======================================================
    virtual void read_in_data(){
    }
    virtual Solution generate_random_solution_from(Matrix Density){
        Solution r;
        for (int i=0;i<ProblemSize;i++){
            if (rng()<Density.get_value(0,i)){
                r.push_back(1);
            }else{
                r.push_back(0);
            }
        }
        return r;
    }
    virtual double evaluation(Solution a_solu){
        double r=0;
        for (int i=0;i<ProblemSize;i++){
            r +=a_solu[i];
        }
        return r;
    }

    // ======================================================
    // Intefaces for CE
    // =======================================================
    virtual Matrix get_initial_density(){
        Matrix M(1,ProblemSize,0.5);
        return M;
    }
    virtual void update_density(Matrix& Density, Matrix emDensity, double SmoothParameter){
        for (int i=0; i<ProblemSize; i++){
            Density.change_value(0,i,
                                 (1-SmoothParameter)*Density.get_value(0,i)+SmoothParameter*emDensity.get_value(0,i));
        }
    }
    virtual void learning_empirical_density(Matrix& emDensity, Sample EliteSample){
        if (emDensity.get_rowsize() !=1 || emDensity.get_columnsize()!= ProblemSize){
            std::cerr << "The empirical density for learning has a wrong size!\n";
            std::exit(1);
        }
        double p;
        for (int i=0; i<ProblemSize; i++){
            p=0;
            for (int j=0; j<EliteSample.get_samplesize(); j++){
                p += EliteSample.get_ith_solution(j).first[i];
            }
            p=p/EliteSample.get_samplesize();
            emDensity.change_value(0,i,p);
        }
    }

protected:

    // =============================================
    // Member variables
    // =============================================
    int ProblemSize;

private:

    // =============================================
    // Help functions
    // =============================================
    void copy(const OneMax& a_o){
        ProblemSize=a_o.ProblemSize;
    }
    void dest(){
    }
};

#endif // ONEMAX_H
