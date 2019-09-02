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
#include <jsoncpp/json/json.h>
#include <memory>
#include <utility>
#include <unistd.h>


#include "../solution/solutionArray.hpp"
#include "../solutionSelection/solutionSelection.hpp"
#include "../solutionSelection/solutionSelectionBuilder.hpp"
#include "exprtk/exprtk.hpp"
#include "problem.hpp"

using TYPE_FITNESS_CONTINUOUSPROBLEM = double;
using TYPE_CELL_CONTINUOUSPROBLEM = double;
using SOL_CONTINUOUSPROBLEM = SolutionArray<TYPE_FITNESS_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>;

class Objectif {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

  public:
    Objectif(const std::string &function, const Json::Value& variables) {
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
            for(unsigned int i = 0 ; i < valueSize ; i++)
                value[i] = s(i + offset);
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

class ContinuousProblem : public Problem<SOL_CONTINUOUSPROBLEM, TYPE_FITNESS_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM> {
  public:
    ContinuousProblem() : _domain(nullptr) {
    }

    ContinuousProblem(std::string fileInstance) : _domain(nullptr) {
        Json::Value config = loadInstance(fileInstance); 
        loadJson(config);
    }

    ~ContinuousProblem() {}

    void loadJson(const Json::Value &config) {
        instance_number = config["problem"]["instance_number"].asString();

        for(unsigned int i = 0; i < config["problem"]["objectif"].size(); i++) {
            objectif.push_back(Objectif(config["problem"]["objectif"][i]["function"].asString(),
                                        config["problem"]["objectif"][i]["variables"]));
        }

        // Définition du nombre de varaibles
        nomberOfVariable = 0;
        for(unsigned int i = 0 ; i < objectif.size() ; i++) {
            nomberOfVariable += objectif[i].getValueSize();
        }

        // Définie pour chaque variables son domaine
        _domain = std::make_unique<std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM> []>(nomberOfVariable);
        // solution_selection = std::make_unique<SolutionSelection<SOL_CONTINUOUSPROBLEM> []>(objectif.size());
        for(unsigned int i = 0; i < config["problem"]["objectif"].size(); i++) {
            unsigned int domainSize = config["problem"]["objectif"][i]["domain"].size();
            for(unsigned int j = 0; j < domainSize; j++) {
                _domain[j] = std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>(config["problem"]["objectif"][i]["domain"][j][0].asDouble(),config["problem"]["objectif"][i]["domain"][j][1].asDouble());
            }
            solution_selection.push_back(solutionSelectionBuilder<SOL_CONTINUOUSPROBLEM, TYPE_FITNESS_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>::build(*this, config["problem"]["objectif"][i]["solutionSelection"]));
        }
    }

    std::unique_ptr<SOL_CONTINUOUSPROBLEM> new_solution() const {
        std::unique_ptr<SOL_CONTINUOUSPROBLEM> s = std::make_unique<SOL_CONTINUOUSPROBLEM>(objectif.size(), nomberOfVariable);
        return std::move(s);
    }

    void full_eval(SOL_CONTINUOUSPROBLEM& s) {
        unsigned int offset = 0;
        for(unsigned int i = 0; i < objectif.size(); i++) {
            objectif[i].setValue(s, i + offset);
            offset += objectif[i].getValueSize() - 1;

            s.setFitness(i, objectif[i].getFitness());
        }
    }

	std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM> domain(unsigned index) const {
        assert(index < nomberOfVariable); 

        if (_domain == nullptr)
		    throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : domain()");
        return _domain[index];
	}

	bool solutionSelection(const SOL_CONTINUOUSPROBLEM &s_worst, const SOL_CONTINUOUSPROBLEM &s_best) {
        // ! Need to implement multi-objectif !
        return solution_selection[0]->operator()(s_worst, s_best);
	}

	unsigned int solutionSelection(const Population<SOL_CONTINUOUSPROBLEM> &p) {
        // ! Need to implement multi-objectif !
        return solution_selection[0]->operator()(p);
	}

   private:
    std::vector<std::unique_ptr<SolutionSelection<SOL_CONTINUOUSPROBLEM>>> solution_selection;
    std::string instance_number;
    std::vector<Objectif> objectif; // ! variable modifier par full_eval
    unsigned int nomberOfVariable;
    std::unique_ptr<std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM> []> _domain;
};

#endif