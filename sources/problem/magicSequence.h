///
/// @file magicSequence.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief magic sequence Problem
///

#ifndef MAGICSEQUENCE_H
#define MAGICSEQUENCE_H

#include "problem.h"
#include "../solution/solutionArray.h"


using TYPE_FITNESS_MAGICSEQUENCE = double;
using TYPE_CELL_MAGICSEQUENCE = unsigned int;
using SOL = SolutionArray<TYPE_FITNESS_MAGICSEQUENCE, TYPE_CELL_MAGICSEQUENCE>;
class MagicSequence : public Problem<SOL, TYPE_FITNESS_MAGICSEQUENCE, TYPE_CELL_MAGICSEQUENCE> {
    public:
    MagicSequence() {

    }

    void loadInstance(const std::string &file) {
    }

    void full_eval(SOL &s) {
        double resultat = 0;
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {

            unsigned int count = 0;
            for (unsigned int j = 0 ; j < s.sizeArray() ; j++) {
                if (s(j) == i) {
                    count++;
                }
            }

            if (count == s(i)) {
                resultat += 1;
            }
        }

        s.setFitness(0, resultat/ static_cast<double>(s.sizeArray()));
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL &s) const {
        
    }

    protected:
};

#endif