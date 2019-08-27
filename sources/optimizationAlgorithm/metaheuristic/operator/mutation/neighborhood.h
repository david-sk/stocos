///
/// @file neighborhood.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include <random>
#include <memory>       // std::shared_ptr std::unique_ptr

#include "../atomicOperation.h"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Neighborhood : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    Neighborhood(std::mt19937 &mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem) :
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem) {

    }

    virtual ~Neighborhood() {

    }

    virtual void operator()(SOL &s) {
        std::cerr<<"Not implemented"<<std::endl;
        exit(EXIT_FAILURE);
    }

    virtual std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s) {
        std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> list(std::make_unique<std::vector<std::pair<unsigned int, TYPE_CELL>>>());
        SOL s1 = s;
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            if (s(i) == 1) {
                s1(i, 0);
                list->push_back(std::pair<unsigned int, SOL>(i, s1));
                s1(i, 1);
            } else {
                s1(i, 1);
                list->push_back(std::pair<unsigned int, SOL>(i, s1));
                s1(i, 0);
            }
        }

        return std::move(list);
    }

    virtual void applyOperator(SOL &s, const std::vector<std::pair<unsigned int, TYPE_CELL>> &_listOfMutations) {
        std::cerr<<"Not implemented"<<std::endl;
        exit(EXIT_FAILURE);
    }


    protected:
};

#endif