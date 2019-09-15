/// 
/// @file domExtension.hpp
/// @author Jxtopher
/// @brief fr: Définition du domaine par extension c-à-d est l'ensemble des élements du domain
///        en: Definition of the domaine by extension that is to say all the elements of the domain
/// @version 0.1
/// @date 2019-09-12
/// 
///

#include "domain.hpp"

#include <map>
#include <unordered_set>
#include <memory>

namespace stocos 
{

template <typename TYPE_CELL>
class DomExtension : public Domain<TYPE_CELL>  {
    public:
    /// 
    /// @brief Pour chaque cases, extension
    /// 
    ///
    DomExtension(std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> exhaustive_list, std::shared_ptr<std::unordered_set<TYPE_CELL>> dom = nullptr) :
        dom_each_cell(exhaustive_list), _dom(dom) {
    }

    /// 
    /// @brief Pour toutes les cases, give exhautive list, extension
    /// 
    ///
    DomExtension(const std::shared_ptr<std::unordered_set<TYPE_CELL>> dom) : 
        _dom(dom) {
        
    }

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