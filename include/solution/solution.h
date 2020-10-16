///
/// @file solution.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef SOLUTIONARRAY_H
#define SOLUTIONARRAY_H

#include <cassert>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

#include "domain.h"
#include "fitness.h"

namespace stocos {

template<typename TYPE_FITNESS, typename TYPE_CELL>
class Solution : public Fitness<TYPE_FITNESS>, private std::vector<TYPE_CELL> {
  public:
	Solution(const unsigned int sizeArray = 1, const unsigned int numberOfObjective = 1);

	Solution(const Solution& s);

	Solution(const Json::Value& jsonValue);

	Solution(const std::string& solution);

	~Solution();

	Solution& operator=(const Solution& s);

	bool operator==(const Solution& s) const;

	void operator()(const unsigned int index, const TYPE_CELL value);

	TYPE_CELL operator()(const unsigned int index) const;

	unsigned int sizeArray() const;

	// --------------------------------------------------------------------
	friend std::ostream& operator<<(std::ostream& out,
									Solution<TYPE_FITNESS, TYPE_CELL> const& s) {
		for(unsigned int i = 0; i < s.numberOfObjective(); i++) out << s.getFitness(i) << " ";
		out << ": ";
		for(unsigned int i = 0; i < s.sizeArray(); i++) out << s(i) << " ";
		return out;
	}

	void loadJson(const std::string& strJson);
	void loadJson(const Json::Value& jsonValue);

	///
	/// @return the solution in JSON format
	///
	Json::Value asJson() const;
};

} // namespace stocos
#endif