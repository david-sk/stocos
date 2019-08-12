#ifndef ALGOBUILDER_H
#define	ALGOBUILDER_H

#include <random>
#include <map>
#include <memory>

#include "../statistic/statistic.h"
#include "../statistic/sensor.h"
#include "../statistic/sensorNumRound.h"
#include "../statistic/sensorSolution.h"
#include "../statistic/sensorStopwatch.h"
#include "../stoppingCriteria/stoppingCriteria.h"
#include "../stoppingCriteria/criteriaBudget.h"
#include "../stoppingCriteria/criteriaFitnessObjectif.h"
#include "../problem/problem.h"
#include "../problem/SubsetSum.h"
#include "../problem/oneMax.h"
#include "../optimizationAlgorithm/metaheuristic/firstImprovement.h"
#include "../optimizationAlgorithm/metaheuristic/bestImprovement.h"
#include "../optimizationAlgorithm/metaheuristic/onePlusLambda.h"
#include "../optimizationAlgorithm/metaheuristic/iteratedLocalSearch.h"
#include "../optimizationAlgorithm/metaheuristic/simulatedAnnealing.h"
#include "../optimizationAlgorithm/metaheuristic/tabuSearch.h"
#include "../optimizationAlgorithm/metaheuristic/evolutionaryAlgorithm.h"
#include "../optimizationAlgorithm/metaheuristic/operator/mutation/flipBit.h"
#include "../optimizationAlgorithm/metaheuristic/operator/mutation/neighborhood.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_maximization.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_minimization.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_difference.h"


template<typename SOL, typename TYPE_FITNESS,typename TYPE_CELL>
class AlgoBuilder {
    public:
        AlgoBuilder(std::mt19937 &mt_rand, shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem) :
        _mt_rand(mt_rand),
        _problem(problem) {

        }

        virtual ~AlgoBuilder() {
            
        }


        unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> operator()(const string &nameAlgo, const Json::Value &configuration) {
            
            unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> optimizationAlgorithm = nullptr;

            unique_ptr<Statistic<SOL>> _statistic = statistic(configuration);
            unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperation = atomicOperation(configuration["AtomicOperation"]);
            unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria = stoppingCriteria(configuration["StoppingCriteria"]);
            unique_ptr<Selection<SOL>> _selection = selection(configuration["Selection"]);
            

        
            if (nameAlgo == "FirstImprovement") {
                optimizationAlgorithm = make_unique<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, move(_statistic), move(_stoppingCriteria), _problem, move(_atomicOperation), move(_selection));
            } else if (nameAlgo == "BestImprovement") {
                // optimizationAlgorithm = make_unique<BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, *_statistic, *_stoppingCriteria, _problem, *_atomicOperation, *_selection);
            } else if (nameAlgo == "OnePlusLambda") {
                optimizationAlgorithm = make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, move(_statistic), move(_stoppingCriteria), _problem, move(_atomicOperation), move(_selection), configuration["lambda"].isInt());
            } else if (nameAlgo == "IteratedLocalSearch") {
                unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> _optimizationAlgorithm_ils = this->operator()(configuration["OptimizationAlgorithm"]["className"].asString(), configuration["OptimizationAlgorithm"]);
                optimizationAlgorithm = make_unique<IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, move(_statistic), move(_stoppingCriteria), _problem, move(_atomicOperation), move(_optimizationAlgorithm_ils), move(_selection));
            } else if (nameAlgo == "TabuSearch") {
                optimizationAlgorithm = make_unique<TabuSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, move(_statistic), move(_stoppingCriteria), _problem, move(_atomicOperation), move(_selection));
            } else if (nameAlgo == "EvolutionaryAlgorithm") {
                optimizationAlgorithm = make_unique<EvolutionaryAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, move(_statistic), move(_stoppingCriteria), _problem, move(_atomicOperation), move(_selection), configuration["sizeOfTabuList"].isInt());
            } else if (nameAlgo == "OnePlusLambda") {
                optimizationAlgorithm = make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, move(_statistic), move(_stoppingCriteria), _problem, move(_atomicOperation), move(_selection), configuration["lambda"].isInt());
            } else if (nameAlgo == "OnePlusLambda") {
                optimizationAlgorithm = make_unique<BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, move(_statistic), move(_stoppingCriteria), _problem, move(_atomicOperation), move(_selection));
            } else {
                throw runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " The algorithm does not exist.");
            }

            return move(optimizationAlgorithm);
        }
        


        unique_ptr<Statistic<SOL>> statistic(const Json::Value &configuration) {
            unique_ptr<Statistic<SOL>> _statistic = make_unique<Statistic<SOL>>(true);
            _statistic->addSensor(new SensorNumRound<SOL>);
            _statistic->addSensor(new SensorSolution<SOL>);
            _statistic->addSensor(new SensorStopwatch<SOL>);
            return move(_statistic);
        }

        unique_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> stoppingCriteria(const Json::Value &configuration) {
            unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria = make_unique<StoppingCriteria<SOL, TYPE_FITNESS>>();
            _stoppingCriteria->addCriteria(new CriteriaBudget<SOL, TYPE_FITNESS>(configuration["budget"].asUInt()));
            _stoppingCriteria->addCriteria(new CriteriaFitnessObjectif<SOL, TYPE_FITNESS>(static_cast<TYPE_FITNESS>(configuration["fitnessObjectif"].asDouble())));
            return move(_stoppingCriteria);
        }
        
        unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperation(const Json::Value &configuration) {
            if (configuration["className"].asString() == "FlipBit") {
                return make_unique<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, configuration["c"].asInt());
            } else if (configuration["className"].asString() == "Neighborhood") {
                //return make_unique<Neighborhood<SOL, TYPE_FITNESS, SOL>>(this->_mt_rand);
                throw runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " Not implemented");
            }
            return nullptr;
        }

        unique_ptr<Selection<SOL>> selection(const Json::Value &configuration) {
            unique_ptr<Selection<SOL>> _selection = nullptr;

            if (configuration.asString() == "max") {
                _selection = make_unique<Selection_maximization<SOL>>();
            } else if (configuration.asString() == "min") {
                _selection = make_unique<Selection_minimization<SOL>>();
            } else if (configuration.asString() == "diff") { 
                _selection = make_unique<Selection_difference<SOL>>(_problem->getFitnessObjectif());
            } else {
                _selection = make_unique<Selection_difference<SOL>>(_problem->getFitnessObjectif());
            }
            return move(_selection);
        }


    private:
        std::mt19937 &_mt_rand;
        shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
        
};


#endif

