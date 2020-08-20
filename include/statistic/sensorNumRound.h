///
/// @file sensorNumRound.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///

#ifndef SENSORNUMROUND_H
#define SENSORNUMROUND_H

#include <string>

#include <jsoncpp/json/json.h>

#include "../solution/solutionArray.h"
#include "sensor.h"

namespace stocos {

template<class SOL>
class SensorNumRound : public Sensor<SOL> {
  public:
	SensorNumRound();

	virtual ~SensorNumRound();

	void apply(const SOL& s);

	Json::Value asJson() const;
	Json::Value finish();

	std::string name() const;

  private:
	unsigned int numRound;
};

} // namespace stocos

#endif