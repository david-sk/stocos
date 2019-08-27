///
/// @file tabuSearch.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief F. Glover, "Future paths for integer programming and links to artificial intelligence," Computers & Operations Research, vol. 13, pp. 533-549, 1986.
///

#ifndef TABUSEARCH_H
#define TABUSEARCH_H

#include <boost/circular_buffer.hpp>

#include <memory>



template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class TabuSearch : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
    public:
    TabuSearch(std::mt19937 &mt_rand, 
        std::shared_ptr<Statistic<SOL>> statistic,
        std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
        std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
        std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations,
        std::unique_ptr<Selection<SOL>> selection,
        unsigned int sizeOfTabuList = 7) : 
        OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic), std::move(stoppingCriteria), problem),
        _atomicOperations(std::move(atomicOperations)),
        _selection(std::move(selection))  {
        BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":"<<__LINE__<<" Creation TabuSearch";
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
            this->_statistic->operator()(solution_star, className());

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
        this->_statistic->operator()(solution_star, className());
        
        return std::move(std::make_unique<SOL>(solution_star));
    }


    std::string className() const {
        if (_class_name.empty())
            return "TabuSearch";
        else 
            return _class_name;
    }

    void className(const std::string &class_name) {
        _class_name = class_name;
    }

    protected:
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> _atomicOperations;
    std::unique_ptr<Selection<SOL>> _selection;
    std::string _class_name;

    SOL solution_star;
    SOL solution_beta;
    boost::circular_buffer<SOL> tabuList;
};


#endif


