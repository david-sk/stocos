#ifndef SENSOR_H
#define SENSOR_H

#include <jsoncpp/json/json.h>

template<class SOL>
class Sensor {
public:
    Sensor() {

    }

    virtual ~Sensor() {

    }
    
    virtual void apply(const SOL &s) = 0;
    virtual Json::Value asJson() const = 0;
    virtual Json::Value finish() = 0;
    virtual std::string name() const = 0;

private:
};

#endif