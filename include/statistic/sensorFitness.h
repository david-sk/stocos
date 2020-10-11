///
/// @file sensorFitness.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///

#ifndef SENSORFITNESS_H
#define SENSORFITNESS_H

#include <string>

#include <jsoncpp/json/json.h>

#include "../solution/solution.h"
#include "../solution/solutionArray.h"
#include "sensor.h"

namespace stocos {

template<class SOL>
class SensorFitness : public Sensor<SOL> {
  public:
	SensorFitness();

	virtual ~SensorFitness();

	void apply(const SOL& s);

	Json::Value asJson() const;

	Json::Value finish();

	std::string name() const;

  private:
	SOL solution;
};

} // namespace stocos
#endif