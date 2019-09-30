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

template <typename TYPE_FITNESS, typename TYPE_CELL>
class Domain : public SolutionArray<TYPE_FITNESS, TYPE_CELL> {
    public:
    /// 
    /// @brief Pour tout les cases, give a range [a, b], avec un pas de n,  intension
    /// 
    ///
    Domain(const unsigned int numberOfObjective, const unsigned int sizeArray) :
        SolutionArray<TYPE_FITNESS, TYPE_CELL>(numberOfObjective, sizeArray) {

    }

    Domain(const Domain &dom) : 
		SolutionArray<TYPE_FITNESS, TYPE_CELL>(dom) {
    }

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