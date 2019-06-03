///
/// \file magicSequence.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2019-05
/// \brief Knapsack Problem
///

#ifndef MAGICSEQUENCE_H
#define MAGICSEQUENCE_H

#include "problem.h"
#include "../solution/solutionArray.h"


using TYPE_CELL_MAGICSEQUENCE = int;
using SOL = SolutionArray<double, int>;
class MagicSequence : public Problem<SOL, TYPE_CELL_MAGICSEQUENCE> {
    public:
    MagicSequence() {

    }

    void loadInstance(string file) {
    }

    void full_eval(SOL &s) const {
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL &s) const {
        
    }

    protected:
};

#endif