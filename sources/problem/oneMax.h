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

#include "../solution/solutionArray.h"
#include "problem.h"

template<class SOL>
class OneMax : public Problem<SOL> {
    public:
    
    OneMax() {

    }
    
    ~OneMax() {

    }

    void full_eval(SOL &s) const {
        unsigned int sum = 0;
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            sum += s(i);
        }
        s.setFitness(0, sum);
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL &s) const {
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            s(i, 0);
        }
    }

    private:
};

#endif