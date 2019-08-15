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

using namespace std;


template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SolverGeneric : public Solver {
	public:
		SolverGeneric(const Json::Value &configuration, shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem) : 
			Solver(),
			_configuration(configuration),
			_problem(problem) {
				DEBUG_TRACE("CREATE SolverGeneric")
				if (!configuration["seed"].empty())
					mt_rand.seed(configuration["seed"].isInt());
				else
					mt_rand.seed(static_cast<mt19937::result_type>(time(0)));

				problem->loadInstance(_configuration["problem"]["instance"].asString());

				AlgoBuilder<SOL, TYPE_FITNESS, TYPE_CELL> algoBuilder(mt_rand, _problem);

				for (string const& id : _configuration["OptimizationAlgorithm"].getMemberNames())
					oAlgo.insert(oAlgo.begin(), algoBuilder(id, _configuration["OptimizationAlgorithm"][id]));
					//oAlgo.push_back(algoBuilder(id, _configuration["OptimizationAlgorithm"][id]));			
		}
		virtual ~SolverGeneric() {
			DEBUG_TRACE("DELETE SolverGeneric")
		}

		void operator()() {
			std::unique_ptr<SOL> s = _problem->new_solution();
			std::unique_ptr<SOL> s_new = oAlgo[_configuration["numParameter"].asUInt()]->operator()(*s);
			std::cout<<std::endl;
			cout<<*s_new<<endl;

			cout<<oAlgo[_configuration["numParameter"].asUInt()]->className()<<endl;
		}
		
	protected:
		const Json::Value &_configuration;
		shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;
		std::mt19937 mt_rand;
		// map<string, std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>>> oAlgo;
		vector<std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> > oAlgo;
		
		
};

#endif
