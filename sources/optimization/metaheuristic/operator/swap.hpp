///
/// @file swap.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief Echange N case distinc
///

#ifndef OPERATION_SWAP_H
#define OPERATION_SWAP_H

#include <cassert>
#include <algorithm>
#include <vector>
#include <memory>       // std::shared_ptr std::unique_ptr

#include "atomicOperation.hpp"

namespace stocos 
{

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Swap : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
        Swap(std::mt19937 &mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem, unsigned int number_of_swap): 
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem), 
        _number_of_swap(number_of_swap) {
            N = 1;
            rid = std::make_unique<std::uniform_int_distribution<unsigned int>>(0, N-1);
        }
        
        virtual void operator()(SOL &s) {
            // Random
            if (s.sizeArray() != N) {
                N = s.sizeArray() -1;
                assert(_number_of_swap < N / 2);
                rid = std::make_unique<std::uniform_int_distribution<unsigned int>>(0, N);
            }

            // Tirage aléatoire sans remise
            std::unique_ptr<std::vector<unsigned int>> list(std::make_unique<std::vector<unsigned int>>());

            while (list->size() != (_number_of_swap * 2)) {
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
                backup.push_back(std::pair<unsigned int, TYPE_CELL>((*list)[i], s((*list)[i])));
                backup.push_back(std::pair<unsigned int, TYPE_CELL>((*list)[i+1], s((*list)[i+1])));
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
        std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid;
        std::vector<std::pair<unsigned int, TYPE_CELL>> backup;
        unsigned int _number_of_swap;
        unsigned int N;
};

}

#endif