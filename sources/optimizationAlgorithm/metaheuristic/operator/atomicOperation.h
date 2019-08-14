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

#include "../../optimizationAlgorithm.h"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class AtomicOperation  {
    public:
    AtomicOperation(std::mt19937 &mt_rand) : 
        _mt_rand(mt_rand) {

    }

    virtual ~AtomicOperation() {

    }

    virtual void operator()(SOL &s) = 0;
    virtual std::unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s) {
        cerr<<"Not implemented"<<endl;
        exit(EXIT_FAILURE);
    }
    virtual void applyOperator(SOL &s, const vector<pair<unsigned int, TYPE_CELL>> &_listOfMutations) {
        cerr<<"Not implemented"<<endl;
        exit(EXIT_FAILURE);
    }


    protected:
        std::mt19937 &_mt_rand;
};

#endif