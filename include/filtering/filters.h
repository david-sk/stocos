#ifndef FILTERS_H
#define FILTERS_H

#include <unordered_set>

#include "../solution/solution.h"

namespace stocos {

template<typename SOL>
class Filters : public std::unordered_set<bool (*)(const SOL&)> {
  public:
    bool operator()(const SOL& s) const;
};

} // namespace stocos

#endif
