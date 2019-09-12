///
/// @file sensorStopwatch.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief Stop watch
///

#ifndef STOPWATCH_H
#define	STOPWATCH_H

#include <iostream>
#include <chrono>
#include <ctime>

#include "sensor.hpp"



template<class SOL>
class SensorStopwatch : public Sensor<SOL> {
public:
	SensorStopwatch() : Sensor<SOL>() {
		start();
	}
	
	virtual ~SensorStopwatch() {

	}
	
	void start() {
		_start_minutes = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now().time_since_epoch());
		_start_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch());
	}
	
	void stop() {
        _end_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch());
		_end_minutes = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now().time_since_epoch());
	}
	
	int diff_microseconds() {
		std::chrono::microseconds ms = _end_microseconds - _start_microseconds;
		return ms.count();
	}

	int diff_minutes() {
		std::chrono::microseconds m = _end_minutes - _start_minutes;
		return m.count();
	}

    void apply(const SOL &s) {
		stop();
    }

    Json::Value asJson() const {
		std::chrono::microseconds microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch());
		std::chrono::microseconds minutes = std::chrono::duration_cast<std::chrono::minutes>(std::chrono::steady_clock::now().time_since_epoch());

		std::chrono::microseconds ms = microseconds - _start_microseconds;
        return Json::Value(static_cast<int>(ms.count()));
    }
		
    Json::Value finish() {
        //out<<"Time: " <<diff_minutes()<<"m "<<diff_microseconds()<<"μs";
		return Json::Value();
    }

    std::string name() const {
        return std::string("time_μs");
    }
	
protected:
	std::chrono::microseconds _start_microseconds;
	std::chrono::microseconds _end_microseconds;
	std::chrono::minutes _start_minutes;
	std::chrono::minutes _end_minutes;
};
#endif	/* STOPWATCH_H */