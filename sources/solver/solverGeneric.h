///
/// @file solver.h
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

#include "solver.h"
#include "algobuilder.h"
#include "../problem/problem.h"

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SolverGeneric : public Solver {
	public:
		SolverGeneric(const Json::Value &configuration, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem) : 
			Solver(),
			_configuration(configuration),
			_problem(problem) {
				BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" CREATE SolverGeneric";
				if (!configuration["seed"].empty())
					mt_rand.seed(configuration["seed"].isInt());
				else
					mt_rand.seed(static_cast<std::mt19937::result_type>(time(0)));

				if (access(_configuration["problem"]["instance"].asString().c_str(), F_OK ) == -1) {
					throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] the file does not exist : "+ _configuration["problem"]["instance"].asString());
				}
				problem->loadInstance(_configuration["problem"]["instance"].asString());

				AlgoBuilder<SOL, TYPE_FITNESS, TYPE_CELL> algoBuilder(mt_rand, _problem, _configuration);

				for (std::string const &id : _configuration["OptimizationAlgorithm"].getMemberNames())
					optimizationAlgorithm[stoul(id)] = algoBuilder(std::move(_configuration["OptimizationAlgorithm"][id]));
				//optimizationAlgorithm.insert(optimizationAlgorithm.begin(), algoBuilder(_configuration["OptimizationAlgorithm"][id]));

				// Create the initial solution
				if (_configuration["Solution"].empty())
					initial_solution = _problem->new_solution();
				else
					initial_solution = std::make_unique<SOL>(_configuration["Solution"]);
		}
		virtual ~SolverGeneric() {
			BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" DELETE SolverGeneric";
		}

		void operator()() {
			if (optimizationAlgorithm.size() <= _configuration["parameter_id"].asUInt())
				throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] parameter_id "+ std::to_string(_configuration["parameter_id"].asUInt()) +" does not exist.");
			
			BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Launch optimisation "<< optimizationAlgorithm[_configuration["parameter_id"].asUInt()]->className();
			std::unique_ptr<SOL> s_new = optimizationAlgorithm[_configuration["parameter_id"].asUInt()]->operator()(*initial_solution);
		}
		
	protected:
		const Json::Value &_configuration;
		std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
		std::mt19937 mt_rand;
		std::unique_ptr<SOL> initial_solution;
		//std::vector<std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> > optimizationAlgorithm;
		std::map<unsigned int, std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>> optimizationAlgorithm;
		
		
};

#endif
