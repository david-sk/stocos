///
/// \file selection_minimization.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SELECTION_MINIMIZATION_H
#define SELECTION_MINIMIZATION_H

template<class SOL>
class Selection_minimization : public Selection<SOL> {
    public:
    Selection_minimization()  {

    }

    virtual ~Selection_minimization() {

    }

    bool operator()(const SOL &s1, const SOL &s2) {
        assert(s1.fitnessIsValid());
        assert(s2.fitnessIsValid());
        
        return s1.getFitness() < s2.getFitness();
    }

    bool operator()(const SOL &s1, const SOL &s2, const unsigned int numObjectif) {
        assert(s1.fitnessIsValid(numObjectif));
        assert(s2.fitnessIsValid(numObjectif));
        
        return s1.getFitness(numObjectif) < s2.getFitness(numObjectif);
    }
};

#endif