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
    virtual unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s);
    virtual void applyMutation(SOL &s, const vector<pair<unsigned int, TYPE_CELL>> &_listOfMutations);


    protected:
        std::mt19937 &_mt_rand;
};

#endif