#include <iostream>
#include <ctime>
#include <unistd.h>
#include <cstdlib>

#include "Control.h"

using namespace std;

int main(int argc, char** argv){
    if (argc < 7){
        std::cerr << "Missing parameters!\n";
        std::exit(1);
    }else{
        std::string mp=argv[1];
        if (mp != "-m"){
            std::cerr << "The option " << "\"" << argv[1] << "\"" << " is undefined!\n";
            std::exit(1);
        }
        std::string pp=argv[3];
        if (pp != "-p"){
            std::cerr << "The option " << "\"" << argv[3] << "\"" << " is undefined!\n";
            std::exit(1);
        }
        std::string pf=argv[5];
        if (pf != "-f"){
            std::cerr << "The option " << "\"" << argv[3] << "\"" << " is undefined!\n";
            std::exit(1);
        }
        std::string mname=argv[2];
        std::string pname=argv[4];
        std::string pfname=argv[6];
        Problem* actp=build_problem(pname);
        actp->chang_file_name(pfname);
        Method* actm=build_method(mname);
        actm->optimization(actp);
    }
    return 0;
}
