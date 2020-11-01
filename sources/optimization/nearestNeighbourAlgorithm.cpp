///
/// @file nearestNeighbourAlgorithm.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Nearest neighbour algorithm
///        see : https://en.wikipedia.org/wiki/Nearest_neighbour_algorithm
///

#include <optimization/nearestNeighbourAlgorithm.h>

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
NearestNeighbourAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>::NearestNeighbourAlgorithm(
    std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
    std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
    std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
    : Optimization<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, std::move(statistic),
                                                 std::move(stoppingCriteria), problem) {
    BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__
                             << " Creation NearestNeighbourAlgorithm";
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
NearestNeighbourAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>::~NearestNeighbourAlgorithm() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<SOL> NearestNeighbourAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>::
    operator()(const SOL& s) {
    std::unique_ptr<SOL> solution_final = std::make_unique<SOL>(s);
    SOL subsolution(2);
    rid = std::make_unique<std::uniform_int_distribution<unsigned int>>(
        0, solution_final->sizeArray() - 1);
    std::pair<std::vector<unsigned int>::iterator, double> best_node; // <id_node, fitness>

    //
    std::vector<unsigned int> nodes_not_use;
    for(unsigned int i = 0; i < solution_final->sizeArray(); i++) nodes_not_use.push_back(i);
    std::shuffle(nodes_not_use.begin(), nodes_not_use.end(), this->_mt_rand);
    unsigned int count = 0;

    //
    unsigned int pick = *(nodes_not_use.begin());
    nodes_not_use.erase(nodes_not_use.begin());
    solution_final->operator()(0, pick);
    for(unsigned int i = 1; i < solution_final->sizeArray(); i++) {
        subsolution(0, solution_final->operator()(i - 1));

        subsolution(1, nodes_not_use[0]);
        this->_problem->evaluation(subsolution);
        best_node.first = nodes_not_use.begin();
        best_node.second = subsolution.getFitness();
        for(std::vector<unsigned int>::iterator it = nodes_not_use.begin() + 1;
            it != nodes_not_use.end(); ++it) {
            subsolution(1, nodes_not_use[*it]);
            this->_problem->evaluation(subsolution);
            if(subsolution.getFitness() < best_node.second) {
                best_node.first = it;
                best_node.second = subsolution.getFitness();
            }
            count++;
        }
        solution_final->operator()(i, *(best_node.first));
        nodes_not_use.erase(best_node.first);

        std::cout << count << " "
                  << (solution_final->sizeArray() * (solution_final->sizeArray() - 1)) / 2 << "\r";
        std::cout.flush();
    }

    this->_problem->evaluation(*solution_final);
    return std::move(solution_final);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::string NearestNeighbourAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>::className() const {
    if(_class_name.empty())
        return "NearestNeighbourAlgorithm";
    else
        return _class_name;
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void NearestNeighbourAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>::className(
    const std::string& class_name) {
    _class_name = class_name;
}
template class NearestNeighbourAlgorithm<Solution<double, double>, double, double>;
template class NearestNeighbourAlgorithm<Solution<double, bool>, double, bool>;
template class NearestNeighbourAlgorithm<Solution<int, bool>, int, bool>;
template class NearestNeighbourAlgorithm<Solution<unsigned int, bool>, unsigned int, bool>;
template class NearestNeighbourAlgorithm<Solution<double, unsigned int>, double, unsigned int>;
template class NearestNeighbourAlgorithm<Solution<unsigned int, unsigned int>, unsigned int,
                                         unsigned int>;
} // namespace stocos
