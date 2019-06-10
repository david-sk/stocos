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
#include "../../optimizationAlgorithm/metaheuristic/iteratedLocalSearch.h"
#include "../../optimizationAlgorithm/metaheuristic/simulatedAnnealing.h"
#include "../../optimizationAlgorithm/metaheuristic/tabuSearch.h"
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

            mutation_FlipBit_1 = make_shared<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, 1);
            mutation_FlipBit_N = make_shared<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, 1);
            
            selection = make_shared<Selection_difference<SOL>>(_problem.getFitnessObjectif());
            
            stoppingCriteria = make_shared<StoppingCriteria<SOL, TYPE_FITNESS>>();
            stoppingCriteria->addCriteria(new CriteriaBudget<SOL, TYPE_FITNESS>(budget));
            stoppingCriteria->addCriteria(new CriteriaFitnessObjectif<SOL, TYPE_FITNESS>(_problem.getFitnessObjectif()));
            
            statistic = make_shared<Statistic<SOL>>(statStatistic);
            statistic->addSensor(new SensorNumRound<SOL>);
            statistic->addSensor(new SensorSolution<SOL>);
            statistic->addSensor(new SensorStopwatch<SOL>);

            optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>("FirstImprovement", 
            new FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit_1, *selection)));
            optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>("BestImprovement", 
            new BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit_1, *selection)));
            optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>("OnePlusLambda", 
            new OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit_1, *selection, 50)));

            stoppingCriteria_ils = make_shared<StoppingCriteria<SOL, TYPE_FITNESS>>();
            stoppingCriteria_ils->addCriteria(new CriteriaBudget<SOL, TYPE_FITNESS>(100));
            statistic_ils = make_shared<Statistic<SOL>>(false);

            firstImprovement_ils = make_shared<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, *statistic_ils, *stoppingCriteria_ils, _problem, *mutation_FlipBit_1, *selection);
            optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> *>("IteratedLocalSearch", 
            new IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit_N, *firstImprovement_ils, *selection)));
        
            TabuSearch<SOL, TYPE_FITNESS, TYPE_CELL> TS(this->_mt_rand, *statistic, *stoppingCriteria, _problem, *mutation_FlipBit_1, *selection);
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
        
        shared_ptr<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>> mutation_FlipBit_1;
        shared_ptr<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>> mutation_FlipBit_N;
        shared_ptr<Selection<SOL>> selection;
        shared_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> stoppingCriteria;
        shared_ptr<Statistic<SOL>> statistic;

        // 
        shared_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> stoppingCriteria_ils;
        shared_ptr<Statistic<SOL>> statistic_ils;
        shared_ptr<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>> firstImprovement_ils;
};


#endif

