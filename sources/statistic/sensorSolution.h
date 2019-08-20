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

    void operator()(std::stringstream &out, const SOL &s) {
        out<<s;
    }

    Json::Value asJson(const SOL &s) {
        return s.asJson();
    }

    void finish(std::stringstream &out) {
        
    }
    std::string name() const {
        return std::string("Solution");
    }
private:
};

#endif