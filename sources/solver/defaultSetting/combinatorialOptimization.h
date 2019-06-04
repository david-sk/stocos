#ifndef COMBINATORIALOPTIMIZATION_H
#define	COMBINATORIALOPTIMIZATION_H

#include <random>

#include "../solver.h"

#include "../../statistic/statistic.h"
#include "../../statistic/sensor.h"
#include "../../statistic/sensorNumRound.h"
#include "../../statistic/sensorSolution.h"
#include "../../statistic/sensorStopwatch.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "../../stoppingCriteria/criteriaBudget.h"
#include "../../stoppingCriteria/criteriaFitnessObjectif.h"
#include "../../problem/SubsetSum.h"
#include "../../optimizationAlgorithm/metaheuristic/firstImprovement.h"
#include "../../optimizationAlgorithm/metaheuristic/bestImprovement.h"
#include "../../optimizationAlgorithm/metaheuristic/onePlusLambda.h"
#include "../../optimizationAlgorithm/metaheuristic/operator/mutation/flipBit.h"
#include "../../optimizationAlgorithm/metaheuristic/selection/selection.h"
#include "../../optimizationAlgorithm/metaheuristic/selection/selection_maximization.h"
#include "../../optimizationAlgorithm/metaheuristic/selection/selection_minimization.h"
#include "../../optimizationAlgorithm/metaheuristic/selection/selection_difference.h"


template<typename SOL, typename TYPE_FITNESS,typename TYPE_CELL>
class CombinatorialOptimization {
    public:
        CombinatorialOptimization(std::mt19937 &mt_rand, Problem<SOL, TYPE_FITNESS, TYPE_CELL> &problem) :
        _mt_rand(mt_rand),
        _problem(problem)
        {
            statStatistic = true;
            budget = 400;

            mutation_FlipBit = make_shared<FlipBit<SOL, bool>>(this->_mt_rand, 5);
            
            selection = make_shared<Selection_difference<SOL>>(_problem.getFitnessObjectif());
            
            stoppingCriteria = make_shared<StoppingCriteria<SOL>>();
            stoppingCriteria->addCriteria(new CriteriaBudget<SOL>(budget));
            stoppingCriteria->addCriteria(new CriteriaFitnessObjectif<SOL>(_problem.getFitnessObjectif()));
            
            statistic = make_shared<Statistic<SOL>>(statStatistic);
            statistic->addSensor(new SensorNumRound<SOL>);
            statistic->addSensor(new SensorSolution<SOL>);
            statistic->addSensor(new SensorStopwatch<SOL>);

            optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>("FirstImprovement", 
            new FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit, *selection)));
            optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>("BestImprovement", 
            new BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit, *selection)));
            optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>("OnePlusLambda", 
            new OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit, *selection, 50)));
        }

        virtual ~CombinatorialOptimization() {
            
        }

        unique_ptr<SOL> operator()(const SOL &s, int numParameter) {
            assert(0 <= numParameter);
            assert(numParameter < static_cast<int>(optimizationAlgorithm.size()));
            return optimizationAlgorithm[static_cast<unsigned int>(numParameter)].second->operator()(s);
        }

    private:
        std::mt19937 &_mt_rand;
        Problem<SOL, TYPE_FITNESS, TYPE_CELL> &_problem;

        unsigned int budget;            /// < budget alouer a l'aglorithme d'optimisation
        bool statStatistic;

        vector<pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>> optimizationAlgorithm; /// < pair : name and pointer of algo
        
        shared_ptr<FlipBit<SOL, TYPE_CELL>> mutation_FlipBit;
        shared_ptr<Selection<SOL>> selection;
        shared_ptr<StoppingCriteria<SOL>> stoppingCriteria;
        shared_ptr<Statistic<SOL>> statistic;

};


#endif

