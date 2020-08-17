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

#include "../problem/problem.h"
#include "optimizationAlgorithm.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class NearestNeighbourAlgorithm : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
	NearestNeighbourAlgorithm(std::mt19937& mt_rand, std::shared_ptr<Statistic<SOL>> statistic,
							  std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
							  std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem);

	~NearestNeighbourAlgorithm();

	std::unique_ptr<SOL> operator()(const SOL& s);

	std::string className() const;
	void className(const std::string& class_name);

  protected:
	std::string _class_name;
	std::unique_ptr<std::uniform_int_distribution<unsigned int>> rid;
};

} // namespace stocos
#endif
