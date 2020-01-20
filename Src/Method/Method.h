#ifndef METHOD_H
#define METHOD_H

#include <ctime>
#include <cstdlib>
#include "../Problem/Problem.h"


inline std::string getTime(){
    time_t timep;
    time (&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "[%Y-%m-%d %H:%M:%S]",localtime(&timep) );
    return tmp;
}


class Method
{
public:

    // =================================================
    // Constructors & destructor
    // =================================================
    Method(){
        MethodCode=0;
    }
    Method(const Method& a_m){
        copy(a_m);
    }
    Method& operator=(const Method& a_m){
        if (this != & a_m){
            dest();
            copy(a_m);
        }
        return *this;
    }
    virtual ~Method(){
        dest();
    }

    // =================================================
    // Member variables
    // =================================================
    int get_method_code() const{
        return MethodCode;
    }

    virtual void optimization(Problem* actp)=0;

protected:

    // ==================================================
    // Member variables
    // ==================================================
    int MethodCode;

private:

    // ===================================================
    // Help functions
    // ===================================================
    void copy(const Method& a_m){
        MethodCode=a_m.MethodCode;
    }
    void dest(){
    }
};

#endif // METHOD_H
