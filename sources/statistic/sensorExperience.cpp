///
/// @file sensorExperience.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///
#include <statistic/sensorExperience.h>

namespace stocos {

template<class SOL>
SensorExperience<SOL>::SensorExperience(unsigned int num, const std::string &name) : _num(num), _name(name) {
}

template<class SOL>
SensorExperience<SOL>::~SensorExperience() {
}

template<class SOL>
void SensorExperience<SOL>::apply(const SOL& s) {
}

template<class SOL>
Json::Value SensorExperience<SOL>::asJson() const {
	Json::Value exp;
	exp["name"] = _name;
	exp["number"] = _num;
	return exp;
}

template<class SOL>
Json::Value SensorExperience<SOL>::finish() {
	return Json::Value();
}

template<class SOL>
std::string SensorExperience<SOL>::name() const {
	return std::string("experience");
}

} // namespace stocos