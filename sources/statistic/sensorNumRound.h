#ifndef SENSORNUMROUND_H
#define SENSORNUMROUND_H


#include "sensor.h"

template<class SOL>
class SensorNumRound : public Sensor<SOL> {
public:
    SensorNumRound() : Sensor<SOL>() {
        numRound = 0;
    }

    virtual ~SensorNumRound() {

    }

    void operator()(std::stringstream &out, const SOL &s) {
        out<<numRound++;
    }

    void finish(std::stringstream &out) {
        
    }


private:
    unsigned int numRound;
};

#endif