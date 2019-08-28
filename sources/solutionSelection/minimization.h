///
/// @file selection_minimization.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef MINIMIZATION_H
#define MINIMIZATION_H

#include "solutionSelection.h"

template<class SOL>
class Minimization : public SolutionSelection<SOL> {
    public:
    Minimization()  {

    }

    virtual ~Minimization() {

    }

    inline bool operator()(const SOL &s1, const SOL &s2, const unsigned int numObjectif = 0) const {
        assert(s1.fitnessIsValid(numObjectif));
        assert(s2.fitnessIsValid(numObjectif));
        
        return s1.getFitness(numObjectif) < s2.getFitness(numObjectif);
    }

    inline unsigned int operator()(const Population<SOL> &p) const {
        assert(0 < p.size());
        
        double fitness = p[0].getFitness();
        unsigned int index = 0;
        for (unsigned int i = 0 ; i < p.size() ; i++) {
            if (p[i].getFitness() < fitness) {
                fitness = p[i].getFitness();
                index = i;
            }
        }
        return index;
    }
};

#endif