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

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class OnePlusLambda : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    OnePlusLambda(std::mt19937 &mt_rand, 
        std::unique_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
        std::unique_ptr<Selection<SOL>> selection,
        unsigned int lambda) : 
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, move(statistic), move(stoppingCriteria), problem),
        _atomicOperations(move(atomicOperations)),
        _selection(move(selection)),
        _lambda(lambda) {
        DEBUG_TRACE("Creation OnePlusLambda");
    }

    ~OnePlusLambda() {
    }
    
    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem->full_eval(solution_star);
        }
        
        while (this->_stoppingCriteria->operator()(solution_star)) {
            this->_statistic->operator()(solution_star);

            solution_beta = solution_star;
            for (unsigned int i = 0 ; i < _lambda ; i++) {
                solution_alpha = solution_star;
                
                _atomicOperations->operator()(solution_alpha);
                this->_problem->full_eval(solution_alpha);
                if (_selection->operator()(solution_alpha, solution_beta)) {
                    solution_beta = solution_alpha;
                }
            }
             solution_star = solution_beta;
        }

        this->_statistic->operator()(solution_star);

        return move(make_unique<SOL>(solution_star));
    }
    
    string className() const {
        return "OnePlusLambda";
    }

    protected:
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
        std::unique_ptr<Selection<SOL>> _selection;
        unsigned int _lambda;
        SOL solution_star;
        SOL solution_alpha;
        SOL solution_beta;
};

#endif