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
#include <iostream>
#include <map>
#include <memory>
#include <unordered_set>

#include <jsoncpp/json/json.h>

#include "domain.h"

namespace stocos {

template<typename TYPE_CELL>
class Domain {
  public:
	///
	/// @brief Pour chaque variables, extension
	///
	Domain(std::map<unsigned int, std::shared_ptr<std::unordered_set<TYPE_CELL>>> exhaustive_list,
		   std::shared_ptr<std::unordered_set<TYPE_CELL>> dom = nullptr);

	///
	/// @brief Pour toutes les variables, give exhautive list, extension
	///
	Domain(const std::shared_ptr<std::unordered_set<TYPE_CELL>> dom);

	///
	/// @brief Pour toutes les variables, definition du domaine
	///
	/// @param [a, b[ : range definition
	/// @param step : Step size of the sequence. It defaults to 1.
	///
	Domain(const TYPE_CELL a, const TYPE_CELL b, const TYPE_CELL step = 1);

	Domain(const Domain& dom);

	Domain(const Json::Value& jsonValue);

	///
	/// @brief Taille du domain pour une variable
	///
	unsigned int get_size_domain(const unsigned int variable_index) const;
	///
	/// @brief Ajouter une element au domaine d'une variable
	///
	void add_element(const unsigned int variable_index, TYPE_CELL element);

	///
	/// @brief Retirer un element au domaine d'une variable
	///
	void remove_element(const unsigned int variable_index, TYPE_CELL element);

	///
	/// @brief
	///
	bool in_domain(const unsigned int variable_index, const TYPE_CELL element);
	///
	/// @brief Retourne l'element à l'index pour une variable
	///
	TYPE_CELL pick(const unsigned int variable_index, unsigned int element_index);

	void show() const;

	void loadJson(const Json::Value& jsonValue);

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