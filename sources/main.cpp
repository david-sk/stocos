/// 
/// \file main.cpp
/// \author Jxtopher
/// \brief 
/// \version 0.1
/// \date 2019-08-11
/// 
/// 

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <map>
#include <boost/program_options.hpp>

#include "problem/oneMax.h"
#include "problem/knapsack.h"
#include "problem/subsetSum.h"


#include "solver/solver.h"
#include "solver/solverGeneric.h"
#include "macro.h"

using namespace std;

void version(string name_software, string num_version);
void segfault_sigaction(int signal, siginfo_t *si, void *arg);

void version(string name_software, string num_version) {
	std::cout<<"******************************************"<<std::endl;
	std::cout<<"[+] *** "<<name_software<<" ***"<<std::endl;
	std::cout<<"[+] Day compilation : "<<__DATE__<<" "<<__TIME__<<std::endl;
	std::cout<<"[+] Version : "<<num_version<<std::endl;
	std::cout<<"******************************************"<<std::endl;
}

void segfault_sigaction(int signal, siginfo_t *si, void *arg) {
    printf("Caught segfault at address %p\n", si->si_addr);
    exit(EXIT_SUCCESS);
}


int main(int argc, char **argv, char **envp) {
    DEBUG_TRACE("Start of the program")

	// -> signal
    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);
   // <- signal

	// Paramètre du programme
    string configFile;
    bool solve = true;
    bool initSolution = false;

	boost::program_options::variables_map vm;
	boost::program_options::options_description argements("[*] main option");
	argements.add_options()
						("help,h", "help message")
						("version,v", "version")
                        ("solve,s", boost::program_options::value<bool>(&solve), "solve the problem (default : true)")
                        ("initSolution,i", boost::program_options::value<bool>(&initSolution), "give a initial solution (default : false)")
						("config,c", boost::program_options::value<string>(&configFile), "file configuration json (default : null)");
	try {
    	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, argements), vm);
		// boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(config).allow_unregistered().run(), vm);
		boost::program_options::notify(vm);
	} catch (const boost::program_options::error &ex) {
    	//std::cerr << __FILE__<<":"<<__LINE__ <<ex.what() << endl;
        throw runtime_error("[-] error program_options");
  	}

	if (vm.count("version")) {
			version("STOChastic Optimization Solver", "1");
			exit(EXIT_SUCCESS);
	}

    if (configFile.empty()) {
        cerr<<"./xx -c config.json"<<endl;
        exit(EXIT_FAILURE);
    }

    // Read json file
    Json::Value configuration;
    Json::Reader reader;
    std::ifstream test(configFile, std::ifstream::binary);
    bool parsingSuccessful = reader.parse(test, configuration, false);

    if (!parsingSuccessful)
        throw runtime_error(reader.getFormattedErrorMessages());

    std::string encoding = configuration.get("encoding", "UTF-8").asString();
    cout<<configuration<<endl;

    // Definition des problems
    shared_ptr<OneMax> eOneMax = make_shared<OneMax>();
    shared_ptr<Subsetsum> eSubsetsum = make_shared<Subsetsum>();
    shared_ptr<Knapsack> eKnapsack = make_shared<Knapsack>();

    Solver *solver = nullptr;
    if (configuration["problem"]["name"].asString() == "OneMax")
        solver = new SolverGeneric<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>(configuration, eOneMax);
    else if (configuration["problem"]["name"].asString() == "Subsetsum")
        solver = new SolverGeneric<SOL_SUBSETSUM, TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM>(configuration, eSubsetsum);
    else if (configuration["problem"]["name"].asString() == "Knapsack")
        solver = new SolverGeneric<SOL_KNAPSACK, TYPE_FITNESS_KNAPSACK, TYPE_CELL_KNAPSACK>(configuration, eKnapsack);
    else 
        throw runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] The optimization problem does not exist.");


    if (solve) {
        solver->operator()();
    }
    // if (solve) {
    //     solver->operator()();
    // } else if (initSolution) {
    //     solver->statisticQuiet();
    //     solver->initializationSolution();
    // } else {
    //     solver->statisticQuiet();
    //     solver->operator()(solution, parameter);
    // }


    DEBUG_TRACE("Stop program")
    return EXIT_SUCCESS;
}