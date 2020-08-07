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

#include <cassert>
#include <map>
#include <memory>
#include <unordered_set>

#include <jsoncpp/json/json.h>

#include "domain.hpp"

namespace stocos {

template<typename TYPE_CELL>
class Domain {
  public:
	///
	/// @brief Pour chaque variables, extension
	///
	Domain(std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> exhaustive_list,
		   std::shared_ptr<std::unordered_set<TYPE_CELL>> dom = nullptr)
		: dom_each_cell(exhaustive_list), _dom(dom) {
	}

	///
	/// @brief Pour toutes les variables, give exhautive list, extension
	///
	Domain(const std::shared_ptr<std::unordered_set<TYPE_CELL>> dom) : _dom(dom) {
	}

	///
	/// @brief Pour toutes les variables, definition du domaine
	///
	/// @param a : Starting point of the sequence.
	/// @param b : Endpoint of the sequence. This item will not be included in the sequence.
	/// @param step : Step size of the sequence. It defaults to 1.
	///
	Domain(const TYPE_CELL a, const TYPE_CELL b, const TYPE_CELL step = 1) {
		_dom = std::make_shared<std::unordered_set<TYPE_CELL>>();
		for(TYPE_CELL i = a; i < b; i += step) _dom->insert(i);
	}

	Domain(const Domain& dom) {
		// ! copie _dom, dom_each_cell
	}
	// ! operator=

	Domain(const Json::Value& jsonValue) {
		loadJson(jsonValue);
	}

	///
	/// @brief Taille du domain pour une variable
	///
	unsigned int get_size_domain(const unsigned int variable_index) const {
		try {
			return dom_each_cell.at(variable_index)->size();
		} catch(const std::out_of_range& oor) { return _dom->size(); }
	}
	///
	/// @brief Ajouter une element au domaine d'une variable
	///
	void add_element(const unsigned int variable_index, TYPE_CELL element) {
		if(dom_each_cell[variable_index] == nullptr)
			dom_each_cell[variable_index] = std::make_shared<std::unordered_set<TYPE_CELL>>(*_dom);
		dom_each_cell[variable_index]->insert(element);
	}

	///
	/// @brief Retirer un element au domaine d'une variable
	///
	void remove_element(const unsigned int variable_index, TYPE_CELL element) {
		if(dom_each_cell[variable_index] == nullptr)
			dom_each_cell[variable_index] = std::make_shared<std::unordered_set<TYPE_CELL>>(*_dom);
		dom_each_cell[variable_index]->erase(element);
	}

	///
	/// @brief
	///
	bool in_domain(const unsigned int variable_index, const TYPE_CELL element) {
		if(dom_each_cell[variable_index] == nullptr) {
			typename std::unordered_set<TYPE_CELL>::const_iterator got = _dom->find(element);
			return got != _dom->end();
		} else {
			typename std::unordered_set<TYPE_CELL>::const_iterator got =
				dom_each_cell[variable_index]->find(element);
			return got != dom_each_cell[variable_index]->end();
		}
		return false;
	}

	///
	/// @brief Retourne l'element à l'index pour une variable
	///
	TYPE_CELL pick(const unsigned int variable_index, unsigned int element_index) {
		auto it = dom_each_cell[variable_index]->begin();
		std::advance(it, element_index);
		return (*it);
	}

	void show() const {
		for(typename std::map<unsigned int,
							  std::shared_ptr<std::unordered_set<TYPE_CELL>>>::const_iterator it =
				dom_each_cell.begin();
			it != dom_each_cell.end(); + +it) {
			std::cout << it->first << " =>";
			for(typename std::unordered_set<TYPE_CELL>::const_iterator it2 = it->second->begin();
				it2 != it->second->end(); ++it2) {
				std::cout << " " << *it2;
			}
			std::cout << std::endl;
		}
	}

	void loadJson(const Json::Value& jsonValue) {
		if(!jsonValue["exhaustive_list"].empty()) {
			_dom = std::make_shared<std::unordered_set<TYPE_CELL>>();
			for(unsigned int i = 0; i < jsonValue["exhaustive_list"].size(); i++)
				_dom->insert(jsonValue["exhaustive_list"][i].asDouble());
		} else if(!jsonValue["interval"].empty()) {
		} else
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
									 " [-] option does not exist.");
	}

	// Json::Value asJson() const {

	// }

  private:
	///< definition du domaine pour toutes les variables
	std::shared_ptr<std::unordered_set<TYPE_CELL>> _dom;
	///< definition du domaine pour chaque variables
	std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> dom_each_cell;
};

} // namespace stocos

#endif