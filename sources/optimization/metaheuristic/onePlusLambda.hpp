///
/// @file onePlusLambda.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef ONEPLUSLAMBDA_H
#define ONEPLUSLAMBDA_H

#include <memory>
#include <random>
#include <string>

#include "../optimizationAlgorithm.hpp"

namespace stocos 
{

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class OnePlusLambda : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    OnePlusLambda(std::mt19937 &mt_rand, 
        std::shared_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
        unsigned int lambda) : 
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic), std::move(stoppingCriteria), problem),
        _atomicOperations(std::move(atomicOperations)),
        _lambda(lambda) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation OnePlusLambda";
    }

    ~OnePlusLambda() {
    }
    
    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem->evaluation(solution_star);
        }
        
        while (this->_stoppingCriteria->operator()(solution_star)) {
            this->_statistic->operator()(solution_star, className());

            solution_beta = solution_star;
            for (unsigned int i = 0 ; i < _lambda ; i++) {
                solution_alpha = solution_star;
                
                _atomicOperations->operator()(solution_alpha);
                this->_problem->evaluation(solution_alpha);
                if (this->_problem->solutionSelection(solution_alpha, solution_beta)) {
                    solution_beta = solution_alpha;
                }
            }
             solution_star = solution_beta;
        }

        return std::move(std::make_unique<SOL>(solution_star));
    }
    

    std::string className() const {
        if (_class_name.empty())
            return "OnePlusLambda";
        else 
            return _class_name;
    }

    void className(const std::string &class_name) {
        _class_name = class_name;
    }

    protected:
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
        unsigned int _lambda;
        std::string _class_name;
        SOL solution_star;
        SOL solution_alpha;
        SOL solution_beta;
};

}
#endif