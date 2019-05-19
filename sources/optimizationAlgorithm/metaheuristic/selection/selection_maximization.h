///
/// \file selection_minimization.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SELECTION_MAXIMIZATION_H
#define SELECTION_MAXIMIZATION_H

template<class SOL>
class Selection_maximization : public Selection<SOL> {
    public:
    Selection_maximization() {

    }

    virtual ~Selection_maximization() {

    }

    SOL operator()(const SOL &s1, const SOL &s2) {
        assert(s1.fitnessIsValid());
        assert(s2.fitnessIsValid());
        
        if (s1.getFitness() < s2.getFitness()) {
            return s2;
        } else {
            return s1;
        }
    }
};

#endif