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

#include <algorithm>    // std::find
#include <vector>       // std::vector
#include <random>
#include "../../../../solution/solutionArray.h"

#include "../atomicOperation.h"

using namespace std;

template<typename SOL, typename TYPE_CELL>
class KBit : public AtomicOperation<SOL, TYPE_CELL> {
    public:
    KBit(std::mt19937 &mt_rand, unsigned int k) :
    AtomicOperation<SOL, TYPE_CELL>(mt_rand),
    _k(k) {
        rid = make_unique<uniform_int_distribution<unsigned int>>(0, 1);
    }
    virtual ~KBit() {

    }

    void operator()(SOL &s) {
         unique_ptr<vector<unsigned int>> list = listOfMutations(s);

         for (unsigned int i = 0 ; i < list->size() ; i++) {
            if (s((*list)[i]) == 1) 
                s((*list)[i], 0);
            else 
                s((*list)[i], 1);
        }

        backup = move(list);
    }

    unique_ptr<vector<unsigned int>> listOfMutations(const SOL &s) {
        assert(_k <= s.sizeArray());

        unique_ptr<vector<unsigned int>> list(make_unique<vector<unsigned int>>());
        
        if (s.sizeArray() != N) {
            N = s.sizeArray();
            rid = make_unique<uniform_int_distribution<unsigned int>>(0, N);
            
        }

        while (list->size() != _k) {
            unsigned int element = rid->operator()(this->_mt_rand);
            auto it = std::find(list->begin(), list->end(), element);

            if (it == list->end()) {
                list->push_back(element);
            }
        }

        return move(list);
    }

    void cancelMutations(SOL &s) const {
        for (unsigned int i = 0 ; i < backup->size() ; i++) {
            if (s((*backup)[i]) == 1) 
                s((*backup)[i], 0);
            else 
                s((*backup)[i], 1);
        }
    }

    private:
        unique_ptr<uniform_int_distribution<unsigned int>> rid;
        unique_ptr<vector<unsigned int>> backup;
        unsigned int _k;
        unsigned int N;
};

#endif