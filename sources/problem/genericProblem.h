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
    GenericProblem() {}

    GenericProblem(std::string fileInstance) {
        loadInstance(fileInstance);
    }

    ~GenericProblem() {}

    void loadInstance(const std::string& file) {
        Json::Value root; // will contains the root value after parsing.
        Json::Reader reader;
        std::ifstream test(file, std::ifstream::binary);
        bool parsingSuccessful = reader.parse(test, root, false);

        if(!parsingSuccessful)
            throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " " + reader.getFormattedErrorMessages());

        std::string encoding = root.get("encoding", "UTF-8").asString();
        numInstance = root["problem"]["numInstance"].asString();

        for(unsigned int i = 0; i < root["problem"]["objectif"].size(); i++) {
            objectif.push_back(Objectif(root["problem"]["objectif"][i]["function"].asString(),
                                        root["problem"]["objectif"][i]["variables"]));
        }

        nomberOfVariable = 0;
        for(unsigned int i = 0 ; i < objectif.size() ; i++) {
            nomberOfVariable += objectif[i].getValueSize();
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

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL_GENERICPROBLEM& s) const {}

  private:
    std::string numInstance;
    std::vector<Objectif> objectif; // ! variable modifier par full_eval
    unsigned int nomberOfVariable;
};

#endif