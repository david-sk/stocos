///
/// \file flipBit.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef OPERATION_FLIPBIT_H
#define OPERATION_FLIPBIT_H


#include <random>
#include <vector>
#include <memory>
#include "../../../../solution/solutionArray.h"

#include "../atomicOperation.h"

template<typename SOL, typename TYPE_CELL>
class FlipBit : public AtomicOperation<SOL, TYPE_CELL> {
    public:
    FlipBit(std::mt19937 &mt_rand, unsigned int c) :
    AtomicOperation<SOL, TYPE_CELL>(mt_rand),
    _c(c) {
        urd = make_unique<uniform_real_distribution<>>(0, 1);
        
    }
    virtual ~FlipBit() {

    }

    void operator()(SOL &s) {
        backup.clear();
        if (s.sizeArray() != N) {
            N = s.sizeArray();
            mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
            backup.reserve(N); 
        }

        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            if (urd->operator()(this->_mt_rand) < mutation_rate) {
                if (s(i) == 1) 
                    s(i, 0);
                else 
                    s(i, 1);
                backup.push_back(i);
            }
        }
    }

    void cancelMutations(SOL &s) const {
        for (unsigned int i = 0 ; i < backup.size() ; i++) {
            if (s(backup[i]) == 1) 
                s(backup[i], 0);
            else 
                s(backup[i], 1);
        }
    }

    /*unique_ptr<vector<unsigned int>> listOfMutations(const SOL &s) {
        unique_ptr<vector<unsigned int>> list(make_unique<vector<unsigned int>>());
        
        if (s.sizeArray() != N) {
            N = s.sizeArray();
            mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
        }

        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            if (urd->operator()(this->_mt_rand) < mutation_rate) {
                list->push_back(i);
            }
        }
        return move(list);
    }*/


    unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s) {
        unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> list(make_unique<vector<pair<unsigned int, TYPE_CELL>>>());
        
        if (s.sizeArray() != N) {
            N = s.sizeArray();
            mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
        }

        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            if (urd->operator()(this->_mt_rand) < mutation_rate) {
                if (s(i) == 1) 
                    list->push_back(pair<unsigned int, TYPE_CELL>(i, 0));
                else 
                    list->push_back(pair<unsigned int, TYPE_CELL>(i, 1));
                
            }
        }
        return move(list);
    }

    
    private:
        unique_ptr<uniform_real_distribution<>> urd;
        double mutation_rate;
        unsigned int N;
        const unsigned int _c;                     // < parameter c
        vector<unsigned int> backup;
};

#endif