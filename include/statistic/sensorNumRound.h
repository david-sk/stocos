///
/// @file sensorNumRound.hpp
/// @author Jxtopher
/// @version 0.1
/// @copyright CC-BY-NC-SA
/// @date 2019-08-30
/// @brief
///

#ifndef SENSORNUMROUND_H
#define SENSORNUMROUND_H

#include <string>

#include <jsoncpp/json/json.h>

#include "../solution/solution.h"
#include "sensor.h"

namespace stocos {

template<class SOL>
class SensorNumRound : public Sensor<SOL> {
  public:
    SensorNumRound();

    virtual ~SensorNumRound();

    void apply(const SOL& s);

    Json::Value asJson() const;

    Json::Value finish();

    std::string name() const;

  private:
    unsigned int numRound;
};

} // namespace stocos

#endif