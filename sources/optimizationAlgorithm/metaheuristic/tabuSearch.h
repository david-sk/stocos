///
/// \file tabuSearch.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief F. Glover, "Future paths for integer programming and links to artificial intelligence," Computers & Operations Research, vol. 13, pp. 533-549, 1986.
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
        std::unique_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
        std::unique_ptr<Selection<SOL>> selection,
        unsigned int sizeOfTabuList = 7) : 
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, move(statistic), move(stoppingCriteria), problem),
        _atomicOperations(move(atomicOperations)),
        _selection(move(selection))  {
        DEBUG_TRACE("Creation TabuSearch");
        tabuList.set_capacity(sizeOfTabuList);
    }

    virtual ~TabuSearch() {
    }

    std::unique_ptr<SOL> operator()(const SOL &s) {
        solution_star = s;
        if (!solution_star.fitnessIsValid()) {
            this->_problem->full_eval(solution_star);
        }

        while (this->_stoppingCriteria->operator()(solution_star)) {
            this->_statistic->operator()(solution_star);

            solution_beta = solution_star;
            _atomicOperations->operator()(solution_beta);

            // Recherche dans la liste tabou
            bool inTheTabooList = false;
            for (SOL solutionTabu : tabuList) {
                if (solutionTabu == solution_beta) {
                    inTheTabooList = true; 
                    break;
                }
            }

            if (!inTheTabooList) {
                this->_problem->full_eval(solution_beta);
                if (_selection->operator()(solution_beta, solution_star)) {
                    solution_star = solution_beta;
                }
            }
            tabuList.push_back(solution_beta);
        }
        
        return move(make_unique<SOL>(solution_star));
    }


    string className() const {
        return "TabuSearch";
    }

    protected:
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
    std::unique_ptr<Selection<SOL>> _selection;

    SOL solution_star;
    SOL solution_beta;
    boost::circular_buffer<SOL> tabuList;
};


#endif


