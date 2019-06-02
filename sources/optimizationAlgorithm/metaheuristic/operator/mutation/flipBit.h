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
#include "../../../../solution/solutionArray.h"

#include "../atomicOperation.h"

template<class SOL>
class FlipBit : public AtomicOperation<SOL> {
    public:
    FlipBit(std::mt19937 &mt_rand, unsigned int c) :
    AtomicOperation<SOL>(mt_rand),
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

    private:
        unique_ptr<uniform_real_distribution<>> urd;
        double mutation_rate;
        unsigned int N;
        const unsigned int _c;                     // < parameter c
        vector<unsigned int> backup;
};

#endif