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

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class KBit : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    KBit(std::mt19937 &mt_rand, unsigned int k) :
    AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand),
    _k(k) {
        N = 1;
        rid = make_unique<uniform_int_distribution<unsigned int>>(0, 1);
    }
    virtual ~KBit() {

    }

    void operator()(SOL &s) {
        backup.clear();
        std::unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> list = listOfMutations(s);
        for (unsigned int i = 0 ; i < list->size() ; i++) {
            s((*list)[i].first, (*list)[i].second);
            backup.push_back((*list)[i].first);
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

    std::unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL &s) {
        assert(_k <= s.sizeArray());

        std::unique_ptr<vector<pair<unsigned int, TYPE_CELL>>> list(make_unique<vector<pair<unsigned int, TYPE_CELL>>>());
        
        if (s.sizeArray() != N) {
            N = s.sizeArray();
            rid = make_unique<uniform_int_distribution<unsigned int>>(0, N);
        }

        while (list->size() != _k) {
            unsigned int element = rid->operator()(this->_mt_rand);
            bool findElement = false;
            for (unsigned int i = 0 ; i < list->size() ; i++) {
                if ((*list)[i].first == element) {
                    findElement = true;
                }
            } 
            
            if (!findElement) {
                if (s(element) == 1)
                    list->push_back(pair<unsigned int, TYPE_CELL>(element, 0));
                 else
                    list->push_back(pair<unsigned int, TYPE_CELL>(element, 1));
            }
        }

        return move(list);
    }

    void applyOperator(SOL &s, const vector<pair<unsigned int, TYPE_CELL>> &_listOfMutations) {
        backup.clear();
        for (unsigned int i = 0 ; i < _listOfMutations.size() ; i++) {
            s(_listOfMutations[i].first, _listOfMutations[i].second);
            backup.push_back(_listOfMutations[i].first);
        }
    }


    private:
        std::unique_ptr<uniform_int_distribution<unsigned int>> rid;
        vector<unsigned int> backup;
        unsigned int _k;
        unsigned int N;
};

#endif