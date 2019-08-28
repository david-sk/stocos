///
/// @file bestImprovement.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef BESTIMPROVEMENT_H
#define BESTIMPROVEMENT_H

#include <random>

#include "../optimizationAlgorithm.h"
#include "../../stoppingCriteria/stoppingCriteria.h"
#include "../../problem/problem.h"
#include "operator/atomicOperation.h"
#include "operator/mutation/neighborhood.h"




template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class BestImprovement : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    BestImprovement(std::mt19937 &mt_rand,
        std::shared_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations) :
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic), std::move(stoppingCriteria), problem) {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation of BestImprovement class";
        //_atomicOperations = new Neighborhood<SOL, TYPE_FITNESS, SOL>(mt_rand);
    }

    virtual ~BestImprovement() {
    }
    
    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;

        // if (!solution_star.fitnessIsValid()) {
        //    this-> _problem.full_eval(solution_star);
        // }

        // #ifdef DEBUG
        // std::cerr<<s<<std::endl;
        // #endif
        // this->_statistic.operator()(solution_star);

        // while (this->_stoppingCriteria.operator()(solution_star)) {
        //     //Best neighborhood
        //     std::unique_ptr<std::vector<std::pair<unsigned int, SOL>>> listOfNeighborhood =  _atomicOperations.listOfMutations(solution_star);

        //     unsigned int bestNeighbour = 0;
        //     this->_problem.full_eval((*listOfNeighborhood)[0].second);

        //     for (unsigned int i = 1 ; i < listOfNeighborhood->size() ; i++) {
        //         this->_problem.full_eval((*listOfNeighborhood)[i].second);
        //         if (this->_problem->solutionSelection((*listOfNeighborhood)[i].second, (*listOfNeighborhood)[bestNeighbour].second)) {
        //             bestNeighbour = i;
        //         }
        //     }

        //     if (this->_problem->solutionSelection((*listOfNeighborhood)[bestNeighbour].second, solution_star)) {
        //         solution_star = (*listOfNeighborhood)[bestNeighbour].second;
        //     }
            
            
        //     #ifdef DEBUG
        //     std::cerr<<s<<std::endl;
        //     #endif
        //     this->_statistic.operator()(solution_star);
        // }

        return std::move(std::make_unique<SOL>(solution_star));
    }


    std::string className() const {
        if (_class_name.empty())
            return "BestImprovement";
        else 
            return _class_name;
    }

    void className(const std::string &class_name) {
        _class_name = class_name;
    }

    protected:
    SOL solution_star;
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, SOL>> _atomicOperations;
    std::string _class_name;
};

#endif