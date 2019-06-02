///
/// \file evalOneMax.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef EVALONEMAX_H
#define EVALONEMAX_H

#include <iostream>
#include <memory>

#include "../solution/solutionArray.h"
#include "problem.h"

using namespace std;

using SOL_ONEMAX = SolutionArray<unsigned int, bool>;
class OneMax : public Problem<SOL_ONEMAX> {
    public:
    
    OneMax(unsigned int N) : _N(N) {

    }
    
    ~OneMax() {

    }

    void loadInstance(string file) {
        
    }

    unique_ptr<SOL_ONEMAX> new_solution() const {
        unique_ptr<SOL_ONEMAX> s(make_unique<SOL_ONEMAX>(_N) );
        for (unsigned int i = 0 ; i < s->sizeArray() ; i++) {
            s->operator()(i, 0);
        } 
        return move(s);
    }

    void full_eval(SOL_ONEMAX &s) const {
        unsigned int sum = 0;
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            sum += s(i);
        }
        s.setFitness(0, sum);
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL_ONEMAX &s) const {
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            s(i, 0);
        }
    }

    private:
        unsigned int _N;
};

#endif