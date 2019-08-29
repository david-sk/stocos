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
#include "../solutionSelection/maximization.h"

using TYPE_FITNESS_MAGICSEQUENCE = double;
using TYPE_CELL_MAGICSEQUENCE = unsigned int;
using SOL_MAGICSEQUENCE = SolutionArray<TYPE_FITNESS_MAGICSEQUENCE, TYPE_CELL_MAGICSEQUENCE>;
class MagicSequence : public Problem<SOL_MAGICSEQUENCE, TYPE_FITNESS_MAGICSEQUENCE, TYPE_CELL_MAGICSEQUENCE> {
    public:
    MagicSequence() {

    }

    void loadJson(const Json::Value &config) {
    }

    void full_eval(SOL_MAGICSEQUENCE &s) {
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

    void reset_solution(SOL_MAGICSEQUENCE &s) const {
        
    }

	bool solutionSelection(const SOL_MAGICSEQUENCE &s_worst, const SOL_MAGICSEQUENCE &s_best) {
        return solution_selection(s_worst, s_best);
	}

	unsigned int solutionSelection(const Population<SOL_MAGICSEQUENCE> &p) {
        return solution_selection(p);
	}

   private:
    Maximization<SOL_MAGICSEQUENCE> solution_selection;
};

#endif