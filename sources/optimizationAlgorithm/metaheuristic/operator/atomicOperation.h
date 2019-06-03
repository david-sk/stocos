///
/// \file AtomicOperations.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef ATOMICOPERATOR_H
#define ATOMICOPERATOR_H

#include <random>

template<typename SOL, typename TYPE_CELL>
class AtomicOperation  {
    public:
    AtomicOperation(std::mt19937 &mt_rand) : _mt_rand(mt_rand) {

    }

    virtual ~AtomicOperation() {

    }

    virtual void operator()(SOL &s) = 0;


    protected:
        std::mt19937 &_mt_rand;
};

#endif