#ifndef RNG_H
#define RNG_H

#include <cstdlib>


inline double rng(){
        return static_cast<double>(std::rand())/RAND_MAX;
}


#endif // RNG_H
