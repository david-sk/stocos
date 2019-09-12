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


#include "../solution/solution.hpp"
#include "sensor.hpp"

template<class SOL>
class SensorFitness : public Sensor<SOL> {
public:
    SensorFitness() : Sensor<SOL>() {
        
    }

    virtual ~SensorFitness() {

    }

    void apply(const SOL &s) {
        solution = s;
    }

    Json::Value asJson() const {
        Json::Value x = solution.asJson();
        return x["fitness"];
    }

    Json::Value finish() {
        return Json::Value();
    }
    std::string name() const {
        return std::string("Fitness");
    }
private:
    SOL solution;
};

#endif