///
/// @file genericProblem.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-08
/// @brief
///

#ifndef GENERICPROBLEM_H
#define GENERICPROBLEM_H

#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <utility>
#include <unistd.h>

#include "../solution/solutionArray.h"

#include "exprtk/exprtk.h"
#include "problem.h"



using TYPE_FITNESS_GENERICPROBLEM = double;
using TYPE_CELL_GENERICPROBLEM = double;
using SOL_GENERICPROBLEM = SolutionArray<TYPE_FITNESS_GENERICPROBLEM, TYPE_CELL_GENERICPROBLEM>;

class Objectif {
    typedef exprtk::symbol_table<double> symbol_table_t;
    typedef exprtk::expression<double> expression_t;
    typedef exprtk::parser<double> parser_t;

  public:
    Objectif(std::string function, const Json::Value& variables) {
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

    void setValue(SOL_GENERICPROBLEM& s, unsigned int offset) {
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

class GenericProblem : public Problem<SOL_GENERICPROBLEM, TYPE_FITNESS_GENERICPROBLEM, TYPE_CELL_GENERICPROBLEM> {
  public:
    GenericProblem() : _domain(nullptr) {
    }

    GenericProblem(std::string fileInstance) : _domain(nullptr) {
        Json::Value config = loadInstance(fileInstance); 
        loadJson(config);
    }

    ~GenericProblem() {}

    void loadJson(const Json::Value &config) {
        numInstance = config["problem"]["numInstance"].asString();

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
        _domain = std::make_unique<std::pair<TYPE_CELL_GENERICPROBLEM, TYPE_CELL_GENERICPROBLEM> []>(nomberOfVariable);
        for(unsigned int i = 0; i < config["problem"]["objectif"].size(); i++) {
            unsigned int domainSize = config["problem"]["objectif"][i]["domain"].size();
            for(unsigned int j = 0; j < domainSize; j++) {
                _domain[j] = std::pair<TYPE_CELL_GENERICPROBLEM, TYPE_CELL_GENERICPROBLEM>(config["problem"]["objectif"][i]["domain"][j][0].asDouble(),config["problem"]["objectif"][i]["domain"][j][1].asDouble());
            }
        }
    }

    std::unique_ptr<SOL_GENERICPROBLEM> new_solution() const {
        std::unique_ptr<SOL_GENERICPROBLEM> s = std::make_unique<SOL_GENERICPROBLEM>(objectif.size(), nomberOfVariable);
        return std::move(s);
    }

    void full_eval(SOL_GENERICPROBLEM& s) {
        unsigned int offset = 0;
        for(unsigned int i = 0; i < objectif.size(); i++) {
            objectif[i].setValue(s, i + offset);
            offset += objectif[i].getValueSize() - 1;

            s.setFitness(i, objectif[i].getFitness());
        }
    }

	std::pair<TYPE_CELL_GENERICPROBLEM, TYPE_CELL_GENERICPROBLEM> domain(unsigned index) const {
        assert(index < nomberOfVariable); 

        if (_domain == nullptr)
		    throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + "[-] Not implemented : domain()");
        return _domain[index];
	}

  private:
    std::string numInstance;
    std::vector<Objectif> objectif; // ! variable modifier par full_eval
    unsigned int nomberOfVariable;
    std::unique_ptr<std::pair<TYPE_CELL_GENERICPROBLEM, TYPE_CELL_GENERICPROBLEM> []> _domain;
};

#endif