///
/// @file continuousProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-08
/// @brief
///

#ifndef CONTINUOUSPROBLEM_H
#define CONTINUOUSPROBLEM_H

#include <fstream>
#include <iostream>
#include <memory>
#include <utility> // std::pair

#include <jsoncpp/json/json.h>
#include <unistd.h>

#include <exprtk/exprtk.hpp>

#include "../solution/solutionArray.h"
#include "../solutionSelection/solutionSelection.h"
#include "../solutionSelection/solutionSelectionBuilder.h"
#include "problem.h"

namespace stocos {

using TYPE_FITNESS_CONTINUOUSPROBLEM = double;
using TYPE_CELL_CONTINUOUSPROBLEM = double;
using SOL_CONTINUOUSPROBLEM =
	SolutionArray<TYPE_FITNESS_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>;

class Objectif {
	typedef exprtk::symbol_table<double> symbol_table_t;
	typedef exprtk::expression<double> expression_t;
	typedef exprtk::parser<double> parser_t;

  public:
	Objectif(const std::string& function, const Json::Value& variables) {
		parser_t parser;
		value = std::make_unique<double[]>(variables.size());
		valueSize = variables.size();
		for(unsigned int j = 0; j < valueSize; j++) {
			symbol_table.add_variable(variables[j].asString(), value[j]);
		}
		symbol_table.add_constants();

		expression.register_symbol_table(symbol_table);
		parser.compile(function, expression);
	}

	void setValue(SOL_CONTINUOUSPROBLEM& s, unsigned int offset) {
		for(unsigned int i = 0; i < valueSize; i++) value[i] = s(i + offset);
	}

	unsigned int getValueSize() {
		return valueSize;
	}

	double getFitness() {
		return expression.value();
	}

  private:
	std::unique_ptr<double[]> value;
	unsigned int valueSize;

	expression_t expression;
	symbol_table_t symbol_table;
};

class ContinuousProblem : public Problem<SOL_CONTINUOUSPROBLEM, TYPE_FITNESS_CONTINUOUSPROBLEM,
										 TYPE_CELL_CONTINUOUSPROBLEM> {
  public:
	ContinuousProblem();

	ContinuousProblem(std::string fileInstance);

	~ContinuousProblem();

	void loadJson(const Json::Value& config);

	std::unique_ptr<SOL_CONTINUOUSPROBLEM> new_solution() const;
	void evaluation(SOL_CONTINUOUSPROBLEM& s);

	std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>
		domain(unsigned index) const;

	bool solutionSelection(const SOL_CONTINUOUSPROBLEM& s_worst,
						   const SOL_CONTINUOUSPROBLEM& s_best);

	unsigned int solutionSelection(const Population<SOL_CONTINUOUSPROBLEM>& p);

  private:
	std::vector<std::unique_ptr<SolutionSelection<SOL_CONTINUOUSPROBLEM>>> solution_selection;
	std::string instance_number;
	std::vector<Objectif> objectif; // ! variable modifier par evaluation
	unsigned int nomberOfVariable;
	std::unique_ptr<std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>[]> _domain;
};

} // namespace stocos

#endif