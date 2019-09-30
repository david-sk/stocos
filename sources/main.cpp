/// 
/// @file main.cpp
/// @author Jxtopher
/// @brief 
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-11
/// 
/// 

#define BOOST_LOG_DYN_LINK 1

#include <iostream>
#include <cstdlib>
#include <signal.h>
#include <map>
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/program_options.hpp>

#include "problem/oneMax.hpp"
#include "problem/latinSquare.hpp"
// #include "problem/knapsack.hpp"
#include "problem/travelingSalesmanProblem.hpp"
// #include "problem/subsetSum.hpp"
// #include "problem/continuousProblem.hpp"


#include "solver/solver.hpp"
#include "solver/solverGeneric.hpp"
#include "solver/solverClientRPC.hpp"

using namespace stocos;

void version(std::string name_software, std::string num_version);
void segfault_sigaction(int signal, siginfo_t *si, void *arg);

void version(std::string name_software, std::string num_version) {
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
	// -> signal
    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = segfault_sigaction;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGINT, &sa, NULL);
   // <- signal
	// Paramètre du programme
    std::string config_pathfile;
    std::string config_json;
    std::string loggin;
    
	boost::program_options::variables_map vm;
	boost::program_options::options_description argements("[*] main option");
	argements.add_options()
						("help,h", "help message")
						("version,v", "version")
						("config,c", boost::program_options::value<std::string>(&config_pathfile), "file configuration json (default : null)")
                        ("json,j", boost::program_options::value<std::string>(&config_json), "in string json (default : null)")
                        ("loggin,l", boost::program_options::value<std::string>(&loggin), "loggin (default : null)");
	try {
    	boost::program_options::store(boost::program_options::parse_command_line(argc, argv, argements), vm);
		// boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(config).allow_unregistered().run(), vm);
		boost::program_options::notify(vm);
	} catch (const boost::program_options::error &ex) {
    	//std::cerr << __FILE__<<":"<<__LINE__ <<ex.what() << std::endl;
        throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] error program_options");
  	}

	if (vm.count("version")) {
			version("STOChastic Optimization Solver", "1");
			exit(EXIT_SUCCESS);
	}

	// Defined the show log siverity level
	if (loggin == "debug") 
    	boost::log::core::get()->set_filter(boost::log::trivial::severity == boost::log::trivial::debug);
	else
		boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);

    if (config_pathfile.empty() && config_json.empty()) {
        std::cerr<<"./xx -c config.json"<<std::endl;
        std::cerr<<"./xx -j \"{\"JSON\" : \"ON\"}\""<<std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Read json file
    Json::Value configuration;
    Json::Reader reader;
    std::ifstream test(config_pathfile, std::ifstream::binary);
    bool parsingSuccessful = false;

    if (!config_pathfile.empty()) {
		if (!std::ifstream(config_pathfile.c_str()).good()) {
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] the file does not exist : "+ config_pathfile);
		}
        parsingSuccessful = reader.parse(test, configuration, false);
    } else if (!config_json.empty()) {
        parsingSuccessful = reader.parse(config_json, configuration);
    }

    if (!parsingSuccessful)
        throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +reader.getFormattedErrorMessages());

    std::string encoding = configuration.get("encoding", "UTF-8").asString();

    // Definition des problems
    std::shared_ptr<OneMax> eOneMax = std::make_shared<OneMax>();
    // std::shared_ptr<Subsetsum> eSubsetsum = std::make_shared<Subsetsum>();
    // std::shared_ptr<Knapsack> eKnapsack = std::make_shared<Knapsack>();
    std::shared_ptr<TravelingSalesmanProblem> eTravelingSalesmanProblem = std::make_shared<TravelingSalesmanProblem>();
    // std::shared_ptr<ContinuousProblem> eContinuousProblem = std::make_shared<ContinuousProblem>();


    Solver *solver = nullptr;

    if (configuration["aposd"].empty()) {
        if (configuration["problem"]["name"].asString() == "OneMax")
            solver = new SolverGeneric<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>(configuration, eOneMax);
        // else if (configuration["problem"]["name"].asString() == "Subsetsum")
        //     solver = new SolverGeneric<SOL_SUBSETSUM, TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM>(configuration, eSubsetsum);
        // else if (configuration["problem"]["name"].asString() == "Knapsack")
        //     solver = new SolverGeneric<SOL_KNAPSACK, TYPE_FITNESS_KNAPSACK, TYPE_CELL_KNAPSACK>(configuration, eKnapsack);
        // else if (configuration["problem"]["name"].asString() == "ContinuousProblem")
        //     solver = new SolverGeneric<SOL_CONTINUOUSPROBLEM, TYPE_FITNESS_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>(configuration, eContinuousProblem);
        else if (configuration["problem"]["name"].asString() == "TravelingSalesmanProblem")
            solver = new SolverGeneric<SOL_STP, TYPE_FITNESS_STP, TYPE_CELL_STP>(configuration, eTravelingSalesmanProblem);
        else
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] The optimization problem does not exist.");
    } else {
        if (configuration["aposd"]["Interface"].asString() == "WEBAPPLICATION") 
            solver = new SolverClientRPC<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>(configuration, eOneMax);
        else if (configuration["aposd"]["Interface"].asString() == "MPI")
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] The interface \""+ configuration["aposd"][""].asString() +"\" does not implemented."); 
        else
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] The interface \""+ configuration["aposd"][""].asString() +"\" does not exist.");
    }

    solver->operator()();
    delete solver;

    return EXIT_SUCCESS;
}
