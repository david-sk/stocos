///
/// \file solverSubsetsum.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SOLVERSUBSETSUM_H
#define SOLVERSUBSETSUM_H

#include <random>
#include <fstream>

#include "solver.h"
#include "defaultSetting/combinatorialOptimization.h"
#include "../problem/SubsetSum.h"

class SolverSubsetsum : public Solver {
    public:
    SolverSubsetsum(std::mt19937 &mt_rand, 
        boost::program_options::variables_map &vm, 
        boost::program_options::options_description & desc, 
        int argc, 
        char **argv) : 
        Solver(mt_rand, vm, desc, argc, argv) {

        N = 10000;
        optimizationAlgo = 0;
        budget = 400;
        statStatistic = false;

        settings(argc, argv);

        }

    virtual ~SolverSubsetsum() {

    }


    void settings(int argc, char **argv) {
        boost::program_options::options_description config("[*] Subsetsum parameter");
	    config.add_options()
			("N", boost::program_options::value<unsigned int>(&N), "taille de l'instance générer (default: 1000)")
			("algo,A", boost::program_options::value<int>(&optimizationAlgo), "algorithme utiliser ()")
            ("budget", boost::program_options::value<unsigned int>(&budget), "budget alouer à l'algorithme (default:400)")
            ("statistic", boost::program_options::value<bool>(&statStatistic), "Affiche des statistiques (default:false)");
        
        this->_desc.add(config);

        try {
            boost::program_options::store(boost::program_options::parse_command_line(argc, argv, this->_desc), this->_vm);
            boost::program_options::notify(this->_vm);
        } catch (const boost::program_options::error &ex) {
            std::cerr << __FILE__<<":"<<__LINE__ <<ex.what() << endl;
        }
        if (this->_vm.count("help")) {
                cout<<this->_desc<<endl;
                exit(EXIT_SUCCESS);
        }

        eSubsetsum = make_shared<Subsetsum>(N);
        CO = make_unique<CombinatorialOptimization<SOL_SUBSETSUM, TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM>>(this->_mt_rand, *eSubsetsum, budget);
    }

    void operator()() {
        SOL_SUBSETSUM s(1, N);

        eSubsetsum->reset_solution(s);

        this->operator()(s, optimizationAlgo);
        
        std::cout<<std::endl;
        cout<<s<<endl;
    }

    void operator()(SOL_SUBSETSUM &s, int numParameter) {
        unique_ptr<SOL_SUBSETSUM> solution_result(CO->operator()(s, numParameter));
        s = (*solution_result);
    }

    void operator()(string &solution, int numParameter) {
        SOL_SUBSETSUM s(solution);
        this->operator()(s, numParameter);
        cout<<s;
    }

    void initializationSolution() {
        SOL_SUBSETSUM s(1, N);
        
        eSubsetsum->reset_solution(s);
        eSubsetsum->full_eval(s);

        cout<<s;
    }

    private:
    unsigned int N;                 /// < Taille du problème
    int optimizationAlgo;           /// < algo utiliser
    unsigned int budget;            /// < budget alouer a l'aglorithme d'optimisation
    bool statStatistic;

    // 
    shared_ptr<Subsetsum> eSubsetsum;
    unique_ptr<CombinatorialOptimization<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>> CO;
};

#endif
