///
/// @file sensorSolution.hpp
/// @author Jxtopher
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
/// @brief Capture the current solution
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

template class SensorSolution<Solution<int>>;
template class SensorSolution<SolutionArray<double, double>>;
template class SensorSolution<SolutionArray<double, bool>>;
template class SensorSolution<SolutionArray<int, bool>>;
template class SensorSolution<SolutionArray<unsigned int, bool>>;
template class SensorSolution<SolutionArray<double, unsigned int>>;
template class SensorSolution<SolutionArray<unsigned int, unsigned int>>;
} // namespace stocos