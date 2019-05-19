///
/// \file operation_FlipBit.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef OPERATION_FLIPBIT_H
#define OPERATION_FLIPBIT_H


#include <random>
#include "../../../../solution/solutionArray.h"

#include "../atomicOperation.h"

template<class SOL>
class Mutation_FlipBit : public AtomicOperation<SOL> {
    public:
    Mutation_FlipBit(std::mt19937 &mt_rand, unsigned int c) :
    AtomicOperation<SOL>(mt_rand) {

    }
    virtual ~Mutation_FlipBit() {

    }

    void operator()(SOL &s) {
        uniform_int_distribution<unsigned int> rid(0, s.sizeArray() - 1);

        unsigned int ret = rid(this->_mt_rand);


        if (s(ret) == 1) 
            s(ret, 0);
        else 
            s(ret, 1);
    }

    private:
    
};

#endif