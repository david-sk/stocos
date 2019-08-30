///
/// @file solver.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef SOLVER_GENERIC_H
#define	SOLVER_GENERIC_H

#include <random>
#include <string>
#include <memory>
#include <map>
#include <vector>

#include <boost/program_options.hpp>

#include <jsoncpp/json/json.h>

#include "solver.hpp"
#include "algobuilder.hpp"
#include "../problem/problem.hpp"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SolverGeneric : public Solver {
	public:
		SolverGeneric(const Json::Value &configuration, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem) : 
			Solver(),
			_configuration(configuration),
			_problem(problem) {
				BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" CREATE SolverGeneric";

				if (!configuration["seed"].empty())
					mt_rand.seed(configuration["seed"].asInt());
				else
					mt_rand.seed(static_cast<std::mt19937::result_type>(time(0)));

				if (!_configuration["problem"]["instance"].empty()) {
					Json::Value tmp = problem->loadInstance(_configuration["problem"]["instance"].asString());
					problem->loadJson(tmp);
				} else if (!_configuration["problem"]["numInstance"].empty())
					problem->loadJson(_configuration);
				else
					throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] Problem does not exist.");


				AlgoBuilder<SOL, TYPE_FITNESS, TYPE_CELL> algoBuilder(mt_rand, _problem, _configuration);

				for (std::string const &id : _configuration["OptimizationAlgorithm"].getMemberNames())
					optimizationAlgorithm[stoul(id)] = algoBuilder(std::move(_configuration["OptimizationAlgorithm"][id]));

				//
				_statistic = algoBuilder.getStatistic();

				// Create the initial solution
				if (_configuration["initial_solution"].empty())
					initial_solution = _problem->new_solution();
				else
					initial_solution = std::make_unique<SOL>(_configuration["initial_solution"]);

				if (!initial_solution->fitnessIsValid()) {
					_problem->full_eval(*initial_solution);
				}
		}
		virtual ~SolverGeneric() {
			BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" DELETE SolverGeneric";
		}

		void operator()() {
			if (optimizationAlgorithm.size() <= _configuration["parameter_id"].asUInt())
				throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] parameter_id "+ std::to_string(_configuration["parameter_id"].asUInt()) +" does not exist.");
			
			BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Launch optimisation "<< optimizationAlgorithm[_configuration["parameter_id"].asUInt()]->className();
			std::unique_ptr<SOL> s_new = optimizationAlgorithm[_configuration["parameter_id"].asUInt()]->operator()(*initial_solution);

			className(optimizationAlgorithm[_configuration["parameter_id"].asUInt()]->className());
			_statistic->operator()(*s_new, className());
		}


		std::string className() const {
			if (_class_name.empty())
				return "SolverGeneric";
			else 
				return _class_name;
		}

		void className(const std::string &class_name) {
			_class_name = class_name;
		}
	protected:
		const Json::Value &_configuration;
		std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
		std::shared_ptr<Statistic<SOL>> _statistic;
		std::mt19937 mt_rand;
		std::unique_ptr<SOL> initial_solution;
		std::map<unsigned int, std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>> optimizationAlgorithm;
		std::string _class_name;
		
		
};

#endif
