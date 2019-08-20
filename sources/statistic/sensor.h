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
    
    virtual void operator()(std::stringstream &out, const SOL &s) = 0;
    virtual Json::Value asJson(const SOL &s) = 0;
    virtual void finish(std::stringstream &out) = 0;
    virtual std::string name() const = 0;

private:
};

#endif