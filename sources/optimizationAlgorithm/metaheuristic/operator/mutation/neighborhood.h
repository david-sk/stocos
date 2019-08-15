///
/// @file AtomicOperations.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef NEIGHBORHOOD_H
#define NEIGHBORHOOD_H

#include <random>

#include "../atomicOperation.h"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Neighborhood : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    Neighborhood(std::mt19937 &mt_rand) :
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand) {

    }

    virtual ~Neighborhood() {

    }

    virtual void operator()(SOL &s) {
        cerr<<"Not implemented"<<endl;
        exit(EXIT_FAILURE);
    }

    virtual std::unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s) {
        std::unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> list(make_unique<vector<pair<unsigned int, TYPE_CELL>>>());
        SOL s1 = s;
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            if (s(i) == 1) {
                s1(i, 0);
                list->push_back(pair<unsigned int, SOL>(i, s1));
                s1(i, 1);
            } else {
                s1(i, 1);
                list->push_back(pair<unsigned int, SOL>(i, s1));
                s1(i, 0);
            }
        }

        return move(list);
    }

    virtual void applyOperator(SOL &s, const vector<pair<unsigned int, TYPE_CELL>> &_listOfMutations) {
        cerr<<"Not implemented"<<endl;
        exit(EXIT_FAILURE);
    }


    protected:
};

#endif