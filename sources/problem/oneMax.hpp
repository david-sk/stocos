///
/// @file oneMax.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef EVALONEMAX_H
#define EVALONEMAX_H

#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <unistd.h>

#include "../solution/solutionArray.hpp"
#include "../solutionSelection/solutionSelection.hpp"
#include "../solutionSelection/maximization.hpp"

#include "problem.hpp"

using TYPE_FITNESS_ONEMAX = unsigned int;
using TYPE_CELL_ONEMAX = bool;
using SOL_ONEMAX = SolutionArray<TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>;
class OneMax : public Problem<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> {
   public:
    OneMax() : _N(1) {
    }

    OneMax(const std::string &fileInstance) { 
        Json::Value config = loadInstance(fileInstance); 
        loadJson(config);
    }

    OneMax(unsigned int N) : _N(N) {}

    ~OneMax() {}

    virtual void loadJson(const Json::Value &config) {
        instance_number = config["problem"]["instance_number"].asString();
        _N = config["problem"]["N"].asUInt();
    }

    std::unique_ptr<SOL_ONEMAX> new_solution() const {
        std::unique_ptr<SOL_ONEMAX> s(std::make_unique<SOL_ONEMAX>(_N));
        for (unsigned int i = 0; i < s->sizeArray(); i++) {
            s->operator()(i, 0);
        }
        return std::move(s);
    }

    bool checkSolutionStructure(const SOL_ONEMAX &s) const {
        if (s.sizeArray() != _N || s.numberOfObjective() != 1) {
            return false;
        }
        return true;
    }

    void evaluation(SOL_ONEMAX &s) {
        unsigned int sum = 0;
        for (unsigned int i = 0; i < s.sizeArray(); i++) {
            sum += s(i);
        }
        s.setFitness(0, sum);
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void resetSolution(SOL_ONEMAX &s) const {
        for (unsigned int i = 0; i < s.sizeArray(); i++) {
            s(i, 0);
        }
    }
    
    TYPE_FITNESS_ONEMAX getFitnessObjectif(unsigned int numObjectif = 0) const {
        assert(numObjectif = 0);
        return _N;
    }


	bool solutionSelection(const SOL_ONEMAX &s_worst, const SOL_ONEMAX &s_best) {
        return solution_selection(s_worst, s_best);
	}

	unsigned int solutionSelection(const Population<SOL_ONEMAX> &p) {
        return solution_selection(p);
	}

   private:
    Maximization<SOL_ONEMAX> solution_selection;
    std::string instance_number;
    unsigned int _N;
};

#endif