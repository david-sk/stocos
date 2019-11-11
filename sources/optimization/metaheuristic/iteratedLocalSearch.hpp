///
/// @file iteratedLocalSearch.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///
 

#ifndef ITERATEDLOCALSEARCH_H
#define ITERATEDLOCALSEARCH_H

#include <memory>
#include <random>
#include <string>

#include "operator/atomicOperation.hpp"
#include "../optimizationAlgorithm.hpp"
#include "../../problem/problem.hpp"

namespace stocos 
{

// Exploration-Exploitation
template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class IteratedLocalSearch : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    IteratedLocalSearch(std::mt19937 &mt_rand, 
    std::shared_ptr<Statistic<SOL>> statistic,
    std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
    std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> exploration,
    std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> exploitation) : 
    OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic), std::move(stoppingCriteria), problem),
    _exploration(std::move(exploration)),
    _exploitation(std::move(exploitation)) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation IteratedLocalSearch";
        _exploitation->className("ILS>"+_exploitation->className());
    }

    ~IteratedLocalSearch() {
    }
    
    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem->evaluation(solution_star);
        }
        
        while (this->_stoppingCriteria->operator()(solution_star)) {
            this->_statistic->operator()(solution_star, className());

            solution_beta = solution_star;
            
            _exploration->operator()(solution_beta);
            std::unique_ptr<SOL> solution_beta_beta = _exploitation->operator()(solution_beta);

            this->_problem->evaluation(*solution_beta_beta);
            if (this->_problem->solutionSelection(*solution_beta_beta, solution_star)) {
                solution_star = *solution_beta_beta;
            }
        }

        return std::move(std::make_unique<SOL>(solution_star));
    }

    std::string className() const {
        if (_class_name.empty())
            return "IteratedLocalSearch";
        else 
            return _class_name;
    }

    void className(const std::string &class_name) {
        _class_name = class_name;
    }
    
    protected:
        std::string _class_name;
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _exploration;
        std::unique_ptr<OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>> _exploitation;
        SOL solution_star;
        SOL solution_beta;
};

}
#endif