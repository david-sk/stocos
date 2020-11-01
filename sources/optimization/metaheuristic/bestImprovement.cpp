///
/// @file bestImprovement.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include <optimization/metaheuristic/bestImprovement.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::BestImprovement(
    std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
    std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
    std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
    std::unique_ptr<AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>> atomicOperations)
    : Optimization<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
                                                 std::move(stoppingCriteria), problem) {
    BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation of BestImprovement class";
    //_atomicOperations = new Neighborhood<SOL, TYPE_FITNESS, SOL>(mt_rand);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::~BestImprovement() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::operator()(const SOL& s) {
    solution_star = s;

    // if (!solution_star.fitnessIsValid()) {
    //    this-> _problem.evaluation(solution_star);
    // }

    // #ifdef DEBUG
    // std::cerr<<s<<std::endl;
    // #endif
    // this->_statistic.operator()(solution_star);

    // while (this->_stoppingCriteria.operator()(solution_star)) {
    //     //Best neighborhood
    //     std::unique_ptr<std::vector<std::pair<unsigned int, SOL>>> listOfNeighborhood =
    //     _atomicOperations.listOfMutations(solution_star);

    //     unsigned int bestNeighbour = 0;
    //     this->_problem.evaluation((*listOfNeighborhood)[0].second);

    //     for (unsigned int i = 1 ; i < listOfNeighborhood->size() ; i++) {
    //         this->_problem.evaluation((*listOfNeighborhood)[i].second);
    //         if (this->_problem->solutionSelection((*listOfNeighborhood)[i].second,
    //         (*listOfNeighborhood)[bestNeighbour].second)) {
    //             bestNeighbour = i;
    //         }
    //     }

    //     if (this->_problem->solutionSelection((*listOfNeighborhood)[bestNeighbour].second,
    //     solution_star)) {
    //         solution_star = (*listOfNeighborhood)[bestNeighbour].second;
    //     }

    //     #ifdef DEBUG
    //     std::cerr<<s<<std::endl;
    //     #endif
    //     this->_statistic.operator()(solution_star);
    // }

    return std::move(std::make_unique<SOL>(solution_star));
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
    if(_class_name.empty())
        return "BestImprovement";
    else
        return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void BestImprovement<SOL, TYPE_FITNESS, TYPE_CELL>::className(const std::string& class_name) {
    _class_name = class_name;
}

template class BestImprovement<Solution<double, double>, double, double>;
template class BestImprovement<Solution<double, bool>, double, bool>;
template class BestImprovement<Solution<int, bool>, int, bool>;
template class BestImprovement<Solution<unsigned int, bool>, unsigned int, bool>;
template class BestImprovement<Solution<double, unsigned int>, double, unsigned int>;
template class BestImprovement<Solution<unsigned int, unsigned int>, unsigned int, unsigned int>;
} // namespace stocos