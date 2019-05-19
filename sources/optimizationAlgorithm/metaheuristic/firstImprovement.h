///
/// \file firstImprovement.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///
 

#ifndef FIRSTIMPROVEMENT_H
#define FIRSTIMPROVEMENT_H

#include <random>

#include "operator/atomicOperation.h"
#include "../optimizationAlgorithm.h"
#include "../../problem/problem.h"
#include "selection/selection.h"

using namespace std;

template<class SOL>
class FirstImprovement : public OptimizationAlgorithm<SOL> {
    public:
    FirstImprovement(std::mt19937 &mt_rand, 
    Statistic<SOL> &statistic,
    StoppingCriteria<SOL> &stoppingCriteria,
    Problem<SOL> &problem,
    AtomicOperation<SOL> &atomicOperations,
    Selection<SOL> &selection,
    unsigned int N) : 
    OptimizationAlgorithm<SOL>(mt_rand, statistic, stoppingCriteria, problem),
    _atomicOperations(atomicOperations),
    _selection(selection) {
        rid = new uniform_int_distribution<unsigned int>(0, N-1);
    }

    ~FirstImprovement() {
        delete rid;
    }
    
    void operator()(SOL &s) {
        
        if (!s.fitnessIsValid()) {
            this->_problem.full_eval(s);
        }
        //unsigned int i = 0;
        while (this->_stoppingCriteria.operator()(s)) {
            //auto fitnessBefore = s.getFitness();
            

            #ifdef DEBUG
            cerr<<s<<endl;
            #endif
            this->_statistic.operator()(s);


            SOL s1(s);
            //-------------------------------
            _atomicOperations.operator()(s1);
            this->_problem.full_eval(s1);
            s = _selection(s1, s);
            
            //-------------------------------


            /*unsigned int ret = rid->operator()(this->_mt_rand);

            if (s(ret) == 1) 
                s(ret, 0);
            else 
                s(ret, 1);

            this->_problem.full(s);
            if (s.getFitness() < fitnessBefore ) {
                if (s(ret) == 1) 
                    s(ret, 0);
                else 
                    s(ret, 1);
                s.setFitness(fitnessBefore);
            }*/
        }

        
        #ifdef DEBUG
        cerr<<s<<endl;
        #endif
        this->_statistic.operator()(s);
        
    }

    protected:
        uniform_int_distribution<unsigned int> *rid;
        AtomicOperation<SOL> &_atomicOperations;
        Selection<SOL> &_selection;
};

#endif