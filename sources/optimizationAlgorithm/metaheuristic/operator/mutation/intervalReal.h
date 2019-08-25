///
/// @file flipBit.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief intervalle real [a,b]
///

#ifndef OPERATION_INTERVALREAL_H
#define OPERATION_INTERVALREAL_H

#include <random>
#include <vector>
#include <memory>
#include "../../../../solution/solutionArray.h"

#include "../atomicOperation.h"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class IntervalReal : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    IntervalReal(std::mt19937 &mt_rand, unsigned int c, double a, double b) :
    AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand),
    _c(c),
    _a(a),
    _b(b) {
        urd_0_1 = std::make_unique<std::uniform_real_distribution<>>(0, 1);
        urd = std::make_unique<std::uniform_real_distribution<>>(a, b);
        
    }
    virtual ~IntervalReal() {

    }

    void operator()(SOL &s) {
        if (s.sizeArray() != N) {
            N = s.sizeArray();
            mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
            backup.reserve(N); 
        }

        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            if (urd_0_1->operator()(this->_mt_rand) < mutation_rate) {
                s(i, s(i) + urd->operator()(this->_mt_rand));
            }
        }
    }

    // void cancelMutations(SOL &s) const {
    //     for (unsigned int i = 0 ; i < backup.size() ; i++) {
    //         if (s(backup[i]) == 1) 
    //             s(backup[i], 0);
    //         else 
    //             s(backup[i], 1);
    //     }
    // }

    // std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s) {
    //     std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> list(std::make_unique<std::vector<std::pair<unsigned int, TYPE_CELL>>>());
        
    //     if (s.sizeArray() != N) {
    //         N = s.sizeArray();
    //         mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
    //     }

    //     for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
    //         if (urd->operator()(this->_mt_rand) < mutation_rate) {
    //             if (s(i) == 1) 
    //                 list->push_back(std::pair<unsigned int, TYPE_CELL>(i, 0));
    //             else 
    //                 list->push_back(std::pair<unsigned int, TYPE_CELL>(i, 1));
                
    //         }
    //     }
    //     return std::move(list);
    // }

    // void applyOperator(SOL &s, const std::vector<std::pair<unsigned int, TYPE_CELL>> &_listOfMutations) {
    //     backup.clear();
    //     for (unsigned int i = 0 ; i < _listOfMutations.size() ; i++) {
    //         s(_listOfMutations[i].first, _listOfMutations[i].second);
    //         backup.push_back(i);
    //     }
    // }

    
    private:
        const unsigned int _c;                     // < Nombre de case à mute / arraySize
        const unsigned int _a;                     // < Lower bound
        const unsigned int _b;                     // < Upper bollard
        std::unique_ptr<std::uniform_real_distribution<>> urd_0_1;
        std::unique_ptr<std::uniform_real_distribution<>> urd;
        double mutation_rate;
        unsigned int N;
        std::vector<unsigned int> backup;
};

#endif