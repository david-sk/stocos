///
/// @file sensorFinal.hpp
/// @author Jxtopher
/// @brief Show statistics summary at a final optimisation
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-24
///

#ifndef SENSORFINAL_H
#define SENSORFINAL_H

#include <string>

#include <jsoncpp/json/json.h>

#include "sensor.hpp"
#include "sensorNumRound.hpp"
#include "sensorStopwatch.hpp"

namespace stocos {

template<class SOL>
class SensorFinal : public Sensor<SOL> {
  public:
	SensorFinal(unsigned int num, const std::string &name = "") : Sensor<SOL>(), _num(num), _name(name) {
		stopwatch.start();
	}

	virtual ~SensorFinal() {
		stopwatch.stop();
	}

	void apply(const SOL& s) {
		numRound.apply(s);
		solution_best = s;
	}

	Json::Value asJson() const {
		return Json::Value();
	}

	Json::Value finish() {
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

	std::string name() const {
		return std::string("final");
	}

  private:
	SensorStopwatch<SOL> stopwatch;
	SensorNumRound<SOL> numRound;
	unsigned int _num;
	std::string _name;
	SOL solution_best;
};

} // namespace stocos
#endif