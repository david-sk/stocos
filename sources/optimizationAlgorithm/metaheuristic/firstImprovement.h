///
/// \file firstImprovement.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///
 

#ifndef FIRSTIMPROVEMENT_H
#define FIRSTIMPROVEMENT_H

#include <random>

#include "operator/atomicOperation.h"
#include "../optimizationAlgorithm.h"
#include "../../problem/problem.h"
#include "selection/selection.h"

using namespace std;

template<typename SOL, typename TYPE_CELL>
class FirstImprovement : public OptimizationAlgorithm<SOL, TYPE_CELL> {
    public:
    FirstImprovement(std::mt19937 &mt_rand, 
    Statistic<SOL> &statistic,
    StoppingCriteria<SOL> &stoppingCriteria,
    Problem<SOL, TYPE_CELL> &problem,
    AtomicOperation<SOL, TYPE_CELL> &atomicOperations,
    Selection<SOL> &selection,
    unsigned int N) : 
    OptimizationAlgorithm<SOL, TYPE_CELL>(mt_rand, statistic, stoppingCriteria, problem),
    _atomicOperations(atomicOperations),
    _selection(selection) {
        DEBUG_TRACE("Creation FirstImprovement");
        rid = new uniform_int_distribution<unsigned int>(0, N-1);
    }

    ~FirstImprovement() {
        delete rid;
    }
    
    unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem.full_eval(solution_star);
        }
        
        while (this->_stoppingCriteria.operator()(solution_star)) {
            this->_statistic.operator()(solution_star);

            solution_beta = solution_star;
            
            _atomicOperations.operator()(solution_beta);
            this->_problem.full_eval(solution_beta);
            if (_selection(solution_beta, solution_star)) {
                solution_star = solution_beta;
            }
        }

        this->_statistic.operator()(solution_star);

        return move(make_unique<SOL>(solution_star));
    }

    protected:
        uniform_int_distribution<unsigned int> *rid;
        AtomicOperation<SOL, TYPE_CELL> &_atomicOperations;
        Selection<SOL> &_selection;
        SOL solution_star;
        SOL solution_beta;
};

#endif