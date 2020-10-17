///
/// @file factory.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @date 2019-08-30
///
///

#ifndef ALGOBUILDER_H
#define ALGOBUILDER_H

#include <map>
#include <memory>
#include <random>

#include "optimization/exhaustiveSearch/backtracking.h"
#include "optimization/exhaustiveSearch/combinationGenerator.h"
#include "optimization/metaheuristic/bestImprovement.h"
#include "optimization/metaheuristic/evolutionaryAlgorithm.h"
#include "optimization/metaheuristic/firstImprovement.h"
#include "optimization/metaheuristic/iteratedLocalSearch.h"
#include "optimization/metaheuristic/onePlusLambda.h"
#include "optimization/metaheuristic/operator/mutation/flipBit.h"
#include "optimization/metaheuristic/operator/mutation/intervalInteger.h"
#include "optimization/metaheuristic/operator/mutation/intervalReal.h"
#include "optimization/metaheuristic/operator/mutation/neighborhood.h"
#include "optimization/metaheuristic/operator/shuffle.h"
#include "optimization/metaheuristic/operator/swap.h"
#include "optimization/metaheuristic/simulatedAnnealing.h"
#include "optimization/metaheuristic/tabuSearch.h"
#include "optimization/nearestNeighbourAlgorithm.h"
#include "problem/problem.h"
#include "statistic/sensor.h"
#include "statistic/sensorExperience.h"
#include "statistic/sensorFinal.h"
#include "statistic/sensorFitness.h"
#include "statistic/sensorNameCallingClass.h"
#include "statistic/sensorNumRound.h"
#include "statistic/sensorSolution.h"
#include "statistic/sensorStopwatch.h"
#include "statistic/statistic.h"
#include "stoppingCriteria/criteriaBudget.h"
#include "stoppingCriteria/criteriaFitnessObjectif.h"
#include "stoppingCriteria/stoppingCriteria.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Factory {
  public:
	Factory(std::mt19937& mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
			const Json::Value& configuration)
		: _mt_rand(mt_rand), _problem(problem) {
		_statistic = statistic(configuration["Statistic"]);
	}

	virtual ~Factory() {
	}

	std::unique_ptr<Optimization<SOL, TYPE_FITNESS, TYPE_CELL>>
		operator()(const Json::Value& configuration) {
		std::unique_ptr<Optimization<SOL, TYPE_FITNESS, TYPE_CELL>> optimization =
			nullptr;
		std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria =
			stoppingCriteria(configuration["StoppingCriteria"]);
		std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperation = nullptr;

		if(configuration["className"] != "NearestNeighbourAlgorithm" &&
		   configuration["className"] != "CombinationGenerator")
			_atomicOperation = atomicOperation(configuration["AtomicOperation"]);

		if(configuration["className"] == "FirstImprovement") {
			optimization =
				std::make_unique<FirstImprovement<SOL, TYPE_FITNESS, TYPE_CELL>>(
					this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem,
					std::move(_atomicOperation));
		} else if(configuration["className"] == "BestImprovement") {
			// ! TODO: need to fixed
			// optimization = std::make_unique<BestImprovement<SOL, TYPE_FITNESS,
			// TYPE_CELL>>(this->_mt_rand, *_statistic, *_stoppingCriteria, _problem,
			// *_atomicOperation, *_selection);
		} else if(configuration["className"] == "OnePlusLambda") {
			optimization = std::make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(
				this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem,
				std::move(_atomicOperation), configuration["lambda"].asUInt());
		} else if(configuration["className"] == "IteratedLocalSearch") {
			std::unique_ptr<Optimization<SOL, TYPE_FITNESS, TYPE_CELL>>
				_optimization_ils =
					this->operator()(configuration["Optimization"]);
			optimization =
				std::make_unique<IteratedLocalSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(
					this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem,
					std::move(_atomicOperation), std::move(_optimization_ils));
		} else if(configuration["className"] == "TabuSearch") {
			optimization = std::make_unique<TabuSearch<SOL, TYPE_FITNESS, TYPE_CELL>>(
				this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem,
				std::move(_atomicOperation));
		} else if(configuration["className"] == "EvolutionaryAlgorithm") {
			optimization =
				std::make_unique<EvolutionaryAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>(
					this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem,
					std::move(_atomicOperation), configuration["mu"].asUInt(),
					configuration["lambda"].asUInt());
		} else if(configuration["className"] == "OnePlusLambda") {
			optimization = std::make_unique<OnePlusLambda<SOL, TYPE_FITNESS, TYPE_CELL>>(
				this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem,
				std::move(_atomicOperation), configuration["lambda"].asInt());
		} else if(configuration["className"] == "SimulatedAnnealing") {
			optimization =
				std::make_unique<SimulatedAnnealing<SOL, TYPE_FITNESS, TYPE_CELL>>(
					this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem,
					std::move(_atomicOperation));
		} else if(configuration["className"] == "Backtraking") {
			// ! TODO: need to implement
		} else if(configuration["className"] == "CombinationGenerator") {
			optimization =
				std::make_unique<CombinationGenerator<SOL, TYPE_FITNESS, TYPE_CELL>>(
					this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem);
		} else if(configuration["className"] == "NearestNeighbourAlgorithm") {
			optimization =
				std::make_unique<NearestNeighbourAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>(
					this->_mt_rand, _statistic, std::move(_stoppingCriteria), _problem);
		} else {
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " The algorithm " + configuration["className"].asString() +
									 " does not exist.");
		}

		return std::move(optimization);
	}

	void sensor(const Json::Value& configuration, std::shared_ptr<Statistic<SOL>> __statistic) {
		if(!configuration["sensorExperience"].empty()) {
			__statistic->addSensor(
				new SensorExperience<SOL>(configuration["sensorExperience"]["num"].asUInt(),
										  configuration["sensorExperience"]["name"].asString()));
		}
		if(!configuration["sensorNumRound"].empty()) {
			if(configuration["sensorNumRound"] == true)
				__statistic->addSensor(new SensorNumRound<SOL>);
		}
		if(!configuration["sensorSolution"].empty()) {
			if(configuration["sensorSolution"] == true)
				__statistic->addSensor(new SensorFitness<SOL>);
		}
		if(!configuration["sensorFitness"].empty()) {
			if(configuration["sensorFitness"] == true)
				__statistic->addSensor(new SensorFitness<SOL>);
		}
		if(!configuration["sensorStopwatch"].empty()) {
			if(configuration["sensorStopwatch"] == true)
				__statistic->addSensor(new SensorStopwatch<SOL>);
		}
		if(!configuration["sensorNameCallingClass"].empty()) {
			if(configuration["sensorNameCallingClass"] == true)
				__statistic->addSensor(new SensorNameCallingClass<SOL>);
		}
		if(!configuration["sensorFinal"].empty()) {
			__statistic->addSensor(
				new SensorFinal<SOL>(configuration["sensorFinal"]["num"].asUInt(),
									 configuration["sensorFinal"]["name"].asString()));
		}
	}

	std::shared_ptr<Statistic<SOL>> getStatistic() {
		return _statistic;
	}

	std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>>
		stoppingCriteria(const Json::Value& configuration) {
		std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria =
			std::make_unique<StoppingCriteria<SOL, TYPE_FITNESS>>();
		if(!configuration["budget"].empty())
			_stoppingCriteria->addCriteria(
				new CriteriaBudget<SOL, TYPE_FITNESS>(configuration["budget"].asUInt()));
		if(!configuration["fitnessObjectif"].empty())
			_stoppingCriteria->addCriteria(new CriteriaFitnessObjectif<SOL, TYPE_FITNESS>(
				static_cast<TYPE_FITNESS>(configuration["fitnessObjectif"].asDouble())));
		return std::move(_stoppingCriteria);
	}

	std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>>
		atomicOperation(const Json::Value& configuration) {
		if(configuration["className"].asString() == "FlipBit") {
			return std::make_unique<FlipBit<SOL, TYPE_FITNESS, TYPE_CELL>>(
				this->_mt_rand, configuration["c"].asInt());
		} else if(configuration["className"].asString() == "IntervalReal") {
			return std::make_unique<IntervalReal<SOL, TYPE_FITNESS, TYPE_CELL>>(
				this->_mt_rand, configuration["c"].asInt(), configuration["a"].asInt(),
				configuration["b"].asInt());
		} else if(configuration["className"].asString() == "IntervalInteger") {
			return std::make_unique<IntervalInteger<SOL, TYPE_FITNESS, TYPE_CELL>>(
				this->_mt_rand, configuration["c"].asInt(), configuration["a"].asInt(),
				configuration["b"].asInt());
		} else if(configuration["className"].asString() == "Neighborhood") {
			// return std::make_unique<Neighborhood<SOL, TYPE_FITNESS, SOL>>(this->_mt_rand);
			// throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
			// " Not implemented : "+configuration["className"].asString());
			return nullptr; //! TODO need to fixed
		} else if(configuration["className"].asString() == "Swap") {
			return std::make_unique<Swap<SOL, TYPE_FITNESS, TYPE_CELL>>(
				this->_mt_rand, configuration["number_of_swap"].asInt());
		} else if(configuration["className"].asString() == "Shuffle") {
			return std::make_unique<Shuffle<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand);
		} else
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " The atomicOperation " +
									 configuration["className"].asString() + " does not exist.");
		return nullptr;
	}

  private:
	std::mt19937& _mt_rand;
	std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
	std::shared_ptr<Statistic<SOL>> _statistic;

	std::shared_ptr<Statistic<SOL>> statistic(const Json::Value& configuration) {
		std::shared_ptr<Statistic<SOL>> __statistic;
		if(Statistic<SOL>::NONE == configuration["recording"].asString()) {
			__statistic = std::make_shared<Statistic<SOL>>(true);
		} else if(Statistic<SOL>::STDOUT == configuration["recording"].asString()) {
			__statistic = std::make_shared<Statistic<SOL>>(false);
			sensor(configuration, __statistic);
		} else if(Statistic<SOL>::FILE == configuration["recording"].asString()) {
			__statistic = std::make_shared<Statistic<SOL>>(configuration["namefile"].asString());
			sensor(configuration, __statistic);
		} else if(Statistic<SOL>::MONGODB == configuration["recording"].asString()) {
			__statistic = std::make_shared<Statistic<SOL>>(configuration["hostname"].asString(),
														   configuration["database"].asString(),
														   configuration["collection"].asString());
			sensor(configuration, __statistic);
		} else {
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " The recording statistic " +
									 configuration["recording"].asString() + " does not exist.");
		}
		return std::move(__statistic);
	}
};

} // namespace stocos

#endif