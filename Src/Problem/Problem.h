#ifndef PROBLEM_H
#define PROBLEM_H

#include "../DataStructure/Solution.h"
#include "../DataStructure/Matrix.h"
#include <cstdlib>
#include "../DataStructure/Sample.h"

class Problem
{
public:

    // ===========================================
    // Constructors & destructor
    // ===========================================
    Problem(){
        ProblemInstance="";
    }
    Problem(const Problem& a_p){
        copy(a_p);
    }
    Problem& operator = (const Problem& a_p){
        if (this != & a_p){
            dest();
            copy(a_p);
        }
        return *this;
    }
    virtual ~Problem(){
        dest();
    }

    // ======================================================
    // For all
    // ======================================================
    virtual void read_in_data()=0;
    virtual Solution generate_random_solution_from(Matrix Density)=0;
    virtual double evaluation(Solution a_solu)=0;

    // ======================================================
    // Intefaces for CE
    // =======================================================
    virtual Matrix get_initial_density()=0;
    virtual void update_density(Matrix& Density, Matrix emDensity, double SmoothParameter)=0;
    virtual void learning_empirical_density(Matrix& emDensity,Sample EliteSample)=0;
    virtual void chang_file_name(std::string file)
    {
       ProblemInstance=file;
    }

protected:

    // ===========================================
    // Member variables
    // ===========================================
    std::string ProblemInstance;

private:

    // ============================================
    // Help functions
    // ============================================
    void copy(const Problem& a_p){
        ProblemInstance=a_p.ProblemInstance;
    }
    void dest(){
    }
};

#endif // PROBLEM_H
