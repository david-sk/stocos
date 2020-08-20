///
/// @file solutionArray.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <solution/solutionArray.h>

namespace stocos {

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>::SolutionArray() : Solution<TYPE_FITNESS>(1), _sizeArray(1) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation SolutionArray";
	array = std::make_unique<TYPE_CELL[]>(_sizeArray);
	// domain = nullptr;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>::SolutionArray(const unsigned int sizeArray)
	: Solution<TYPE_FITNESS>(1), _sizeArray(sizeArray) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation SolutionArray";
	array = std::make_unique<TYPE_CELL[]>(_sizeArray);
	// domain = nullptr;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>::SolutionArray(const unsigned int numberOfObjective,
													  const unsigned int sizeArray)
	: Solution<TYPE_FITNESS>(numberOfObjective), _sizeArray(sizeArray) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation SolutionArray";
	array = std::make_unique<TYPE_CELL[]>(_sizeArray);
	// domain = nullptr;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>::SolutionArray(const SolutionArray& s)
	: Solution<TYPE_FITNESS>(s), _sizeArray(s._sizeArray) {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Creation SolutionArray";

	array = std::make_unique<TYPE_CELL[]>(_sizeArray);
	for(unsigned int i = 0; i < _sizeArray; i++) array[i] = s.array[i];

	// domain = s.domain;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>::SolutionArray(const Json::Value& jsonValue)
	: Solution<TYPE_FITNESS>(jsonValue), array(nullptr), _sizeArray(0) {
	loadJson(jsonValue);
	// ! loadJson for dom ?
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>::SolutionArray(const std::string& solution)
	: Solution<TYPE_FITNESS>(), array(nullptr), _sizeArray(0) {
	loadJson(solution);
	// ! loadJson for dom ?
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>::~SolutionArray() {
	BOOST_LOG_TRIVIAL(debug) << __FILE__ << ":" << __LINE__ << " Delete SolutionArray";
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
SolutionArray<TYPE_FITNESS, TYPE_CELL>& SolutionArray<TYPE_FITNESS, TYPE_CELL>::
	operator=(const SolutionArray& s) {
	Solution<TYPE_FITNESS>::operator=(s);
	if(_sizeArray != s._sizeArray) {
		_sizeArray = s._sizeArray;
		array = std::make_unique<TYPE_CELL[]>(_sizeArray);
	}

	for(unsigned int i = 0; i < _sizeArray; i++) array[i] = s.array[i];

	return *this;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
bool SolutionArray<TYPE_FITNESS, TYPE_CELL>::operator==(const SolutionArray& s) const {
	if(sizeArray() != s.sizeArray())
		return false;
	else {
		for(unsigned int i = 0; i < s.sizeArray(); i++) {
			if(array[i] != s(i)) return false;
		}
	}
	return true;
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
void SolutionArray<TYPE_FITNESS, TYPE_CELL>::operator()(const unsigned int index,
														const TYPE_CELL value) {
	assert(index < _sizeArray);
	if(array[index] != value) {
		for(unsigned int i = 0; i < this->_number_of_objective; i++)
			this->_fitness_is_valid[i] = false;
		array[index] = value;
	}
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
TYPE_CELL SolutionArray<TYPE_FITNESS, TYPE_CELL>::operator()(const unsigned int index) const {
	assert(index < _sizeArray);
	return array[index];
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
unsigned int SolutionArray<TYPE_FITNESS, TYPE_CELL>::sizeArray() const {
	return _sizeArray;
}

// --------------------------------------------------------------------
template<typename TYPE_FITNESS, typename TYPE_CELL>
void SolutionArray<TYPE_FITNESS, TYPE_CELL>::loadJson(const std::string& strJson) {
	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(strJson.c_str(), root); // parse process
	if(!parsingSuccessful)
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " +
								 reader.getFormattedErrorMessages());
	loadJson(root);
}

template<typename TYPE_FITNESS, typename TYPE_CELL>
void SolutionArray<TYPE_FITNESS, TYPE_CELL>::loadJson(const Json::Value& jsonValue) {
	Solution<TYPE_FITNESS>::loadJson(jsonValue);
	_sizeArray = jsonValue["solution"].size();
	if(array == nullptr)
		array = std::make_unique<TYPE_CELL[]>(_sizeArray);
	else
		this->array.reset(static_cast<TYPE_CELL*>(realloc(static_cast<void*>(this->array.release()),
														  this->_sizeArray * sizeof(TYPE_CELL))));
	for(unsigned int i = 0; i < jsonValue["solution"].size(); i++)
		array[i] = jsonValue["solution"][i].asDouble();
}

///
/// @return the solution in JSON format
///
template<typename TYPE_FITNESS, typename TYPE_CELL>
Json::Value SolutionArray<TYPE_FITNESS, TYPE_CELL>::asJson() const {
	Json::Value jsonValue = Solution<TYPE_FITNESS>::asJson();
	for(unsigned int i = 0; i < _sizeArray; i++) jsonValue["solution"].append(array[i]);
	return jsonValue;
}

template class SolutionArray<double, double>;
template class SolutionArray<double, bool>;
template class SolutionArray<int, bool>;
template class SolutionArray<unsigned int, bool>;
template class SolutionArray<double, unsigned int>;
template class SolutionArray<unsigned int, unsigned int>;

} // namespace stocos