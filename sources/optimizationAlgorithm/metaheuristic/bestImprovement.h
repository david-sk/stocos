///
/// \file bestImprovement.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef BESTIMPROVEMENT_H
#define BESTIMPROVEMENT_H

#include <random>

#include "../optimizationAlgorithm.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "../../problem/problem.h"
#include "operator/atomicOperation.h"
#include "selection/selection.h"


using namespace std;

template<class SOL>
class BestImprovement : public OptimizationAlgorithm<SOL> {
    public:
    BestImprovement(std::mt19937 &mt_rand,
        Statistic<SOL> &statistic,
        StoppingCriteria<SOL> &stoppingCriteria,
        Problem<SOL> &problem,
        AtomicOperation<SOL> &atomicOperations,
        Selection<SOL> &selection,
        unsigned int N) :
        OptimizationAlgorithm<SOL>(mt_rand, statistic, stoppingCriteria, problem) {
        rid = new uniform_int_distribution<unsigned int>(0, N-1);
    }

    ~BestImprovement() {
        delete rid;
    }
    
    void operator()(SOL &s) {
        if (!s.fitnessIsValid()) {
           this-> _problem.full_eval(s);
        }
        #ifdef DEBUG
        cerr<<s<<endl;
        #endif
        this->_statistic.operator()(s);

        while (this->_stoppingCriteria.operator()(s)) {

            auto bestFitness = s.getFitness();
            unsigned int cellToMutate = 0;

            for (unsigned int j = 0 ; j < s.sizeArray() ; j++) {
                auto fitnessBefore = s.getFitness();

                s(j) == 1 ? s(j, 0) : s(j, 1);
                
                this->_problem.full_eval(s);

                if (bestFitness < s.getFitness()) {
                    bestFitness = s.getFitness();
                    cellToMutate = j;
                }

                s(j) == 1 ? s(j, 0) : s(j, 1);
                
                s.setFitness(fitnessBefore);
            }

            if (bestFitness != s.getFitness()) {                     
                if (s(cellToMutate) == 1) 
                    s(cellToMutate, 0);
                else 
                    s(cellToMutate, 1);
                
                s.setFitness(bestFitness);
            }
            
            #ifdef DEBUG
            cerr<<s<<endl;
            #endif
            this->_statistic.operator()(s);
        }
    }

    protected:
        uniform_int_distribution<unsigned int> *rid;
};

#endif