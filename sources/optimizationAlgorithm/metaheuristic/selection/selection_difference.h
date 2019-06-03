///
/// \file selection_minimization.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SELECTION_DIFFERENCE_H
#define SELECTION_DIFFERENCE_H

#include<cmath>

template<class SOL>
class Selection_difference : public Selection<SOL> {
    public:
    Selection_difference(const double fitnessObjectif) : 
        _fitnessObjectif(fitnessObjectif) {

    }

    virtual ~Selection_difference() {

    }

    bool operator()(const SOL &s1, const SOL &s2) {
        assert(s1.fitnessIsValid());
        assert(s2.fitnessIsValid());
        return abs(_fitnessObjectif - s1.getFitness()) < abs(_fitnessObjectif - s2.getFitness());
    }
    
    private:
    const double _fitnessObjectif;
};

#endif