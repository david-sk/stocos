///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief intervalle real [a,b]
///

#ifndef OPERATION_INTERVALREAL_H
#define OPERATION_INTERVALREAL_H

#include <memory> // std::shared_ptr std::unique_ptr
#include <random>
#include <vector>

#include "../../../../solution/solution.h"

#include "../atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class IntervalReal : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
    IntervalReal(std::mt19937& mt_rand, unsigned int c, double a, double b);
    virtual ~IntervalReal();

    void operator()(SOL& s);

  private:
    const unsigned int _c; // < Nombre de case à mute / arraySize
    const unsigned int _a; // < Lower bound
    const unsigned int _b; // < Upper bollard
    std::unique_ptr<std::uniform_real_distribution<>> urd_0_1;
    std::unique_ptr<std::uniform_real_distribution<>> urd;
    double mutation_rate;
    unsigned int N;
    std::vector<unsigned int> backup;
};

} // namespace stocos
#endif