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

#include "solution.hpp"


template <typename TYPE_CELL>
// template<typename SOL>
class Domain {
    public:
    /// 
    /// @brief Pour tout les cases, give a range [a, b], pas
    /// 
    ///
    Domain(std::tuple<TYPE_CELL, TYPE_CELL, TYPE_CELL> range) {

    }

    /// 
    /// @brief Pour toutes les cases, give exhautive list
    /// 
    ///
    Domain(std::vector<TYPE_CELL> exhaustive_list) {

    }

    /// 
    /// @brief Pour chaque cases
    /// 
    ///
    Domain(std::vector<std::tuple<TYPE_CELL, TYPE_CELL, TYPE_CELL>> range) {

    }

    /// 
    /// @brief Pour chaque cases
    /// 
    ///
    Domain(std::vector<std::vector<TYPE_CELL>> exhaustive_list) {

    }

    virtual ~Domain() {

    }
    
    private:
};

#endif