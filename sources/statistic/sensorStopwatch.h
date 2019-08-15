///
/// @file criteria.h
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

#include "sensor.h"

using namespace std;

template<class SOL>
class SensorStopwatch : public Sensor<SOL> {
public:
	SensorStopwatch() : Sensor<SOL>() {
		start();
	}
	
	virtual ~SensorStopwatch() {

	}
	
	void start() {
		_start_minutes = chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now().time_since_epoch());
		_start_microseconds = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch());
	}
	
	void stop() {
        _end_microseconds = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch());
				_end_minutes = chrono::duration_cast<chrono::minutes>(chrono::steady_clock::now().time_since_epoch());
	}
	
	int diff_microseconds() {
		chrono::microseconds ms = _end_microseconds - _start_microseconds;
		return ms.count();
	}

	int diff_minutes() {
		chrono::microseconds m = _end_minutes - _start_minutes;
		return m.count();
	}

    void operator()(std::stringstream &out, const SOL &s) {
		stop();
    }

		
    void finish(std::stringstream &out) {
        out<<"Time: " <<diff_minutes()<<"m "<<diff_microseconds()<<"μs";
    }
	
protected:
	chrono::microseconds _start_microseconds;
	chrono::microseconds _end_microseconds;
	chrono::minutes _start_minutes;
	chrono::minutes _end_minutes;
};
#endif	/* STOPWATCH_H */