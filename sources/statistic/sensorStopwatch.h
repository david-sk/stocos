///
/// \file criteria.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief Stop watch
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
		_start = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch());
	}
	
	void stop() {
        _end = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now().time_since_epoch());
	}
	
	int diff() {
		chrono::microseconds ms = _end - _start;
		return ms.count();
	}

    void operator()(std::stringstream &out, const SOL &s) {
		stop();
    }

    void finish(std::stringstream &out) {
        out<<"Time: " <<diff()<<"ms";
    }
	
protected:
	chrono::microseconds _start;
	chrono::microseconds _end;
};
#endif	/* STOPWATCH_H */