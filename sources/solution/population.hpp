///
/// @file population.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief 
///

#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include "solution.hpp"



template<typename SOL>
class Population : public Solution<double>,  public std::vector<SOL> {
    public:
    Population() {

    }

    virtual ~Population() {

    }
    
    private:
};

#endif