///
/// @file solution.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Definition of the number of goals, fitness, and fitnessIsValid
///

#ifndef SOLUTION_H
#define SOLUTION_H

#include <cassert>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

#include <jsoncpp/json/json.h>

namespace stocos {

template<typename TYPE_FITNESS>
class Solution {
  public:
	Solution(const Solution& s);
	Solution();

	Solution(const unsigned int number_of_objective);

	Solution(const Json::Value& jsonValue);

	Solution& operator=(const Solution& s);

	~Solution();

	///
	/// @brief Give for a numObjectif the state fitness
	///
	/// @param numObjectif
	/// @return true if the fitness is valide
	/// @return false if the fitness is not valide
	///
	bool fitnessIsValid(unsigned int numObjectif = 0) const;

	///
	/// @brief Set the value fitness for a objectif
	///
	/// @param numObjectif objectif id
	/// @param value new value
	///
	void setFitness(unsigned int numObjectif, TYPE_FITNESS value);

	void setFitness(TYPE_FITNESS value);
	TYPE_FITNESS getFitness(unsigned int numObjectif = 0) const;

	unsigned int numberOfObjective() const;
	// --------------------------------------------------------------------
	friend std::ostream& operator<<(std::ostream& out, const Solution<TYPE_FITNESS>& s) {
		for(unsigned int i = 0; i < s.numberOfObjective(); i++) out << s.getFitness(i);
		return out;
	}

	void loadJson(const std::string& strJson);

	void loadJson(const Json::Value& jsonValue);

	Json::Value asJson() const;

  protected:
	unsigned int _number_of_objective;		   ///< number of objectif
	std::unique_ptr<TYPE_FITNESS[]> _fitness;  ///< list of fitness
	std::unique_ptr<bool[]> _fitness_is_valid; ///< list of the fitness state
};

} // namespace stocos
#endif