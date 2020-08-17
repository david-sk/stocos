///
/// @file sensorNameCallingClass.hpp
/// @author Jxtopher
/// @brief Show statistics summary at a final optimisation
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-24
///

#ifndef SENSORNAMECALLINGCLASS_H
#define SENSORNAMECALLINGCLASS_H

#include <string>

#include <jsoncpp/json/json.h>

#include "sensor.h"
#include "sensorNumRound.h"
#include "sensorStopwatch.h"

namespace stocos {

template<class SOL>
class SensorNameCallingClass : public Sensor<SOL> {
  public:
	SensorNameCallingClass();
	virtual ~SensorNameCallingClass();

	void apply(const SOL& s);

	Json::Value asJson() const;

	Json::Value finish();

	std::string name() const;

  private:
	SOL solution_best;
};

} // namespace stocos
#endif