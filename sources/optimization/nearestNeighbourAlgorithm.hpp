///
/// @file nearestNeighbourAlgorithm.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Nearest neighbour algorithm
///        see : https://en.wikipedia.org/wiki/Nearest_neighbour_algorithm
///

#ifndef NEARESTNEIGHOURALGORITHM_H
#define NEARESTNEIGHOURALGORITHM_H

#include <algorithm> // std::shuffle
#include <memory>	// std::shared_ptr std::unique_ptr
#include <random>	// std::mt19937
#include <string>	// std::string
#include <utility>   // std::pair
#include <vector>	// std::vector

#include "../problem/problem.hpp"
#include "optimizationAlgorithm.hpp"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class NearestNeighbourAlgorithm : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	NearestNeighbourAlgorithm(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
							  std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
							  std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
		: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(
			  mt_rand, std::move(statistic), std::move(stoppingCriteria), problem) {
		BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__
								 << " Creation NearestNeighbourAlgorithm";
	}

	~NearestNeighbourAlgorithm() {}

	std::unique_ptr<SOL> operator()(const SOL& s) {
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
					  << (solution_final->sizeArray() * (solution_final->sizeArray() - 1)) / 2
					  << "\r";
			std::cout.flush();
		}

		this->_problem->evaluation(*solution_final);
		return std::move(solution_final);
	}

	std::string className() const {
		if(_class_name.empty())
			return "NearestNeighbourAlgorithm";
		else
			return _class_name;
	}

	void className(const std::string& class_name) { _class_name = class_name; }

  protected:
	std::string _class_name;
	std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid;
};

} // namespace stocos
#endif
