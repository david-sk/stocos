///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef OPERATION_FLIPBIT_H
#define OPERATION_FLIPBIT_H

#include <memory> // std::shared_ptr std::unique_ptr
#include <random> // std::mt19937
#include <vector> // std::vector

#include "../../../../solution/solution.h"

#include "../atomicOperation.h"

namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class FlipBit : public AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL> {
  public:
    FlipBit(std::mt19937& mt_rand, unsigned int c);
    virtual ~FlipBit();

    void operator()(SOL& s);

    void cancelMutations(SOL& s) const;

    std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> listOfMutations(const SOL& s);

    void applyOperator(SOL& s,
                       const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations);

  private:
    const unsigned int _c; // < parameter c
    unsigned int N;
    std::unique_ptr<std::uniform_real_distribution<>> urd;
    double mutation_rate;

    std::vector<unsigned int> backup;
};

} // namespace stocos
#endif