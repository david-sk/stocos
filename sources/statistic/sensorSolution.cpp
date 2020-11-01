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

template class SensorSolution<Fitness<int>>;
template class SensorSolution<Solution<double, double>>;
template class SensorSolution<Solution<double, bool>>;
template class SensorSolution<Solution<int, bool>>;
template class SensorSolution<Solution<unsigned int, bool>>;
template class SensorSolution<Solution<double, unsigned int>>;
template class SensorSolution<Solution<unsigned int, unsigned int>>;
} // namespace stocos