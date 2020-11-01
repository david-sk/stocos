///
/// @file sensorFitness.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///

#include <statistic/sensorFitness.h>

namespace stocos {

template<class SOL>
SensorFitness<SOL>::SensorFitness() : Sensor<SOL>() {
}
template<class SOL>
SensorFitness<SOL>::~SensorFitness() {
}
template<class SOL>
void SensorFitness<SOL>::apply(const SOL& s) {
    solution = s;
}
template<class SOL>
Json::Value SensorFitness<SOL>::asJson() const {
    return solution.asJson()["fitness"];
}
template<class SOL>
Json::Value SensorFitness<SOL>::finish() {
    return Json::Value();
}
template<class SOL>
std::string SensorFitness<SOL>::name() const {
    return std::string("Fitness");
}

template class SensorFitness<Fitness<int>>;
template class SensorFitness<Solution<double, double>>;
template class SensorFitness<Solution<double, bool>>;
template class SensorFitness<Solution<int, bool>>;
template class SensorFitness<Solution<unsigned int, bool>>;
template class SensorFitness<Solution<double, unsigned int>>;
template class SensorFitness<Solution<unsigned int, unsigned int>>;

} // namespace stocos
