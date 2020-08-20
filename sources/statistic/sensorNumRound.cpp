///
/// @file sensorNumRound.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///
#include <statistic/sensorNumRound.h>

namespace stocos {

template<class SOL>
SensorNumRound<SOL>::SensorNumRound() : Sensor<SOL>() {
	numRound = 0;
}

template<class SOL>
SensorNumRound<SOL>::~SensorNumRound() {
}

template<class SOL>
void SensorNumRound<SOL>::apply(const SOL& s) {
	numRound++;
}

template<class SOL>
Json::Value SensorNumRound<SOL>::asJson() const {
	return Json::Value(numRound);
}

template<class SOL>
Json::Value SensorNumRound<SOL>::finish() {
	return Json::Value();
}

template<class SOL>
std::string SensorNumRound<SOL>::name() const {
	return std::string("round");
}

template class SensorNumRound<Solution<int>>;
template class SensorNumRound<SolutionArray<double, double>>;
template class SensorNumRound<SolutionArray<double, bool>>;
template class SensorNumRound<SolutionArray<int, bool>>;
template class SensorNumRound<SolutionArray<unsigned int, bool>>;
template class SensorNumRound<SolutionArray<double, unsigned int>>;
template class SensorNumRound<SolutionArray<unsigned int, unsigned int>>;

} // namespace stocos