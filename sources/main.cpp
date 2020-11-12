///
/// @file main.cpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-11
///

#define NAME_SOFTWARE "STOChastic Optimization Solver"
#define BOOST_LOG_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/program_options.hpp>
#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <signal.h>
#include <string>

// Include problem
#if MODULE_PROBLEM_ONEMAX
#include "problem/oneMax.h"
#endif
#if MODULE_PROBLEM_NQUEENSPROBLEM
#include "problem/nQueensProblem.h"
#endif
#if MODULE_PROBLEM_LATINSQUARE
#include "problem/latinSquare.h"
#endif
#if MODULE_PROBLEM_KNAPSACK
#include "problem/knapsack.h"
#endif
#if MODULE_PROBLEM_TSP
#include "problem/travelingSalesmanProblem.h"
#endif
#if MODULE_PROBLEM_SUBSETSUM
#include "problem/subsetSum.h"
#endif
#if MODULE_PROBLEM_CONTINOUSPROBLEM
#include "problem/continuousProblem.h"
#endif

// Include solver
#include "solver/solver.hpp"
#include "solver/solverClientRPC.hpp"
#include "solver/solverGeneric.hpp"

#include "version.h"

using namespace stocos;

void version(const std::string& name_software);
void segfault_sigaction(int signal, siginfo_t* si, void* arg);

void version(const std::string& name_software) {
    std::cout << "******************************************" << std::endl;
    std::cout << "[+] *** " << name_software << " ***" << std::endl;
    std::cout << "[+] Day compilation : " << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << "[+] Version (" << CMAKE_BUILD_TYPE << ") : " << VERSION_PROJECT << std::endl;
    std::cout << "[+] Git branch : " << GIT_BRANCH << std::endl;
    std::cout << "[+] Git commit hash : " << GIT_COMMIT_HASH << std::endl;
    std::cout << "******************************************" << std::endl;
}

void segfault_sigaction(int signal, siginfo_t* si, void* arg) {
    std::cerr << __FILE__ << ":" << __LINE__ << static_cast<void*>(si->si_addr) << std::endl;
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv, char** envp) {
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
    boost::program_options::options_description args("**" + std::string(NAME_SOFTWARE) + "**" +
                                                     " options");
    args.add_options()("help,h", "help message")("version,v", "version")(
        "config,c", boost::program_options::value<std::string>(&config_pathfile),
        "file configuration json (default : null)")(
        "json,j", boost::program_options::value<std::string>(&config_json),
        "in string json (default : null)")(
        "loggin,l", boost::program_options::value<std::string>(&loggin), "loggin (default : null)");
    try {
        boost::program_options::store(boost::program_options::parse_command_line(argc, argv, args),
                                      vm);
        boost::program_options::notify(vm);
    } catch(const boost::program_options::error& ex) {
        throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                                 " [-] error program_options " + ex.what());
    }

    if(vm.count("version")) {
        version(NAME_SOFTWARE);
        return EXIT_SUCCESS;
    }

    if(vm.count("help")) {
        std::cout << args << std::endl;
        return EXIT_SUCCESS;
    }

    // Defined the show log siverity level
    if(loggin == "debug")
        boost::log::core::get()->set_filter(boost::log::trivial::severity ==
                                            boost::log::trivial::debug);
    else
        boost::log::core::get()->set_filter(boost::log::trivial::severity >=
                                            boost::log::trivial::info);

    if(config_pathfile.empty() && config_json.empty()) {
        std::cout << args << std::endl;
        return EXIT_SUCCESS;
    }

    // Read json file
    Json::Value configuration;
    Json::Reader reader;
    std::ifstream test(config_pathfile, std::ifstream::binary);
    bool parsingSuccessful = false;

    if(!config_pathfile.empty()) {
        if(!std::ifstream(config_pathfile.c_str()).good()) {
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                                     " [-] the file does not exist : " + config_pathfile);
        }
        parsingSuccessful = reader.parse(test, configuration, false);
    } else if(!config_json.empty()) {
        parsingSuccessful = reader.parse(config_json, configuration);
    }

    if(!parsingSuccessful)
        throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +
                                 reader.getFormattedErrorMessages());

    std::string encoding = configuration.get("encoding", "UTF-8").asString();

// Definition des problems
#if MODULE_PROBLEM_ONEMAX
    std::shared_ptr<OneMax> eOneMax = std::make_shared<OneMax>();
#else
    throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                             " [-] The oneMax problem is not include of the binary. Please turn "
                             "true of MODULE_PROBLEM_ONEMAX in complilation.");
#endif
#if MODULE_PROBLEM_NQUEENSPROBLEM
    std::shared_ptr<NQueensProblem> eNQueensProblem = std::make_shared<NQueensProblem>();
#else
    throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                             " [-] The n-queens problem is not include of the binary. Please turn "
                             "true of MODULE_PROBLEM_ONEMAX in complilation.");
#endif
#if MODULE_PROBLEM_SUBSETSUM
    std::shared_ptr<Subsetsum> eSubsetsum = std::make_shared<Subsetsum>();
#else
    throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                             " [-] The subsetsum problem is not include of the binary. Please turn "
                             "true of MODULE_PROBLEM_SUBSETSUM in complilation.");
#endif
#if MODULE_PROBLEM_KNAPSACK
    std::shared_ptr<Knapsack> eKnapsack = std::make_shared<Knapsack>();
#else
    throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                             " [-] The Knapsack problem is not include of the binary. Please turn "
                             "true of MODULE_PROBLEM_KNAPSACK in complilation.");
#endif
#if MODULE_PROBLEM_TSP
    std::shared_ptr<TravelingSalesmanProblem> eTravelingSalesmanProblem =
        std::make_shared<TravelingSalesmanProblem>();
#else
    throw std::runtime_error(
        std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
        " [-] The traveling salesman problem is not include of the binary. Please turn "
        "true of MODULE_PROBLEM_TSP in complilation.");
#endif
#if MODULE_PROBLEM_CONTINOUSPROBLEM
    std::shared_ptr<ContinuousProblem> eContinuousProblem = std::make_shared<ContinuousProblem>();
#else
    throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                             " [-] The continous problem is not include of the binary. Please turn "
                             "true of MODULE_PROBLEM_CONTINOUSPROBLEM in complilation.");
#endif

    Solver* solver = nullptr;

    if(configuration["aposd"].empty()) {
        if(configuration["problem"]["name"].asString() == "OneMax") {
#if MODULE_PROBLEM_ONEMAX
            solver = new SolverGeneric<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>(
                configuration, eOneMax);
#endif
        } else if(configuration["problem"]["name"].asString() == "n-queens") {
#if MODULE_PROBLEM_NQUEENSPROBLEM
            solver = new SolverGeneric<SOL_NQUEENSPROBLEM, TYPE_FITNESS_NQUEENSPROBLEM,
                                       TYPE_CELL_NQUEENSPROBLEM>(configuration, eNQueensProblem);
#endif
        } else if(configuration["problem"]["name"].asString() == "Subsetsum") {
#if MODULE_PROBLEM_SUBSETSUM
            solver = new SolverGeneric<SOL_SUBSETSUM, TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM>(
                configuration, eSubsetsum);
#endif
        } else if(configuration["problem"]["name"].asString() == "Knapsack") {
#if MODULE_PROBLEM_KNAPSACK
            solver = new SolverGeneric<SOL_KNAPSACK, TYPE_FITNESS_KNAPSACK, TYPE_CELL_KNAPSACK>(
                configuration, eKnapsack);
#endif
        } else if(configuration["problem"]["name"].asString() == "ContinuousProblem") {
#if MODULE_PROBLEM_CONTINOUSPROBLEM
            solver =
                new SolverGeneric<SOL_CONTINUOUSPROBLEM, TYPE_FITNESS_CONTINUOUSPROBLEM,
                                  TYPE_CELL_CONTINUOUSPROBLEM>(configuration, eContinuousProblem);
#endif
        } else if(configuration["problem"]["name"].asString() == "TravelingSalesmanProblem") {
#if MODULE_PROBLEM_TSP
            solver = new SolverGeneric<SOL_STP, TYPE_FITNESS_STP, TYPE_CELL_STP>(
                configuration, eTravelingSalesmanProblem);
#endif
        } else
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                                     " [-] The optimization problem does not exist.");
    } else {
        if(configuration["aposd"]["Interface"].asString() == "WEBAPPLICATION") {
#if MODULE_PROBLEM_ONEMAX
            solver = new SolverClientRPC<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>(
                configuration, eOneMax);
#endif
        } else if(configuration["aposd"]["Interface"].asString() == "MPI")
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                                     " [-] The interface \"" +
                                     configuration["aposd"][""].asString() +
                                     "\" does not implemented.");
        else
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
                                     " [-] The interface \"" +
                                     configuration["aposd"][""].asString() + "\" does not exist.");
    }

    solver->operator()();
    delete solver;
    return EXIT_SUCCESS;
}
