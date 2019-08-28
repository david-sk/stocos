///
/// @file selection.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef SOLUTION_SELECTION_H
#define SOLUTION_SELECTION_H

#include "../solution/population.h"

template<class SOL>
class SolutionSelection {
    public:
    SolutionSelection() {

    }

    virtual ~SolutionSelection() {

    }

    virtual inline bool operator()(const SOL &s1, const SOL &s2, const unsigned int numObjectif = 0) const = 0;
    virtual inline unsigned int operator()(const Population<SOL> &p) const = 0;
};

#endif