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
#include "../statistic/sensorFinal.h"
#include "../statistic/sensorExperience.h"
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
#include "../optimizationAlgorithm/metaheuristic/operator/mutation/intervalReal.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_maximization.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_minimization.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_difference.h"


template<typename SOL, typename TYPE_FITNESS,typename TYPE_CELL>
class AlgoBuilder {
    public:
        AlgoBuilder(std::mt19937 &mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem, const Json::Value &configuration) :
        _mt_rand(mt_rand),
        _problem(problem) {
            _statistic = statistic(configuration["Statistic"]);
        }

        virtual ~AlgoBuilder() {
            
        }

        std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> operator()(const Json::Value &configuration) {
            std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> optimizationAlgorithm = nullptr;
            std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperation = atomicOperation(configuration["AtomicOperation"]);
            std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria = stoppingCriteria(configuration["StoppingCriteria"]);
            std::unique_ptr<Selection<SOL>> _selection = selection(configuration["Selection"]);
            
            if (configuration["className"] == "FirstImprovement") {
                optimizationAlgorithm = std::make_unique<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_selection));
            } else if (configuration["className"] == "BestImprovement") {
                // optimizationAlgorithm = std::make_unique<BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, *_statistic, *_stoppingCriteria, _problem, *_atomicOperation, *_selection);
            } else if (configuration["className"] == "OnePlusLambda") {
                optimizationAlgorithm = std::make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_selection), configuration["lambda"].asUInt());
            } else if (configuration["className"] == "IteratedLocalSearch") {
                std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> _optimizationAlgorithm_ils = this->operator()(configuration["OptimizationAlgorithm"]);
                optimizationAlgorithm = std::make_unique<IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_optimizationAlgorithm_ils), std::move(_selection));
            } else if (configuration["className"] == "TabuSearch") {
                optimizationAlgorithm = std::make_unique<TabuSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_selection));
            } else if (configuration["className"] == "EvolutionaryAlgorithm") {
                optimizationAlgorithm = std::make_unique<EvolutionaryAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_selection), configuration["mu"].asUInt(), configuration["lambda"].asUInt());
            } else if (configuration["className"] == "OnePlusLambda") {
                optimizationAlgorithm = std::make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_selection), configuration["lambda"].asInt());
            } else if (configuration["className"] == "SimulatedAnnealing") {
                optimizationAlgorithm = std::make_unique<SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_selection));
            } else {
                throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " The algorithm "+ configuration["className"].asString() +" does not exist.");
            }

            return std::move(optimizationAlgorithm);
        }
        


        void sensor(const Json::Value &configuration, std::shared_ptr<Statistic<SOL>> __statistic) {
            if (!configuration["sensorExperience"].empty()) {
                __statistic->addSensor(new SensorExperience<SOL>(configuration["sensorExperience"]["num"].asUInt(), configuration["sensorExperience"]["name"].asString()));
            }
            if (!configuration["sensorNumRound"].empty()) {
                if (configuration["sensorNumRound"] == true) {
                    __statistic->addSensor(new SensorNumRound<SOL>);
                }
            }
            if (!configuration["sensorSolution"].empty()) {
                if (configuration["sensorSolution"] == true) {
                    __statistic->addSensor(new SensorSolution<SOL>);
                }
            }
            if (!configuration["sensorStopwatch"].empty()) {
                if (configuration["sensorStopwatch"] == true) {
                    __statistic->addSensor(new SensorStopwatch<SOL>);
                }
            }
            if (!configuration["sensorFinal"].empty()) {
                __statistic->addSensor(new SensorFinal<SOL>(configuration["sensorFinal"]["num"].asUInt(), configuration["sensorFinal"]["name"].asString()));
            }
        }

        std::shared_ptr<Statistic<SOL>> statistic(const Json::Value &configuration) {
            std::shared_ptr<Statistic<SOL>> __statistic;
            if (Statistic<SOL>::NONE == configuration["recording"].asString()) {
                __statistic = std::make_shared<Statistic<SOL>>(true);
            } else if (Statistic<SOL>::STDOUT == configuration["recording"].asString()) {
                __statistic = std::make_shared<Statistic<SOL>>(false);
                sensor(configuration, __statistic);
            } else if (Statistic<SOL>::FILE == configuration["recording"].asString()) {
                __statistic = std::make_shared<Statistic<SOL>>(configuration["namefile"].asString());
                sensor(configuration, __statistic);
            } else if (Statistic<SOL>::MONGODB == configuration["recording"].asString()) {
                __statistic = std::make_shared<Statistic<SOL>>(
                        configuration["hostname"].asString(),
                        configuration["database"].asString(),
                        configuration["collection"].asString());
                sensor(configuration, __statistic);
            } else {
                throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " The recording statistic "+ configuration["recording"].asString() +" does not exist.");
            }
            return std::move(__statistic);
        }

        std::unique_ptr<StoppingCriteria<SOL,TYPE_FITNESS>> stoppingCriteria(const Json::Value &configuration) {
            std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria = std::make_unique<StoppingCriteria<SOL, TYPE_FITNESS>>();
            if (!configuration["budget"].empty())
                _stoppingCriteria->addCriteria(new CriteriaBudget<SOL, TYPE_FITNESS>(configuration["budget"].asUInt()));
            if (!configuration["fitnessObjectif"].empty())
                _stoppingCriteria->addCriteria(new CriteriaFitnessObjectif<SOL, TYPE_FITNESS>(static_cast<TYPE_FITNESS>(configuration["fitnessObjectif"].asDouble())));
            return std::move(_stoppingCriteria);
        }
        
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperation(const Json::Value &configuration) {
            if (configuration["className"].asString() == "FlipBit") {
                return std::make_unique<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, configuration["c"].asInt());
            } else if (configuration["className"].asString() == "IntervalReal") {
                return std::make_unique<IntervalReal<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, configuration["c"].asInt(), configuration["a"].asInt(), configuration["b"].asInt());
            } else if (configuration["className"].asString() == "Neighborhood") {
                //return std::make_unique<Neighborhood<SOL, TYPE_FITNESS, SOL>>(this->_mt_rand);
                //throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " Not implemented : "+configuration["className"].asString());
                return nullptr;
            }
            return nullptr;
        }

        std::unique_ptr<Selection<SOL>> selection(const Json::Value &configuration) {
            std::unique_ptr<Selection<SOL>> _selection = nullptr;

            if (configuration.asString() == "max") {
                _selection = std::make_unique<Selection_maximization<SOL>>();
            } else if (configuration.asString() == "min") {
                _selection = std::make_unique<Selection_minimization<SOL>>();
            } else if (configuration.asString() == "diff") { 
                _selection = std::make_unique<Selection_difference<SOL>>(_problem->getFitnessObjectif());
            } else {
                _selection = std::make_unique<Selection_difference<SOL>>(_problem->getFitnessObjectif());
            }
            return std::move(_selection);
        }


    private:
        std::mt19937 &_mt_rand;
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
        std::shared_ptr<Statistic<SOL>> _statistic;
        
};


#endif