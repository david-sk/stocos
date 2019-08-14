///
/// \file optimizationAlgorithm.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef OPTIMIZATIONALGORITHM_H
#define OPTIMIZATIONALGORITHM_H

#include <random>

#include "../stoppingCriteria/stoppingCriteria.h"
#include "../problem/problem.h"
#include "../statistic/statistic.h"

template<class SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class OptimizationAlgorithm {
    public:
        OptimizationAlgorithm(std::mt19937 &mt_rand,
        std::unique_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem) : 
            _mt_rand(mt_rand),
            _statistic(move(statistic)),
            _stoppingCriteria(move(stoppingCriteria)),
            _problem(problem) { }
        virtual ~OptimizationAlgorithm() {

        }
    
        virtual std::unique_ptr<SOL> operator()(const SOL &s) = 0;
        virtual string className() const = 0;

    protected:
        std::mt19937 &_mt_rand;
        std::unique_ptr<Statistic<SOL>> _statistic;
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> _stoppingCriteria;
        shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> _problem;

};

#endif