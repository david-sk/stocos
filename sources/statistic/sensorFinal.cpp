///
/// @file sensorFinal.hpp
/// @author Jxtopher
/// @brief Show statistics summary at a final optimisation
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-24
///
#include <statistic/sensorFinal.h>

namespace stocos {

template<class SOL>
SensorFinal<SOL>::SensorFinal(unsigned int num, const std::string& name)
	: Sensor<SOL>(), _num(num), _name(name) {
	stopwatch.start();
}

template<class SOL>
SensorFinal<SOL>::~SensorFinal() {
	stopwatch.stop();
}

template<class SOL>
void SensorFinal<SOL>::apply(const SOL& s) {
	numRound.apply(s);
	solution_best = s;
}

template<class SOL>
Json::Value SensorFinal<SOL>::asJson() const {
	return Json::Value();
}

template<class SOL>
Json::Value SensorFinal<SOL>::finish() {
	Json::Value r;
	r[stopwatch.name()] = stopwatch.asJson();
	r[numRound.name()] = numRound.asJson();
	r["Solution"] = solution_best.asJson();

	Json::Value exp;
	exp["name"] = _name;
	exp["number"] = _num;
	r["experience"] = exp;
	return r;
}

template<class SOL>
std::string SensorFinal<SOL>::name() const {
	return std::string("final");
}

template class SensorFinal<Solution<int>>;
template class SensorFinal<SolutionArray<double, double>>;
template class SensorFinal<SolutionArray<double, bool>>;
template class SensorFinal<SolutionArray<int, bool>>;
template class SensorFinal<SolutionArray<unsigned int, bool>>;
template class SensorFinal<SolutionArray<double, unsigned int>>;
template class SensorFinal<SolutionArray<unsigned int, unsigned int>>;

} // namespace stocos