///
/// @file solutionArray.hpp
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
#include "solution.h"

namespace stocos {

template<typename TYPE_FITNESS, typename TYPE_CELL>
class SolutionArray : public Solution<TYPE_FITNESS> {
  public:
	SolutionArray();

	SolutionArray(const unsigned int sizeArray);

	SolutionArray(const unsigned int numberOfObjective, const unsigned int sizeArray);

	SolutionArray(const SolutionArray& s);

	SolutionArray(const Json::Value& jsonValue);

	SolutionArray(const std::string& solution);

	~SolutionArray();

	SolutionArray& operator=(const SolutionArray& s);

	bool operator==(const SolutionArray& s) const;

	void operator()(const unsigned int index, const TYPE_CELL value);

	TYPE_CELL operator()(const unsigned int index) const;

	unsigned int sizeArray() const;

	// --------------------------------------------------------------------
	friend std::ostream& operator<<(std::ostream& out,
									SolutionArray<TYPE_FITNESS, TYPE_CELL> const& s) {
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

  private:
	std::unique_ptr<TYPE_CELL[]> array;
	unsigned int _sizeArray;
};

} // namespace stocos
#endif