///
/// \file unitTest_population.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2019-05
/// \brief 
///

#ifndef POPULATION_H
#define POPULATION_H

#include <list>
#include "solution.h"

using namespace std;

template<typename SOL>
class Population : public Solution<bool>,  public list<SOL> {
    public:
    Population() {

    }

    virtual ~Population() {

    }


    private:
};

#endif