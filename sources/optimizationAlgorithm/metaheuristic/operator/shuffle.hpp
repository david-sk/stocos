///
/// @file shuffle.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief 
///

#ifndef OPERATION_SHUFFLE_H
#define OPERATION_SHUFFLE_H

#include <cassert>
#include <algorithm>    
#include <memory>       // std::shared_ptr std::unique_ptr
#include <algorithm>    // std::random_shuffle

#include "atomicOperation.hpp"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Shuffle : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
        Shuffle(std::mt19937 &mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem): 
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem)  {
            
        }

        ~Shuffle() {

        }
        
        virtual void operator()(SOL &s) {
            if (index.size() != s.sizeArray()) {
                index.clear();
                for(unsigned int i = 0 ; i < s.sizeArray() ; i++)
                    index.push_back(i);
            }

            std::shuffle(index.begin(), index.end(), this->_mt_rand);
            for(unsigned int i = 0 ; i < s.sizeArray() ; i++) {
                TYPE_CELL tmp = s(i);
                s(i, s(index[i]));
                s(index[i], tmp); 
            }
        }

    private:
        std::vector<TYPE_CELL> index;
};

#endif