///
/// @file firstImprovement.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///
 

#ifndef FIRSTIMPROVEMENT_H
#define FIRSTIMPROVEMENT_H

#include <random>

#include "operator/atomicOperation.h"
#include "../optimizationAlgorithm.h"
#include "../../problem/problem.h"



template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class FirstImprovement : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    FirstImprovement(std::mt19937 &mt_rand, 
    std::shared_ptr<Statistic<SOL>> statistic,
    std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
    std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations) : 
    OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic), std::move(stoppingCriteria), problem),
    _atomicOperations(std::move(atomicOperations)) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation FirstImprovement";
    }

    ~FirstImprovement() {
    }
    
    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem->full_eval(solution_star);
        }
        
        while (this->_stoppingCriteria->operator()(solution_star)) {
            this->_statistic->operator()(solution_star, className());
            
            solution_beta = solution_star;
            
            _atomicOperations->operator()(solution_beta);
            this->_problem->full_eval(solution_beta);
            if (this->_problem->solutionSelection(solution_beta, solution_star)) {
                solution_star = solution_beta;
            }
        }
        
        this->_statistic->operator()(solution_star, className());
        return std::move(std::make_unique<SOL>(solution_star));
    }


    std::string className() const {
        if (_class_name.empty())
            return "FirstImprovement";
        else 
            return _class_name;
    }

    void className(const std::string &class_name) {
        _class_name = class_name;
    }
    protected:
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
        std::string _class_name;
        SOL solution_star;
        SOL solution_beta;
};

#endif