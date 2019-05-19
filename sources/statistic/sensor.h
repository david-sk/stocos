#ifndef SENSOR_H
#define SENSOR_H



template<class SOL>
class Sensor {
public:
    Sensor() {

    }

    virtual ~Sensor() {

    }
    
    virtual void operator()(std::stringstream &out, SOL const &s) = 0;
    virtual void finish(std::stringstream &out) = 0;

private:
};

#endif