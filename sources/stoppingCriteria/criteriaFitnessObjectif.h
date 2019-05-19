///
/// \file criteriaFitnessObjectif.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef CRITERIAFITNESSOBJECTIF_H
#define CRITERIAFITNESSOBJECTIF_H

#include <cassert>
#include "criteria.h"


template<class SOL>
class CriteriaFitnessObjectif : public Criteria<SOL> {
    public:
    CriteriaFitnessObjectif(unsigned int fitnessObjectif) : 
        Criteria<SOL>() {
            _numberOfObjective = 1;
            _fitnessObjectif = new unsigned int[_numberOfObjective];
            _fitnessObjectif[0] = fitnessObjectif;
    }

    CriteriaFitnessObjectif(unsigned int *fitnessObjectif, unsigned int numberOfObjective) : 
        Criteria<SOL>() {
            _numberOfObjective = numberOfObjective;
            _fitnessObjectif = new unsigned int[_numberOfObjective];
            for (unsigned int i = 0 ; i < numberOfObjective ; i++) {
                _fitnessObjectif[0] = fitnessObjectif;
            }
    }


    virtual ~CriteriaFitnessObjectif(){
        delete[] _fitnessObjectif;
    }

    virtual bool operator()(const SOL &s) {
        assert(s.numberOfObjective() == _numberOfObjective);
        // Besion de la définir pour le multi-objectifs
        if (s.fitnessIsValid()) {
            return s.getFitness() < _fitnessObjectif[0];
        } else {
            return true;
        }
        
    }

    protected:
    unsigned int *_fitnessObjectif;
    unsigned int _numberOfObjective;
};

#endif