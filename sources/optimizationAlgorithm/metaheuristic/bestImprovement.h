///
/// \file bestImprovement.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef BESTIMPROVEMENT_H
#define BESTIMPROVEMENT_H

#include <random>

#include "../optimizationAlgorithm.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "../../problem/problem.h"
#include "operator/atomicOperation.h"
#include "operator/mutation/neighborhood.h"
#include "selection/selection.h"


using namespace std;

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class BestImprovement : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    BestImprovement(std::mt19937 &mt_rand,
        Statistic<SOL> &statistic,
        StoppingCriteria<SOL, TYPE_FITNESS> &stoppingCriteria,
        Problem<SOL, TYPE_FITNESS, TYPE_CELL> &problem,
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> &atomicOperations,
        Selection<SOL> &selection) :
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, statistic, stoppingCriteria, problem),
        _selection(selection) {
        DEBUG_TRACE("Creation BestImprovement");
        _atomicOperations = new Neighborhood<SOL, TYPE_FITNESS, SOL>(mt_rand);
    }

    virtual ~BestImprovement() {
    }
    
    unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;

        if (!solution_star.fitnessIsValid()) {
           this-> _problem.full_eval(solution_star);
        }

        #ifdef DEBUG
        cerr<<s<<endl;
        #endif
        this->_statistic.operator()(solution_star);

        while (this->_stoppingCriteria.operator()(solution_star)) {
            //Best neighborhood
            unique_ptr<vector<pair<unsigned int, SOL>>> listOfNeighborhood =  _atomicOperations->listOfMutations(solution_star);

            unsigned int bestNeighbour = 0;
            this->_problem.full_eval((*listOfNeighborhood)[0].second);

            for (unsigned int i = 1 ; i < listOfNeighborhood->size() ; i++) {
                this->_problem.full_eval((*listOfNeighborhood)[i].second);
                if (_selection((*listOfNeighborhood)[i].second, (*listOfNeighborhood)[bestNeighbour].second)) {
                    bestNeighbour = i;
                }
            }

            if (_selection((*listOfNeighborhood)[bestNeighbour].second, solution_star)) {
                solution_star = (*listOfNeighborhood)[bestNeighbour].second;
            }
            
            
            #ifdef DEBUG
            cerr<<s<<endl;
            #endif
            this->_statistic.operator()(solution_star);
        }

        return move(make_unique<SOL>(solution_star));
    }

    protected:
    SOL solution_star;
    AtomicOperation<SOL, TYPE_FITNESS, SOL> *_atomicOperations;
    Selection<SOL> &_selection;
};

#endif