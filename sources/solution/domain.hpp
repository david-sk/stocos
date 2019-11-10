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
#include <cassert>

#include <jsoncpp/json/json.h>

#include "domain.hpp"

namespace stocos 
{

template <typename TYPE_CELL>
class Domain {
    public:
    /// 
    /// @brief Pour chaque cases, extension
    /// 
    Domain(std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> exhaustive_list, std::shared_ptr<std::unordered_set<TYPE_CELL>> dom = nullptr) :
        dom_each_cell(exhaustive_list), _dom(dom) {
    }

    /// 
    /// @brief Pour toutes les cases, give exhautive list, extension
    /// 
    Domain(const std::shared_ptr<std::unordered_set<TYPE_CELL>> dom) :
        _dom(dom) {
        
    }

    /// 
    /// @brief Pour toutes les cases, intension
    ///
    /// @param a : Starting point of the sequence. 
    /// @param b : Endpoint of the sequence. This item will not be included in the sequence.
    /// @param step : Step size of the sequence. It defaults to 1.
    ///
    Domain(const TYPE_CELL a, const TYPE_CELL b, const TYPE_CELL step = 1) {
        _dom = std::make_shared<std::unordered_set<TYPE_CELL>>();
        for (TYPE_CELL i = a ; i < b ; i+=step)
            _dom->insert(i);
    }

    Domain(const Domain &dom)  {
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

    /// 
    /// @brief taille du domain pour une variable
    /// 
    unsigned int size_domain(const unsigned int variable_index) {
        if (dom_each_cell[variable_index] == nullptr)
            return _dom->size();
        else
            return dom_each_cell[variable_index]->size();
    }


    /// 
    /// @brief ajouter un intervalle dans le domain
    /// 
    /// @param a : Starting point of the sequence. 
    /// @param b : Endpoint of the sequence. This item will not be included in the sequence.
    /// @param step : Step size of the sequence. It defaults to 1.
    ///
    void add_interval(const TYPE_CELL a, const TYPE_CELL b, const TYPE_CELL step = 1) {
        assert(false &&  "Need defind add_interval");
        // ! Need defind
    }

    /// 
    /// @brief 
    /// 
    /// @param a 
    /// @param b 
    /// @param step 
    ///
    void remove_interval(const TYPE_CELL a, const TYPE_CELL b) {
        // ! Need defind
        assert(false &&  "Need defind remove_interval");
    }

    /// 
    /// @brief Ajouter une element au domaine d'une variable
    /// 
    void add_element(unsigned int variable_index, TYPE_CELL element) {
        if (dom_each_cell[variable_index] == nullptr)
            dom_each_cell[variable_index] = std::make_shared<std::unordered_set<TYPE_CELL>>(*_dom);
        dom_each_cell[variable_index]->insert(element);
    }

    /// 
    /// @brief Retirer un element au domaine d'une variable
    /// 
    void remove_element(unsigned int variable_index, TYPE_CELL element) {
        if (dom_each_cell[variable_index] == nullptr)
            dom_each_cell[variable_index] = std::make_shared<std::unordered_set<TYPE_CELL>>(*_dom);
        dom_each_cell[variable_index]->erase(element);            
    }

    /// 
    /// @brief Retourner l'element à l'index pour une variable
    /// 
    TYPE_CELL pick(unsigned int variable_index, unsigned int element_index) {
        //std::unordered_set<TYPE_CELL>::iterator
        auto it = dom_each_cell[variable_index]->begin();
        std::advance(it, element_index);
        return (*it);
    }

    void show() {
        for (typename std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>>::const_iterator it = dom_each_cell.begin(); it != dom_each_cell.end(); ++it) {
            std::cout<<it->first<<" =>";
            for (typename std::unordered_set<TYPE_CELL>::const_iterator it2 = it->second->begin(); it2 != it->second->end(); ++it2) {
                std::cout<<" "<<*it2;
            }
            std::cout<<std::endl;
        }
    }


    // void loadJson(const Json::Value &jsonValue) {

    // }

    // Json::Value asJson() const {

    // }

    private:
    //< intervalle ??
    std::shared_ptr<std::unordered_set<TYPE_CELL>> _dom; ///< definition du domaine pour toutes les variables
    std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> dom_each_cell; ///< definition du domaine pour chaque case
};

}

#endif