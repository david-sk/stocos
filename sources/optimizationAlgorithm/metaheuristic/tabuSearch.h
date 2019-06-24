///
/// \file tabuSearch.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <boost/circular_buffer.hpp>

#include <memory>

using namespace std;

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class TabuSearch : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    TabuSearch(std::mt19937 &mt_rand, 
        Statistic<SOL> &statistic,
        StoppingCriteria<SOL, TYPE_FITNESS> &stoppingCriteria,
        Problem<SOL, TYPE_FITNESS, TYPE_CELL> &problem,
        AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> &atomicOperations,
        Selection<SOL> &selection) : 
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, statistic, stoppingCriteria, problem),
        _atomicOperations(atomicOperations),
        _selection(selection)  {
        DEBUG_TRACE("Creation TabuSearch");
        tabuList.set_capacity(5);
    }

    virtual ~TabuSearch() {

    }

    unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem.full_eval(solution_star);
        }

        while (this->_stoppingCriteria.operator()(solution_star)) {
            this->_statistic.operator()(solution_star);

            solution_beta = solution_star;
            _atomicOperations.operator()(solution_beta);

            // Recherche dans la liste tabou
            bool inTheTabooList = false;
            for (SOL solutionTabu : tabuList) {
                if (solutionTabu == solution_beta) {
                    inTheTabooList = true; 
                    break;
                }
            }

            if (!inTheTabooList) {
                this->_problem.full_eval(solution_beta);
                if (_selection(solution_beta, solution_star)) {
                    solution_star = solution_beta;
                }
            }
            tabuList.push_back(solution_beta);
        }
        
        return move(make_unique<SOL>(solution_star));
    }

    protected:
    AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> &_atomicOperations;
    Selection<SOL> &_selection;

    SOL solution_star;
    SOL solution_beta;
    boost::circular_buffer<SOL> tabuList;
};


#endif


