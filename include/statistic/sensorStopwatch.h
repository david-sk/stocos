///
/// @file sensorStopwatch.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Stopwatch the execution time of a block
///

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>
#include <ctime>
#include <iostream>

#include <jsoncpp/json/json.h>

#include "../solution/solutionArray.h"
#include "sensor.h"

namespace stocos {

template<class SOL>
class SensorStopwatch : public Sensor<SOL> {
  public:
	SensorStopwatch();

	virtual ~SensorStopwatch();

	void start();

	void stop();

	int diff_microseconds();

	int diff_minutes();
	
	void apply(const SOL& s);

	Json::Value asJson() const;

	Json::Value finish();

	std::string name() const;

  protected:
	std::chrono::microseconds _start_microseconds;
	std::chrono::microseconds _end_microseconds;
	std::chrono::minutes _start_minutes;
	std::chrono::minutes _end_minutes;
};

} // namespace stocos
#endif /* STOPWATCH_H */