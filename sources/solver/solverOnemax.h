///
/// \file solverOneMax.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SOLVERONEMAX_H
#define SOLVERONEMAX_H

#include <random>
#include <memory>

#include <boost/program_options.hpp>

#include "solver.h"
#include "defaultSetting/combinatorialOptimization.h"
#include "../problem/OneMax.h"


using namespace std;

class SolverOneMax : public Solver {
    public:
    SolverOneMax(std::mt19937 &mt_rand, 
        boost::program_options::variables_map &vm, 
        boost::program_options::options_description & desc, 
        int argc, 
        char **argv) : 
        Solver(mt_rand, vm, desc, argc, argv) {
            sizeArray= 1000;
            optimizationAlgo = 0;
            budget = 400;
            statStatistic = false;
            settings(argc, argv);
    }
    ~SolverOneMax() {

    }

    void settings(int argc, char **argv) {
        boost::program_options::options_description config("[*] OneMax parameter");
	    config.add_options()
			("N", boost::program_options::value<unsigned int>(&sizeArray), "taille de l'instance (default: 1000)")
            ("algo,A", boost::program_options::value<int>(&optimizationAlgo), "algorithme utiliser (default: )")
            ("budget", boost::program_options::value<unsigned int>(&budget), "budget alouer à l'algorithme (default:400)")
            ("statistic", boost::program_options::value<bool>(&statStatistic), "Affiche des statistiques (default:false)");
        this->_desc.add(config);

        try {
            boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(this->_desc).allow_unregistered().run(), this->_vm);
            //boost::program_options::store(boost::program_options::parse_command_line(argc, argv, _desc), this->_vm);
            boost::program_options::notify(this->_vm);
        } catch (const boost::program_options::error &ex) {
    	    std::cerr << __FILE__<<":"<<__LINE__ <<ex.what() << endl;
  	    }
        if (this->_vm.count("help")) {
                cout<<this->_desc<<endl;
                exit(EXIT_SUCCESS);
        }

        eOneMax = make_unique<OneMax>(sizeArray);
        CO = make_unique<CombinatorialOptimization<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>>(this->_mt_rand, *eOneMax, budget);
    }

    void operator()() {
        SOL_ONEMAX s(1, sizeArray);
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            s(i, 0);
        }
        
        this->operator()(s, optimizationAlgo);
        
        cout<<s<<endl;
    }

    void operator()(SOL_ONEMAX &s, int numParameter) {
        unique_ptr<SOL_ONEMAX> solution_result(CO->operator()(s, numParameter));
        s = (*solution_result);
    }
    
    void operator()(string &solution, int numParameter) {
        SOL_ONEMAX s(solution);

        this->operator()(s, numParameter);
        
        cout<<s;
    }

    void initializationSolution() {
        unique_ptr<SOL_ONEMAX> s = eOneMax->new_solution();

        eOneMax->full_eval((*s));
        
        cout<<(*s);
    }

    protected:
        unsigned int sizeArray;
        int optimizationAlgo;
        unsigned int budget;
        bool statStatistic;

        unique_ptr<OneMax> eOneMax;
        unique_ptr<CombinatorialOptimization<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>> CO;
};

#endif