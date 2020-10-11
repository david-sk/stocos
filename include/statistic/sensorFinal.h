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

#include "../solution/solutionArray.h"
#include "sensor.h"
#include "sensorNumRound.h"
#include "sensorStopwatch.h"

namespace stocos {

template<class SOL>
class SensorFinal : public Sensor<SOL> {
  public:
	SensorFinal(unsigned int num, const std::string& name = "");

	virtual ~SensorFinal();

	void apply(const SOL& s);

	Json::Value asJson() const;

	Json::Value finish();

	std::string name() const;

  private:
	SensorStopwatch<SOL> stopwatch;
	SensorNumRound<SOL> numRound;
	unsigned int _num;
	std::string _name;
	SOL solution_best;
};

} // namespace stocos
#endif