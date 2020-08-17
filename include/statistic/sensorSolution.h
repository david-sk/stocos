///
/// @file sensorSolution.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///

#ifndef SENSORSOLTUTION_H
#define SENSORSOLTUTION_H

#include <string>

#include <jsoncpp/json/json.h>

#include "../solution/solution.h"
#include "sensor.h"

namespace stocos {

template<class SOL>
class SensorSolution : public Sensor<SOL> {
  public:
	SensorSolution();

	virtual ~SensorSolution();

	void apply(const SOL& s) ;
	Json::Value asJson() const;

	Json::Value finish();
	std::string name() const;

  private:
	SOL solution;
};

} // namespace stocos
#endif