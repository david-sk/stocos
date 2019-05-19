#ifndef SENSORSOLTUTION_H
#define SENSORSOLTUTION_H


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

    void finish(std::stringstream &out) {
        
    }

private:
};

#endif