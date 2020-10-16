///
/// @file problem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief description of the optimization problem
///

#ifndef PROBLEM_H
#define PROBLEM_H

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <fstream>   // std::ifstream
#include <iostream>  // std::cout, std::endl
#include <sstream>   // std::stringstream
#include <stdexcept> // std::runtime_error
#include <utility>   // std::pair
#include <vector>	// std::vector

#include "../solution/population.h"
#include "../solution/fitness.h"
#include "../solution/solution.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Problem {
  public:
	Problem();

	virtual ~Problem();

	///
	/// @brief give an instance from the json file in Json format
	///
	/// @param file 		path of the json file
	/// @return Json::Value give aconfiguration of the problem in Json format
	///
	virtual Json::Value loadInstance(const std::string& pathfile) const;

	///
	/// @brief Load the configuration in the instance problem
	///
	/// @param config file of the configuration in Json format
	///
	virtual void loadJson(const Json::Value& config) = 0;

	///
	/// @brief
	///
	/// @param s
	///
	virtual void resetSolution(SOL& s) const;
	///
	/// @brief Generating a solution
	///
	/// @return std::unique_ptr<SOL> the solution
	///
	virtual std::unique_ptr<SOL> new_solution() const;

	///
	/// @brief Check the solution structure : array size and the number of the objectif
	///
	/// @param s 		representation of the solution
	/// @return true 	if the solution structure is valid
	/// @return false 	if the solution structure is not valid
	///
	virtual bool checkSolutionStructure(const SOL& s) const;

	///
	/// @brief Evaluation of the solution
	///
	/// @param s solution with the update fitness
	///
	virtual void evaluation(SOL& s) = 0;

	///
	/// @brief Evaluation incremetal of the solution
	///
	/// @param s
	/// @param _listOfMutations
	///
	virtual void evaluationIncremental(
		const SOL& s,
		const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations) const;

	///
	/// @brief Evaluation of a sub-solution
	///
	/// @param s is a solution
	/// @return true 	if the sub-solution valid
	/// @return false 	if the sub-solution **non** valid
	///
	virtual bool evaluationSubSolution(SOL& s) const;

	///
	/// @brief Get the Fitness Objectif object
	///
	/// @param numObjectif
	/// @return TYPE_FITNESS
	///
	virtual TYPE_FITNESS getFitnessObjectif(unsigned int numObjectif = 0) const;

	///-------------
	virtual bool solutionSelection(const SOL& s_worst, const SOL& s_best);

	virtual unsigned int solutionSelection(const Population<SOL>& p);
};

} // namespace stocos

#endif