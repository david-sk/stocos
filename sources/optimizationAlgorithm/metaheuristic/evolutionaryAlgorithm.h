///
/// \file evolutionaryAlgorithm.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///
 

#ifndef EVOLUTIONARYALGORITHM_H
#define EVOLUTIONARYALGORITHM_H

#include <random>

#include "operator/atomicOperation.h"
#include "../optimizationAlgorithm.h"
#include "../../problem/problem.h"
#include "selection/selection.h"

using namespace std;

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class EvolutionaryAlgorithm : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    EvolutionaryAlgorithm(std::mt19937 &mt_rand, 
    Statistic<SOL> &statistic,
    StoppingCriteria<SOL, TYPE_FITNESS> &stoppingCriteria,
    Problem<SOL, TYPE_FITNESS, TYPE_CELL> &problem,
    AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> &atomicOperations,
    Selection<SOL> &selection) : 
    OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, statistic, stoppingCriteria, problem),
    _atomicOperations(atomicOperations),
    _selection(selection) {
        DEBUG_TRACE("Creation EvolutionaryAlgorithm");
    }

    ~EvolutionaryAlgorithm() {
    }
    
    unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem.full_eval(solution_star);
        }

        // Initialisation de la population à partir d'une solution


        // 
        while (this->_stoppingCriteria.operator()(solution_star)) {
            this->_statistic.operator()(solution_star);

            // Evaluation des parents

            // selection des parents pour construire la population enfants

            // Mutation des enfants et construction la population parents.





            // solution_beta = solution_star;
            
            // _atomicOperations.operator()(solution_beta);
            // this->_problem.full_eval(solution_beta);
            // if (_selection(solution_beta, solution_star)) {
            //     solution_star = solution_beta;
            // }
        }

        this->_statistic.operator()(solution_star);

        return move(make_unique<SOL>(solution_star));
    }

    protected:
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> &_atomicOperations;
        Selection<SOL> &_selection;
        SOL solution_star;
        SOL solution_beta;
};

#endif

