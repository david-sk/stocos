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

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/filereadstream.h>

#include "solver.h"

#include "../statistic/statistic.h"
#include "../statistic/sensor.h"
#include "../statistic/sensorNumRound.h"
#include "../statistic/sensorSolution.h"
#include "../statistic/sensorStopwatch.h"
#include "../stoppingCriteria/stoppingCriteria.h"
#include "../stoppingCriteria/criteriaBudget.h"
#include "../stoppingCriteria/criteriaFitnessObjectif.h"
#include "../problem/SubsetSum.h"
#include "../optimizationAlgorithm/metaheuristic/firstImprovement.h"
#include "../optimizationAlgorithm/metaheuristic/bestImprovement.h"
#include "../optimizationAlgorithm/metaheuristic/onePlusLambda.h"
#include "../optimizationAlgorithm/metaheuristic/operator/mutation/mutation_FlipBit.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_maximization.h"
#include "../optimizationAlgorithm/metaheuristic/selection/selection_difference.h"

template<class SOL>
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

        //----------
        eSubsetsum = make_shared<Subsetsum<SOL,  unsigned int>>(N);

        mutation_FlipBit = make_shared<Mutation_FlipBit<SOL>>(this->_mt_rand, 5);
        
        selection = make_shared<Selection_difference<SOL>>(eSubsetsum->getFitnessObjectif());
        
        stoppingCriteria = make_shared<StoppingCriteria<SOL>>();
        stoppingCriteria->addCriteria(new CriteriaBudget<SOL>(budget));
        stoppingCriteria->addCriteria(new CriteriaFitnessObjectif<SOL>(eSubsetsum->getFitnessObjectif()));
        
    	statistic = make_shared<Statistic<SOL>>(statStatistic);
	    statistic->addSensor(new SensorNumRound<SOL>);
	    statistic->addSensor(new SensorSolution<SOL>);
        statistic->addSensor(new SensorStopwatch<SOL>);

        optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL> *>("FirstImprovement", 
        new FirstImprovement<SOL>(this->_mt_rand, *statistic, *stoppingCriteria, *eSubsetsum, *mutation_FlipBit, *selection, N)));
        optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL> *>("BestImprovement", 
        new BestImprovement<SOL>(this->_mt_rand, *statistic, *stoppingCriteria, *eSubsetsum, *mutation_FlipBit, *selection, N)));
        optimizationAlgorithm.push_back(pair<string, OptimizationAlgorithm<SOL> *>("OnePlusLambda", 
        new OnePlusLambda<SOL>(this->_mt_rand, *statistic, *stoppingCriteria, *eSubsetsum, N, 50)));
    }

    virtual ~SolverSubsetsum() {

    }


    void settings(int argc, char **argv) {
        boost::program_options::options_description config("[*] Subsetsum parameter");
	    config.add_options()
			(",N", boost::program_options::value<unsigned int>(&N), "taille de l'instance générer (default: 1000)")
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
    }

    void operator()() {
        SOL s(1, N);

        eSubsetsum->reset_solution(s);

        this->operator()(s, optimizationAlgo);
        
        std::cout<<std::endl;
        cout<<s<<endl;
    }

    void operator()(SOL &s, int numParameter) {
        assert(0 <= numParameter);
        assert(numParameter < static_cast<int>(optimizationAlgorithm.size()));
        optimizationAlgorithm[static_cast<unsigned int>(numParameter)].second->operator()(s);
    }

    void operator()(string &solution, int numParameter) {
        SOL s(solution);
        this->operator()(s, numParameter);
        cout<<s;
    }

    void initializationSolution() {
        SOL s(1, N);
        
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
    shared_ptr<Subsetsum<SOL,  unsigned int>> eSubsetsum;
    vector<pair<string, OptimizationAlgorithm<SOL> *>> optimizationAlgorithm; /// < pair : name and pointer of algo

    shared_ptr<Mutation_FlipBit<SOL>> mutation_FlipBit;
    shared_ptr<Selection_difference<SOL>> selection;
    shared_ptr<StoppingCriteria<SOL>> stoppingCriteria;
    shared_ptr<Statistic<SOL>> statistic;
};

#endif
