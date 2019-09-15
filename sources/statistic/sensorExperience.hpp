/// 
/// @file sensorExperience.hpp
/// @author Jxtopher
/// @brief 
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///

#ifndef SENSOREXPERIENCE_H
#define SENSOREXPERIENCE_H

#include <string>   // std::string

#include <jsoncpp/json/json.h>

#include "sensor.hpp"

namespace stocos 
{

template<class SOL>
class SensorExperience : public Sensor<SOL> {
public:
    SensorExperience(unsigned int num, std::string name = "") : 
        _num(num), _name(name) {
    }

    virtual ~SensorExperience() {

    }

    void apply(const SOL &s) {
    }
    
    Json::Value asJson() const {
        Json::Value exp;
        exp["name"] = _name;
        exp["number"] = _num;
        return exp;
    }

    Json::Value  finish() {
        return Json::Value();
    }

    std::string name() const {
        return std::string("experience");
    }

private:
    unsigned int _num;
    std::string _name;
};

}
#endif