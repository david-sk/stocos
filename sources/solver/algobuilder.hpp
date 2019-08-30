/// 
/// @file algobuilder.hpp
/// @author Jxtopher
/// @brief 
/// @version 0.1
/// @date 2019-08-30
/// 
///

#ifndef ALGOBUILDER_H
#define	ALGOBUILDER_H

#include <random>
#include <map>
#include <memory>

#include "../statistic/statistic.hpp"
#include "../statistic/sensor.hpp"
#include "../statistic/sensorNumRound.hpp"
#include "../statistic/sensorSolution.hpp"
#include "../statistic/sensorStopwatch.hpp"
#include "../statistic/sensorFinal.hpp"
#include "../statistic/sensorExperience.hpp"
#include "../statistic/sensorNameCallingClass.hpp"
#include "../stoppingCriteria/stoppingCriteria.hpp"
#include "../stoppingCriteria/criteriaBudget.hpp"
#include "../stoppingCriteria/criteriaFitnessObjectif.hpp"
#include "../problem/problem.hpp"
#include "../optimizationAlgorithm/metaheuristic/firstImprovement.hpp"
#include "../optimizationAlgorithm/metaheuristic/bestImprovement.hpp"
#include "../optimizationAlgorithm/metaheuristic/onePlusLambda.hpp"
#include "../optimizationAlgorithm/metaheuristic/iteratedLocalSearch.hpp"
#include "../optimizationAlgorithm/metaheuristic/simulatedAnnealing.hpp"
#include "../optimizationAlgorithm/metaheuristic/tabuSearch.hpp"
#include "../optimizationAlgorithm/metaheuristic/evolutionaryAlgorithm.hpp"
#include "../optimizationAlgorithm/metaheuristic/operator/mutation/flipBit.hpp"
#include "../optimizationAlgorithm/metaheuristic/operator/mutation/neighborhood.hpp"
#include "../optimizationAlgorithm/metaheuristic/operator/mutation/intervalReal.hpp"


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
            
            if (configuration["className"] == "FirstImprovement") {
                optimizationAlgorithm = std::make_unique<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation));
            } else if (configuration["className"] == "BestImprovement") {
                // optimizationAlgorithm = std::make_unique<BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, *_statistic, *_stoppingCriteria, _problem, *_atomicOperation, *_selection);
            } else if (configuration["className"] == "OnePlusLambda") {
                optimizationAlgorithm = std::make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), configuration["lambda"].asUInt());
            } else if (configuration["className"] == "IteratedLocalSearch") {
                std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> _optimizationAlgorithm_ils = this->operator()(configuration["OptimizationAlgorithm"]);
                optimizationAlgorithm = std::make_unique<IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), std::move(_optimizationAlgorithm_ils));
            } else if (configuration["className"] == "TabuSearch") {
                optimizationAlgorithm = std::make_unique<TabuSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation));
            } else if (configuration["className"] == "EvolutionaryAlgorithm") {
                optimizationAlgorithm = std::make_unique<EvolutionaryAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), configuration["mu"].asUInt(), configuration["lambda"].asUInt());
            } else if (configuration["className"] == "OnePlusLambda") {
                optimizationAlgorithm = std::make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation), configuration["lambda"].asInt());
            } else if (configuration["className"] == "SimulatedAnnealing") {
                optimizationAlgorithm = std::make_unique<SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem, std::move(_atomicOperation));
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
            if (!configuration["sensorNameCallingClass"].empty()) {
                if (configuration["sensorNameCallingClass"] == true) {
                    __statistic->addSensor(new SensorNameCallingClass<SOL>);
                }
            }
            if (!configuration["sensorFinal"].empty()) {
                __statistic->addSensor(new SensorFinal<SOL>(configuration["sensorFinal"]["num"].asUInt(), configuration["sensorFinal"]["name"].asString()));
            }
        }

        std::shared_ptr<Statistic<SOL>> getStatistic() {
            return _statistic;
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
                return std::make_unique<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _problem, configuration["c"].asInt());
            } else if (configuration["className"].asString() == "IntervalReal") {
                return std::make_unique<IntervalReal<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _problem, configuration["c"].asInt(), configuration["a"].asInt(), configuration["b"].asInt());
            } else if (configuration["className"].asString() == "Neighborhood") {
                //return std::make_unique<Neighborhood<SOL, TYPE_FITNESS, SOL>>(this->_mt_rand);
                //throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " Not implemented : "+configuration["className"].asString());
                return nullptr;
            }
            return nullptr;
        }

    private:
        std::mt19937 &_mt_rand;
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
        std::shared_ptr<Statistic<SOL>> _statistic;



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
};


#endif