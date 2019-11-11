///
/// @file atomicOperation.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef ATOMICOPERATOR_H
#define ATOMICOPERATOR_H

#include <memory>       // std::shared_ptr std::unique_ptr
#include <random>

#include "../../optimizationAlgorithm.hpp"

namespace stocos 
{

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class AtomicOperation  {
    public:
    AtomicOperation(std::mt19937 &mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem) : 
        _mt_rand(mt_rand),
        _problem(problem) {

    }

    virtual ~AtomicOperation() {

    }

    virtual void operator()(SOL &s) = 0;
    virtual std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s) {
        std::cerr<<"Not implemented"<<std::endl;
        exit(EXIT_FAILURE);
    }
    virtual void applyOperator(SOL &s, const std::vector<std::pair<unsigned int, TYPE_CELL>> &_listOfMutations) {
        std::cerr<<"Not implemented"<<std::endl;
        exit(EXIT_FAILURE);
    }


    protected:
        std::mt19937 &_mt_rand;
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
};

}
#endif