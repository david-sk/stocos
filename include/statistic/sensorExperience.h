///
/// @file sensorExperience.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///

#ifndef SENSOREXPERIENCE_H
#define SENSOREXPERIENCE_H

#include <string> // std::string

#include <jsoncpp/json/json.h>

#include "sensor.h"
#include "../solution/solutionArray.h"

namespace stocos {

template<class SOL>
class SensorExperience : public Sensor<SOL> {
  public:
	SensorExperience(unsigned int num, const std::string &name = "");

	virtual ~SensorExperience();

	void apply(const SOL& s);

	Json::Value asJson() const;

	Json::Value finish();

	std::string name() const;

  private:
	unsigned int _num;
	std::string _name;
};

} // namespace stocos
#endif