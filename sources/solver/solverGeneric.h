///
/// \file solver.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SOLVER_GENERIC_H
#define	SOLVER_GENERIC_H

#include <random>
#include <string>
#include <memory>

#include <boost/program_options.hpp>

#include "solver.h"
#include "../problem/problem.h"
#include "defaultSetting/combinatorialOptimization.h"

using namespace std;


template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class SolverGeneric : public Solver {
	public:
		SolverGeneric(std::mt19937 &mt_rand, 
			boost::program_options::variables_map &vm, 
			boost::program_options::options_description & desc, 
			int argc, 
			char **argv,
			Problem<SOL, TYPE_FITNESS, TYPE_CELL> &problem) : 
			Solver(mt_rand, vm, desc, argc, argv),
			_problem(problem) {
			fileInstance = "";
			settings(argc, argv);
			
		}
		virtual ~SolverGeneric() {
			
		}

		void settings(int argc, char **argv) {
			boost::program_options::options_description config("[*] OneMax parameter");
			config.add_options()
				("instance", boost::program_options::value<string>(&fileInstance), "path of instance (default: None)")
				("algo,A", boost::program_options::value<int>(&optimizationAlgo), "algorithme utiliser (default: )")
				("budget", boost::program_options::value<unsigned int>(&budget), "budget alouer à l'algorithme (default:400)")
				("statistic", boost::program_options::value<bool>(&statStatistic), "Affiche des statistiques (default:false)");
			this->_desc.add(config);

			try {
				boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(this->_desc).allow_unregistered().run(), this->_vm);
				boost::program_options::notify(this->_vm);
			} catch (const boost::program_options::error &ex) {
				std::cerr << __FILE__<<":"<<__LINE__ <<ex.what() << endl;
			}
			if (this->_vm.count("help")) {
					cout<<this->_desc<<endl;
					exit(EXIT_SUCCESS);
			}

			_problem.loadInstance(fileInstance);
			CO = make_unique<CombinatorialOptimization<SOL, TYPE_FITNESS, TYPE_CELL>>(this->_mt_rand, _problem);
		}

		void operator()() {
			unique_ptr<SOL> s = _problem.new_solution();

			this->operator()(*s, optimizationAlgo);
			
			std::cout<<std::endl;
			cout<<*s<<endl;
		}

		void operator()(SOL &s, int numParameter) {
			unique_ptr<SOL> solution_result(CO->operator()(s, numParameter));
			s = (*solution_result);
		}

		void operator()(string &solution, int numParameter) {
			SOL s(solution);
			this->operator()(s, numParameter);
			cout<<s;
		}

		void initializationSolution() {
			unique_ptr<SOL> s = _problem.new_solution();

			_problem.full_eval(*s);

			cout<<(*s);
		}

	protected:
		Problem<SOL, TYPE_FITNESS, TYPE_CELL> &_problem;
		string fileInstance;
		bool statStatistic;
		unsigned int budget;
		int optimizationAlgo;
		unique_ptr<CombinatorialOptimization<SOL, TYPE_FITNESS, TYPE_CELL>> CO;
};

#endif
