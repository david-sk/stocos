///
/// \file swap.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2019-05
/// \brief Echange N case distinc
///

#ifndef OPERATION_SWAP_H
#define OPERATION_SWAP_H

#include <cassert>
#include <algorithm>
#include "atomicOperation.h"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Swap : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
        Swap(std::mt19937 &mt_rand, unsigned int nbSwap): 
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand), 
        _nbSwap(nbSwap) {
            N = 1;
            rid = make_unique<uniform_int_distribution<unsigned int>>(0, N);
        }
        
        virtual void operator()(SOL &s) {
            // Random
            if (s.sizeArray() != N) {
                N = s.sizeArray();
                assert(_nbSwap < N / 2);
                rid = make_unique<uniform_int_distribution<unsigned int>>(0, N);
            }

            // Tirage aléatoire sans remise
            unique_ptr<vector<unsigned int>> list(make_unique<vector<unsigned int>>());

            while (list->size() != (_nbSwap * 2)) {
                unsigned int element = rid->operator()(this->_mt_rand);

                bool findElement = false;
                for (unsigned int i = 0 ; i < list->size() ; i++) {
                    if ((*list)[i] == element) {
                        findElement = true;
                    }
                }
                if (!findElement) {
                    list->push_back(element);
                }
            }
            
            // Swap
            backup.clear();
            TYPE_CELL temporay;
            for (unsigned int i = 0 ; i < list->size() ; i+=2) {
                backup.push_back(pair<unsigned int, TYPE_CELL>((*list)[i], s((*list)[i])));
                backup.push_back(pair<unsigned int, TYPE_CELL>((*list)[i+1], s((*list)[i+1])));
                temporay = s((*list)[i]);
                s((*list)[i], s((*list)[i+1]));
                s((*list)[i + 1], temporay);
                
            }
        }

        void cancelMutations(SOL &s) const {
            for (unsigned int i = 0 ; i < backup.size() ; i++) {
                s(backup[i].first, backup[i].second);
            }
        }       

    private:
        unique_ptr<uniform_int_distribution<unsigned int>> rid;
        vector<pair<unsigned int, TYPE_CELL>> backup;
        unsigned int _nbSwap;
        unsigned int N;
};

#endif