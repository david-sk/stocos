///
/// @file sensorStopwatch.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Stop watch
///
#include <statistic/sensorStopwatch.h>

namespace stocos {

template<class SOL>
SensorStopwatch<SOL>::SensorStopwatch() : Sensor<SOL>() {
	start();
}

template<class SOL>
SensorStopwatch<SOL>::~SensorStopwatch() {
}

template<class SOL>
void SensorStopwatch<SOL>::start() {
	_start_minutes = std::chrono::duration_cast<std::chrono::minutes>(
		std::chrono::steady_clock::now().time_since_epoch());
	_start_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::steady_clock::now().time_since_epoch());
}

template<class SOL>
void SensorStopwatch<SOL>::stop() {
	_end_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(
		std::chrono::steady_clock::now().time_since_epoch());
	_end_minutes = std::chrono::duration_cast<std::chrono::minutes>(
		std::chrono::steady_clock::now().time_since_epoch());
}

template<class SOL>
int SensorStopwatch<SOL>::diff_microseconds() {
	std::chrono::microseconds ms = _end_microseconds - _start_microseconds;
	return ms.count();
}

template<class SOL>
int SensorStopwatch<SOL>::diff_minutes() {
	std::chrono::microseconds m = _end_minutes - _start_minutes;
	return m.count();
}

template<class SOL>
void SensorStopwatch<SOL>::apply(const SOL& s) {
	stop();
}

template<class SOL>
Json::Value SensorStopwatch<SOL>::asJson() const {
	std::chrono::microseconds microseconds =
		std::chrono::duration_cast<std::chrono::microseconds>(
			std::chrono::steady_clock::now().time_since_epoch());
	std::chrono::microseconds minutes = std::chrono::duration_cast<std::chrono::minutes>(
		std::chrono::steady_clock::now().time_since_epoch());

	std::chrono::microseconds ms = microseconds - _start_microseconds;
	return Json::Value(static_cast<int>(ms.count()));
}

template<class SOL>
Json::Value SensorStopwatch<SOL>::finish() {
	// out<<"Time: " <<diff_minutes()<<"m "<<diff_microseconds()<<"μs";
	return Json::Value();
}

template<class SOL>
std::string SensorStopwatch<SOL>::name() const {
	return std::string("time_μs");
}

} // namespace stocos