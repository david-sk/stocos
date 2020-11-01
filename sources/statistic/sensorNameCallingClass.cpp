///
/// @file sensorNameCallingClass.hpp
/// @author Jxtopher
/// @brief Show statistics summary at a final optimisation
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-24
///
#include <statistic/sensorNameCallingClass.h>

namespace stocos {

template<class SOL>
SensorNameCallingClass<SOL>::SensorNameCallingClass() : Sensor<SOL>() {
}

template<class SOL>
SensorNameCallingClass<SOL>::~SensorNameCallingClass() {
}

template<class SOL>
void SensorNameCallingClass<SOL>::apply(const SOL& s) {
}

template<class SOL>
Json::Value SensorNameCallingClass<SOL>::asJson() const {
    return Json::Value();
}

template<class SOL>
Json::Value SensorNameCallingClass<SOL>::finish() {
    return Json::Value();
}

template<class SOL>
std::string SensorNameCallingClass<SOL>::name() const {
    return std::string("nameCallingClass");
}

template class SensorNameCallingClass<Fitness<int>>;
template class SensorNameCallingClass<Solution<double, double>>;
template class SensorNameCallingClass<Solution<double, bool>>;
template class SensorNameCallingClass<Solution<int, bool>>;
template class SensorNameCallingClass<Solution<unsigned int, bool>>;
template class SensorNameCallingClass<Solution<double, unsigned int>>;
template class SensorNameCallingClass<Solution<unsigned int, unsigned int>>;

} // namespace stocos
