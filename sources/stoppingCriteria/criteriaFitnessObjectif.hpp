///
/// @file criteriaFitnessObjectif.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef CRITERIAFITNESSOBJECTIF_H
#define CRITERIAFITNESSOBJECTIF_H

#include <cassert>
#include "criteria.hpp"

namespace stocos 
{

template<typename SOL, typename TYPE_FITNESS>
class CriteriaFitnessObjectif : public Criteria<SOL, TYPE_FITNESS> {
    public:
    CriteriaFitnessObjectif(TYPE_FITNESS fitness_objectif) : 
        Criteria<SOL, TYPE_FITNESS>() {
            _number_of_objective = 1;
            _fitness_objectif = new TYPE_FITNESS[_number_of_objective];
            _fitness_objectif[0] = fitness_objectif;
    }

    CriteriaFitnessObjectif(TYPE_FITNESS *fitness_objectif, unsigned int number_of_objective) : 
        Criteria<SOL, TYPE_FITNESS>() {
            _number_of_objective = number_of_objective;
            _fitness_objectif = new TYPE_FITNESS[_number_of_objective];
            for (unsigned int i = 0 ; i < number_of_objective ; i++) {
                _fitness_objectif[i] = fitness_objectif[i];
            }
    }

    virtual ~CriteriaFitnessObjectif(){
        delete[] _fitness_objectif;
    }

    virtual bool operator()(const SOL &s) {
        assert(s.numberOfObjective() == _number_of_objective);

        if (s.fitnessIsValid()) {
            for (unsigned int i = 0 ; i < _number_of_objective ; i++) {
                if ((_fitness_objectif[i] - s.getFitness(i)) != 0) {
                    return true;
                }
            }
            return false;
        } else {
            return true;
        }
    }

    void reset() {}

    protected:
    TYPE_FITNESS *_fitness_objectif;
    unsigned int _number_of_objective;
};

}
#endif