#ifndef CROSSENTROPY_H
#define CROSSENTROPY_H

#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Method.h"
#include <iomanip>

class CrossEntropy
        : public Method
{
public:

    // ================================================
    // Constructors & destructor
    // ================================================
    CrossEntropy(): Method(){
        MethodCode=1;
        std::cout << getTime() << " You are using CE algorithm!\n";
        require();
    }
    CrossEntropy(const CrossEntropy& a_ce): Method(a_ce){
        copy(a_ce);
    }
    CrossEntropy& operator =(const CrossEntropy& a_ce){
        if (this != &a_ce){
            dest();
            Method::operator =(a_ce);
            copy(a_ce);
        }
        return *this;
    }
    virtual ~CrossEntropy(){
        dest();
    }

    // =================================================
    // Member functions
    // =================================================
    virtual void initialization(Problem* actp){
        actp->read_in_data();
        Density=actp->get_initial_density();
        Best_So_Far.first=actp->generate_random_solution_from(Density);
        Best_So_Far.second=actp->evaluation(Best_So_Far.first);
    }

    virtual void sampling(Problem* actp){
        // The default proble is an maximization problem
        SolutionRecord a_solu;
        for (int i=0; i<EliteSize; i++){
            a_solu.first=actp->generate_random_solution_from(Density);
            a_solu.second=actp->evaluation(a_solu.first);
            CurrentSample.add_solution_decreasing(a_solu);
        }

        for (int i=EliteSize; i<SampleSize; i++){
            a_solu.first=actp->generate_random_solution_from(Density);
            a_solu.second=actp->evaluation(a_solu.first);
            if (a_solu.second>CurrentSample.get_ith_solution(EliteSize-1).second){
                CurrentSample.pop_back();
                CurrentSample.add_solution_decreasing(a_solu);
            }
        }

        if (Best_So_Far.second<CurrentSample.get_ith_solution(0).second){
            Best_So_Far=CurrentSample.get_ith_solution(0);
        }
    }

    virtual void optimization(Problem* actp){
        initialization(actp);
        std::cout << getTime() << " Optimization starts!\n";

        Matrix emDensity=actp->get_initial_density();

        clock_t startTime,endTime; // Timing

        startTime=clock();



        std::cout << "Progessing: " << std::setprecision(2) << std::setw(5) << 0
                  << "\%, Fitness: " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << std::setw(15) << Best_So_Far.second << std::flush << "\r";
        //sleep(0.2);
        for (int i=0; i<MaxIteration; i++){
            sampling(actp);
            actp->learning_empirical_density(emDensity,CurrentSample);
            actp->update_density(Density,emDensity,SmoothParameter);
            std::cout << "Progressing: " << std::setprecision(2) << std::setw(5) << (100.0*i)/MaxIteration
                      << "\%, Fitness: " << std::setiosflags(std::ios::fixed) << std::setprecision(2) << std::setw(15) << Best_So_Far.second << std::flush << "\r";
            //sleep(0.2);
            CurrentSample.clear();
        }

        endTime=clock();

        std::cout << getTime() << " The optimization consumes "
                  << static_cast<double>(endTime-startTime)/CLOCKS_PER_SEC << " s!" << std::endl;
        std::cout << getTime() << " The optimal value found is "
                  << Best_So_Far.second << std::endl;
        std::cout << getTime() << " The best solution found is:\n";
        for( unsigned int i=0; i<Best_So_Far.first.size(); i++ ){
//            if( Best_So_Far.first[i] ==1 ){
//                std::cout << i << " ";
//            }
            std::cout<<Best_So_Far.first[i]<<" ";
        }
        std::cout << std::endl;
    }

protected:

    // ================================================
    // Member variables
    // ================================================
    Matrix Density;
    int EliteSize;
    int SampleSize;
    Sample CurrentSample; // The elite solutions only
    double SmoothParameter;
    int MaxIteration;
    SolutionRecord Best_So_Far;

private:

    // ===================================================
    // Help functions
    // ===================================================
    void copy(const CrossEntropy& a_ce){
        Density=a_ce.Density;
        EliteSize=a_ce.EliteSize;
        SampleSize=a_ce.SampleSize;
        CurrentSample=a_ce.CurrentSample;
        SmoothParameter=a_ce.SmoothParameter;
        MaxIteration=a_ce.MaxIteration;
        Best_So_Far=a_ce.Best_So_Far;
    }
    void dest(){
    }
    void require(){
        std::cout << getTime() << " Please type in the sample size: \n";
        std::cin >> SampleSize;
        while (SampleSize <2){
            std::cout << getTime() << " Error! The sample size is at least 2!\n";
            std::cout << getTime() << " Please reenter a sample size: \n";
            std::cin >> SampleSize;
        }
        std::cout << getTime() << " Please choose an elite size: \n";
        std::cin >> EliteSize;
        while (EliteSize <=0 || EliteSize>SampleSize) {
            std::cout << getTime() << " Error! The elite size is in (0," << SampleSize << "]\n";
            std::cout << getTime() << " Please reenter an elite size: \n";
            std::cin >> EliteSize;
        }
        std::cout << getTime() << " Please choose a smooth parameter: \n";
        std::cin >> SmoothParameter;
        while(SmoothParameter<0 || SmoothParameter>1){
            std::cout << getTime() << " Error! The smooth parameter should be in [0,1]!\n";
            std::cout << getTime() << " Please reenter a smooth parameter: \n";
            std::cin >> SmoothParameter;
        }
        std::cout << getTime() << " Please choose an initeration number: \n";
        std::cin >> MaxIteration;
        while (MaxIteration<=0) {
            std::cout << getTime() << " Error! The iteration number must be positive!\n";
            std::cout << getTime() << " Please reenter an iteration number: \n";
            std::cin >> MaxIteration;
        }
        std::cout << getTime() << " Your setting of the CE algorithm is as follows:\n";
        std::cout << getTime() << " Sample Size: " << SampleSize << std::endl;
        std::cout << getTime() << " Elite Size: " << EliteSize << std::endl;
        std::cout << getTime() << " Smooth Parameter: " << SmoothParameter << std::endl;
        std::cout << getTime() << " Max Iteration Number: " << MaxIteration << std::endl;
    }
};

#endif // CROSSENTROPY_H
