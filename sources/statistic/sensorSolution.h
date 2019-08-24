#ifndef SENSORSOLTUTION_H
#define SENSORSOLTUTION_H


#include "../solution/solution.h"
#include "sensor.h"

template<class SOL>
class SensorSolution : public Sensor<SOL> {
public:
    SensorSolution() : Sensor<SOL>() {
        
    }

    virtual ~SensorSolution() {

    }

    void apply(const SOL &s) {
        solution = s;
    }

    Json::Value asJson() const {
        return solution.asJson();
    }

    Json::Value finish() {
        return Json::Value();
    }
    std::string name() const {
        return std::string("Solution");
    }
private:
    SOL solution;
};

#endif