///
/// \file main.cpp
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

//#define NDEBUG // for disabled assert

#include <boost/program_options.hpp>

#include <iostream>
#include <cstdlib>

#include "macro.h"

#include "solver/solverOnemax.h"
#include "solver/solverSubsetsum.h"

using namespace std;

void version(string name_software, string num_version);

void version(string name_software, string num_version) {
	std::cout<<"******************************************"<<std::endl;
	std::cout<<"[+] *** "<<name_software<<" ***"<<std::endl;
	std::cout<<"[+] Day compilation : "<<__DATE__<<" "<<__TIME__<<std::endl;
	std::cout<<"[+] Version : "<<num_version<<std::endl;
	std::cout<<"******************************************"<<std::endl;
}

int main(int argc, char **argv, char **envp) {
	//
	DEBUG_TRACE("Start of the program")

	unsigned long int seed = static_cast<unsigned long int>(time(0));
	unsigned int problemSolving = 0;
	string instance;
	string solution;
	int parameter = -1;

	// Paramètre du programme
	boost::program_options::variables_map vm;

	boost::program_options::options_description config("[*] main option");
	config.add_options()
						("help,h", "help message")
						("version,v", "version")
						("seed,s", boost::program_options::value<unsigned long int>(&seed), "seed (default: time(0))")
						("problem,p",  boost::program_options::value<unsigned int>(&problemSolving), "Problem solving (default : oneMax)")

						("!instance,i", boost::program_options::value<string>(&instance), "instance (default : null)")
						("initSolution", "give a initial solution")
						("solution", boost::program_options::value<string>(&solution), "solution (default : null)")
						("parameter", boost::program_options::value<int>(&parameter), "parameter (default : null)");
	try {
    	//boost::program_options::store(boost::program_options::parse_command_line(argc, argv, config), vm);
		boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(config).allow_unregistered().run(), vm);
		boost::program_options::notify(vm);
	} catch (const boost::program_options::error &ex) {
    	//std::cerr << __FILE__<<":"<<__LINE__ <<ex.what() << endl;
  	}

	if (vm.count("version")) {
			version("STOChastic Optimization Solver", "1");
			exit(EXIT_SUCCESS);
	}

	// 
	boost::program_options::options_description menuHelp("*** Allowed options ***");
	menuHelp.add(config);
	
	//
	std::mt19937 mt_rand;
	mt_rand.seed(seed);

	//
	unique_ptr<Solver> solver;
	using x = void;

	switch (problemSolving) {
		case 0: 
			solver.reset(new SolverOneMax(mt_rand, vm, menuHelp, argc, argv));
			break;
		case 1: 
			solver.reset(new SolverSubsetsum(mt_rand, vm, menuHelp, argc, argv));
			break;
		default:
			solver.reset(new SolverOneMax(mt_rand, vm, menuHelp, argc, argv));
			break;
	}

	if (vm.count("initSolution")) {
		solver->initializationSolution();
	} else if (!solution.empty() && parameter != -1) {
		solver->operator()(solution, parameter);
	} else {
		
		solver->operator()();
	}

	DEBUG_TRACE("Stop program")
	return EXIT_SUCCESS;
}
