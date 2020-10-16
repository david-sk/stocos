///
/// @file solution.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <solution/solution.h>

namespace stocos {

template<typename TYPE_FITNESS, typename TYPE_CELL>
Solution<TYPE_FITNESS, TYPE_CELL>::Solution(const unsigned int sizeArray, const unsigned int numberOfObjective)
	: Fitness<TYPE_FITNESS>(numberOfObjective), std::vector<TYPE_CELL>(sizeArray) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation Solution";
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
Solution<TYPE_FITNESS, TYPE_CELL>::Solution(const Solution& s)
	: Fitness<TYPE_FITNESS>(s), std::vector<TYPE_CELL>(s) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation Solution";
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
Solution<TYPE_FITNESS, TYPE_CELL>::Solution(const Json::Value& jsonValue)
	: Fitness<TYPE_FITNESS>(jsonValue) {
	loadJson(jsonValue);
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
Solution<TYPE_FITNESS, TYPE_CELL>::Solution(const std::string& solution)
	: Fitness<TYPE_FITNESS>() {
	loadJson(solution);
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
Solution<TYPE_FITNESS, TYPE_CELL>::~Solution() {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Delete Solution";
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
Solution<TYPE_FITNESS, TYPE_CELL>& Solution<TYPE_FITNESS, TYPE_CELL>::
	operator=(const Solution& s) {
	Fitness<TYPE_FITNESS>::operator=(s);
	std::vector<TYPE_CELL>::operator=(s);
	return *this;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
bool Solution<TYPE_FITNESS, TYPE_CELL>::operator==(const Solution& s) const {
	if(this->size() != s.size())
		return false;
	else {
		for(unsigned int i = 0; i < s.sizeArray(); i++) {
			if(this->operator[](i) != s(i)) return false;
		}
	}
	return true;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
void Solution<TYPE_FITNESS, TYPE_CELL>::operator()(const unsigned int index,
														const TYPE_CELL value) {
	assert(index < this->size());
	if(this->operator[](index) != value) {
		for(unsigned int i = 0; i < this->_number_of_objective; i++)
			this->_fitness_is_valid[i] = false;
		this->operator[](index) = value;
	}
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
TYPE_CELL Solution<TYPE_FITNESS, TYPE_CELL>::operator()(const unsigned int index) const {
	assert(index < this->size());
	return this->operator[](index);
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
unsigned int Solution<TYPE_FITNESS, TYPE_CELL>::sizeArray() const {
	return this->size();
}

// --------------------------------------------------------------------
template<typename TYPE_FITNESS, typename TYPE_CELL>
void Solution<TYPE_FITNESS, TYPE_CELL>::loadJson(const std::string& strJson) {
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(strJson.c_str(), root); // parse process
	if(!parsingSuccessful)
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +
								 reader.getFormattedErrorMessages());
	loadJson(root);
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
void Solution<TYPE_FITNESS, TYPE_CELL>::loadJson(const Json::Value& jsonValue) {
	Fitness<TYPE_FITNESS>::loadJson(jsonValue);
	this->resize(jsonValue["solution"].size());
	for(unsigned int i = 0; i < jsonValue["solution"].size(); i++)
		this->operator[](i) = jsonValue["solution"][i].asDouble();
}

///
/// @return the solution in JSON format
///
template<typename TYPE_FITNESS, typename TYPE_CELL>
Json::Value Solution<TYPE_FITNESS, TYPE_CELL>::asJson() const {
	Json::Value jsonValue = Fitness<TYPE_FITNESS>::asJson();
	for(unsigned int i = 0; i < this->size(); i++) jsonValue["solution"].append(this->operator[](i));
	return jsonValue;
}

template class Solution<double, double>;
template class Solution<double, bool>;
template class Solution<int, bool>;
template class Solution<unsigned int, bool>;
template class Solution<double, unsigned int>;
template class Solution<unsigned int, unsigned int>;
template class Solution<int, int>;

} // namespace stocos