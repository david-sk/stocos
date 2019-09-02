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
    /// @brief Pour tout les cases, give a range [a, b]
    /// 
    ///
    Domain(std::pair<TYPE_CELL, TYPE_CELL>) {

    }

    /// 
    /// @brief Pour toutes les cases, give exhautive list
    /// 
    ///
    Domain(std::vector<TYPE_CELL>) {

    }

    /// 
    /// @brief Pour chaque cases
    /// 
    ///
    Domain(std::vector<std::pair<TYPE_CELL, TYPE_CELL>>) {

    }

    /// 
    /// @brief Pour chaque cases
    /// 
    ///
    Domain(std::vector<std::vector<TYPE_CELL>>) {

    }

    virtual ~Domain() {

    }
    
    private:
};

#endif