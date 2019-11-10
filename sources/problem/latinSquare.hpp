///
/// @file latinSquare.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef EVALLATINSQUARE_H
#define EVALLATINSQUARE_H

#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <memory>
#include <unistd.h>

#include "../solution/solutionArray.hpp"
#include "../solutionSelection/solutionSelection.hpp"
#include "../solutionSelection/maximization.hpp"

#include "problem.hpp"

namespace stocos 
{

using TYPE_FITNESS_LATINSQUARE = unsigned int;
using TYPE_CELL_LATINSQUARE = bool;
using SOL_LATINSQUARE= SolutionArray<TYPE_FITNESS_LATINSQUARE, TYPE_CELL_LATINSQUARE>;
class LatinSquare : public Problem<SOL_LATINSQUARE, TYPE_FITNESS_LATINSQUARE, TYPE_CELL_LATINSQUARE> {
   public:
    LatinSquare() : _N(1) {
    }

    LatinSquare(const std::string &fileInstance) { 
        Json::Value config = loadInstance(fileInstance); 
        loadJson(config);
    }

    LatinSquare(unsigned int N) : _N(N) {}

    ~LatinSquare() {}

    virtual void loadJson(const Json::Value &config) {
        instance_number = config["problem"]["instance_number"].asString();
        _N = config["problem"]["N"].asUInt();
    }

    std::unique_ptr<SOL_LATINSQUARE> new_solution() const {
        std::unique_ptr<SOL_LATINSQUARE> s(std::make_unique<SOL_LATINSQUARE>(_N));
        for (unsigned int i = 0; i < s->sizeArray(); i++) {
            s->operator()(i, 0);
        }
        return std::move(s);
    }

    bool checkSolutionStructure(const SOL_LATINSQUARE &s) const {
        if (s.sizeArray() != _N || s.numberOfObjective() != 1) {
            return false;
        }
        return true;
    }

    void evaluation(SOL_LATINSQUARE &s) {
        //
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void resetSolution(SOL_LATINSQUARE &s) const {
        for (unsigned int i = 0; i < s.sizeArray(); i++) {
            s(i, 0);
        }
    }
    
    TYPE_FITNESS_LATINSQUARE getFitnessObjectif(unsigned int numObjectif = 0) const {
        assert(numObjectif = 0);
        return _N;
    }


	bool solutionSelection(const SOL_LATINSQUARE &s_worst, const SOL_LATINSQUARE &s_best) {
        return solution_selection(s_worst, s_best);
	}

	unsigned int solutionSelection(const Population<SOL_LATINSQUARE> &p) {
        return solution_selection(p);
	}

   private:
    Maximization<SOL_LATINSQUARE> solution_selection;
    std::string instance_number;
    unsigned int _N;
};

}
#endif