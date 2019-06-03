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

    bool operator()(const SOL &s1, const SOL &s2) {
        assert(s1.fitnessIsValid());
        assert(s2.fitnessIsValid());

        return s2.getFitness() < s1.getFitness();
    }
};

#endif