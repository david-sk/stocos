/// 
/// @file sensorNameCallingClass.hpp
/// @author Jxtopher
/// @brief Show statistics summary at a final optimisation
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-24 
///

#ifndef SENSORNAMECALLINGCLASS_H
#define SENSORNAMECALLINGCLASS_H

#include "sensorStopwatch.hpp"
#include "sensorNumRound.hpp"
#include "sensor.hpp"

namespace stocos 
{

template<class SOL>
class SensorNameCallingClass : public Sensor<SOL> {
public:
    SensorNameCallingClass() : Sensor<SOL>()  {

    }

    virtual ~SensorNameCallingClass() {
    }

    void apply(const SOL &s) {
    }
    
    Json::Value asJson() const {
        return Json::Value();
    }

    Json::Value finish() {
        return Json::Value();
    }


    std::string name() const {
        return std::string("nameCallingClass");
    }

private:
    SOL solution_best;
};

}
#endif