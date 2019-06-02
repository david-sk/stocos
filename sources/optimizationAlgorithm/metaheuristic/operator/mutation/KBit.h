///
/// \file kBit.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2019-05
/// \brief exactly mute K bits distinct
///

#ifndef OPERATION_KBIT_H
#define OPERATION_KBIT_H


#include <random>
#include "../../../../solution/solutionArray.h"

#include "../atomicOperation.h"

template<class SOL>
class KBit : public AtomicOperation<SOL> {
    public:
    FlipBit(std::mt19937 &mt_rand, unsigned int c) :
    AtomicOperation<SOL>(mt_rand) {
        rid = make_unique<uniform_int_distribution<unsigned int>>(0, 1);
    }
    virtual ~FlipBit() {

    }

    void operator()(SOL &s) {
        if (s.sizeArray() - 1 != rid->max())
            rid = make_unique<uniform_int_distribution<unsigned int>>(0, s.sizeArray() - 1);
        

        unsigned int ret = rid->operator()(this->_mt_rand);

        if (s(ret) == 1) 
            s(ret, 0);
        else 
            s(ret, 1);
    }

    private:
        unique_ptr<uniform_int_distribution<unsigned int>> rid;
};

#endif