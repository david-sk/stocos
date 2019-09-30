/// 
/// @file domDiscrete.hpp
/// @author Jxtopher
/// @brief fr: Définition du domaine par extension c-à-d est l'ensemble des élements du domain
///        en: Definition of the domaine by extension that is to say all the elements of the domain
/// @version 0.1
/// @date 2019-09-12
/// 
///

#ifndef DOMDISCRETE_H
#define DOMDISCRETE_H

#include <map>
#include <unordered_set>
#include <memory>

#include "domain.hpp"

namespace stocos 
{

template <typename TYPE_FITNESS, typename TYPE_CELL>
class DomDiscrete : public Domain<TYPE_FITNESS, TYPE_CELL>  {
    public:
    /// 
    /// @brief Pour chaque cases, extension
    /// 
    ///
    DomDiscrete(std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> exhaustive_list, std::shared_ptr<std::unordered_set<TYPE_CELL>> dom = nullptr) :
        Domain<TYPE_FITNESS, TYPE_CELL>(1,1),
        dom_each_cell(exhaustive_list), _dom(dom) {
    }

    /// 
    /// @brief Pour toutes les cases, give exhautive list, extension
    /// 
    ///
    DomDiscrete(const std::shared_ptr<std::unordered_set<TYPE_CELL>> dom) :
        Domain<TYPE_FITNESS, TYPE_CELL>(1,1),
        _dom(dom) {
        
    }

    DomDiscrete(const DomDiscrete &dom) : 
		Domain<TYPE_FITNESS, TYPE_CELL>(dom) {
            // ! copie _dom, dom_each_cell
    }
    // ! operator=

    const std::shared_ptr<const std::unordered_set<TYPE_CELL>> get_domain(const unsigned int variable_index) {
        if (dom_each_cell[variable_index] == nullptr) {
            return _dom;
        } else {
            return dom_each_cell[variable_index];
        }
    }

    unsigned int size_domain(const unsigned int variable_index) {
        if (dom_each_cell[variable_index] == nullptr)
            return 0;
        else
            return dom_each_cell[variable_index].size();
    }

    void remove_element(unsigned int variable_index, TYPE_CELL element) {
        if (dom_each_cell[variable_index] == nullptr)
            dom_each_cell[variable_index] = std::make_shared<std::unordered_set<TYPE_CELL>>(*_dom);
        dom_each_cell[variable_index]->erase(element);            
    }

    TYPE_CELL pick(unsigned int variable_index, unsigned int element_index) {
        //std::unordered_set<TYPE_CELL>::iterator
        auto it = dom_each_cell[variable_index]->begin();
        std::advance(it, element_index);
        return (*it);
    }

    private:
    std::shared_ptr<std::unordered_set<TYPE_CELL>> _dom;
    std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> dom_each_cell;
};

}

#endif