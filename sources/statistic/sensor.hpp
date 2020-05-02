///
/// @file sensor.hpp
/// @author Jxtopher
/// @brief
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///
///
#ifndef SENSOR_H
#define SENSOR_H

#include <jsoncpp/json/json.h>

namespace stocos {

template<class SOL> class Sensor {
  public:
	Sensor() {}

	virtual ~Sensor() {}

	virtual void apply(const SOL& s) = 0;
	virtual Json::Value asJson() const = 0;
	virtual Json::Value finish() = 0;
	virtual std::string name() const = 0;

  private:
};

} // namespace stocos

#endif