///
/// @file sensorSolution.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///
#include <statistic/sensorSolution.h>

namespace stocos {

template<class SOL>
SensorSolution<SOL>::SensorSolution() : Sensor<SOL>() {
}

template<class SOL>
SensorSolution<SOL>::~SensorSolution() {
}

template<class SOL>
void SensorSolution<SOL>::apply(const SOL& s) {
	solution = s;
}

template<class SOL>
Json::Value SensorSolution<SOL>::asJson() const {
	return solution.asJson();
}

template<class SOL>
Json::Value SensorSolution<SOL>::finish() {
	return Json::Value();
}

template<class SOL>
std::string SensorSolution<SOL>::name() const {
	return std::string("Solution");
}

} // namespace stocos