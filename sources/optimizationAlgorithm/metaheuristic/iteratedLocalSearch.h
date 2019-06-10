///
/// \file IteratedLocalSearch.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///
 

#ifndef ITERATEDLOCALSEARCH_H
#define ITERATEDLOCALSEARCH_H

#include <random>

#include "operator/atomicOperation.h"
#include "../optimizationAlgorithm.h"
#include "../../problem/problem.h"
#include "selection/selection.h"

using namespace std;
// Exploration-Exploitation
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class IteratedLocalSearch : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    IteratedLocalSearch(std::mt19937 &mt_rand, 
    Statistic<SOL> &statistic,
    StoppingCriteria<SOL, TYPE_FITNESS> &stoppingCriteria,
    Problem<SOL, TYPE_FITNESS, TYPE_CELL> &problem,
    AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> &exploration,
    OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> &exploitation,
    Selection<SOL> &selection) : 
    OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, statistic, stoppingCriteria, problem),
    _exploration(exploration),
    _exploitation(exploitation),
    _selection(selection) {
        DEBUG_TRACE("Creation IteratedLocalSearch");
    }

    ~IteratedLocalSearch() {
    }
    
    unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem.full_eval(solution_star);
        }
        
        while (this->_stoppingCriteria.operator()(solution_star)) {
            this->_statistic.operator()(solution_star);

            solution_beta = solution_star;
            
            _exploration(solution_beta);
            unique_ptr<SOL> solution_beta_beta = _exploitation(solution_beta);

            this->_problem.full_eval(solution_beta);
            if (_selection(*solution_beta_beta, solution_star)) {
                solution_star = solution_beta;
            }
        }

        this->_statistic.operator()(solution_star);

        return move(make_unique<SOL>(solution_star));
    }

    protected:
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> &_exploration;
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> &_exploitation;
        Selection<SOL> &_selection;
        SOL solution_star;
        SOL solution_beta;
};

#endif