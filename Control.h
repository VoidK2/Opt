#ifndef CONTROL_H
#define CONTROL_H
/*
 * Method   Problem
 * CE       OneMax
 *          Knapsack
 *          k-Median*
 */


#include "Src/Problem/Problem.h"
#include "Src/Problem/OneMax.h"
#include "Src/Problem/Knapsack.h"
#include "Src/Problem/Kmedian.h"
#include "Src/Method/Method.h"
#include "Src/Method/CrossEntropy.h"

inline Method* build_method(std::string mname){
    Method *actm;
    if (mname == "CE"){
        actm = new CrossEntropy();
    }else{
        std::cerr << "Error! The selected method is undefined!\n";
        std::exit(1);
    }
    return actm;
}

inline Problem* build_problem(std::string pname){
    Problem *actp;
    if (pname == "OneMax"){
        int psize;
        std::cout << getTime() << " Please type in a problem size: \n";
        std::cin >> psize;
        while (psize <=0){
            std::cout << getTime() << " Error! The problem size must be larger than 0!\n";
            std::cout << getTime() << " Please reenter in a problem size: \n";
            std::cin >> psize;
        }
        std::cout << getTime() << " The selected problem is OneMax with size " << psize << "!" << std::endl;
        actp = new OneMax(psize);
    }else if (pname == "Knapsack"){
        actp= new Knapsack();
    }else if (pname == "Kmedian"){
        actp= new Kmedian();
    }else{
        std::cout << "The selected problem is undefined!\n";
        std::exit(1);
    }
    return actp;
}

#endif // CONTROL_H
