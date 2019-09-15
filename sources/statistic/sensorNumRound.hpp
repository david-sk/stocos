/// 
/// @file sensorNumRound.hpp
/// @author Jxtopher
/// @brief 
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
///

#ifndef SENSORNUMROUND_H
#define SENSORNUMROUND_H


#include "sensor.hpp"
namespace stocos 
{

template<class SOL>
class SensorNumRound : public Sensor<SOL> {
public:
    SensorNumRound() : Sensor<SOL>() {
        numRound = 0;
    }

    virtual ~SensorNumRound() {

    }

    void apply(const SOL &s) {
        numRound++;
    }
    
    Json::Value asJson() const {
        return Json::Value(numRound);
    }

    Json::Value finish() {
        return Json::Value();
    }

    std::string name() const {
        return std::string("round");
    }

private:
    unsigned int numRound;
};

}

#endif