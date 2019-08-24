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

#endif