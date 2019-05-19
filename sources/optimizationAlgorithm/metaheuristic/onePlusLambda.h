///
/// \file onePlusLambda.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef ONEPLUSLAMBDA_H
#define ONEPLUSLAMBDA_H

#include "../optimizationAlgorithm.h"

template<class SOL>
class OnePlusLambda : public OptimizationAlgorithm<SOL> {
    public:
    OnePlusLambda(std::mt19937 &mt_rand, 
        Statistic<SOL> &statistic,
        StoppingCriteria<SOL> &stoppingCriteria,
        Problem<SOL> &problem,
        unsigned int N, 
        unsigned int lambda) : 
        OptimizationAlgorithm<SOL>(mt_rand, statistic, stoppingCriteria, problem),
        _lambda(lambda) {
        rid = new uniform_int_distribution<unsigned int>(0, N-1);
        lambdaNumber = new unsigned int[_lambda];
    }

    ~OnePlusLambda() {
        delete rid;
        delete lambdaNumber;
    }
    
    void operator()(SOL &s) {
        while (this->_stoppingCriteria.operator()(s)) {
            lambdaNumber[0] = rid->operator()(this->_mt_rand);
            for (unsigned int i = 1 ; i < _lambda;) {
                unsigned int ret = rid->operator()(this->_mt_rand);
                
                for (unsigned int j = 0 ; j < i ; j++) {
                    if(ret == lambdaNumber[j])
                        break;
                    else if (j == ( i- 1) ){
                        j++;
                        lambdaNumber[j] = ret;
                        i++;
                    }
                }
            }

            if (!s.fitnessIsValid()) {
                this->_problem.full_eval(s);
            }
            
            auto bestFitness = s.getFitness();
            unsigned int cellToMutate = 0;

            
            for (unsigned int i = 0 ; i < _lambda ; i++) {
                auto fitnessBefore = s.getFitness();
                s(lambdaNumber[i]) == 1 ? s(lambdaNumber[i], 0) : s(lambdaNumber[i], 1);
                this->_problem.full_eval(s);
                
                if (bestFitness < s.getFitness()) {
                    bestFitness = s.getFitness();
                    cellToMutate = lambdaNumber[i];
                }

                s(lambdaNumber[i]) == 1 ? s(lambdaNumber[i], 0) : s(lambdaNumber[i], 1);
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
        unsigned int _lambda;
        unsigned int *lambdaNumber;
        uniform_int_distribution<unsigned int> *rid;
};

#endif