///
/// @file population.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief 
///

#ifndef DOMAIN_H
#define DOMAIN_H

namespace stocos 
{

#include <unordered_set>

#include "solutionArray.hpp"

template <typename TYPE_CELL>
class Domain {
    public:
    // Domain(const Domain &dom) {
    // }

    /*/// 
    /// @brief Pour chaque cases definition d'un range,  intension
    /// 
    ///
    Domain(std::vector<std::tuple<TYPE_CELL, TYPE_CELL, TYPE_CELL>> range) {

    }



    virtual ~Domain() {

    }

    
    private:
        std::unordered_set<unsigned int> set;*/

public:

    void remove(TYPE_CELL element, unsigned int index);
    void pick_random(unsigned int index);
    // std::unordered_set get_domain(unsigned int index);

    


};

}
#endif