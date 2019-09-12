///
/// @file subsetSum.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief https://en.wikipedia.org/wiki/Subset_sum_problem
///

#ifndef EVALSUBSETSUM_H
#define EVALSUBSETSUM_H

#include <vector>
#include <unistd.h>
#include <fstream>

#include <jsoncpp/json/json.h>

#include "../solution/solutionArray.hpp"
#include "problem.hpp"



using TYPE_FITNESS_SUBSETSUM =unsigned int;
using TYPE_CELL_SUBSETSUM = bool;
using SOL_SUBSETSUM = SolutionArray<TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM>;
class Subsetsum : public Problem<SOL_SUBSETSUM, TYPE_FITNESS_SUBSETSUM, TYPE_CELL_SUBSETSUM> {
    public:
    Subsetsum() {
        generateInstance(1);
    }

    Subsetsum(const unsigned int N) {
        generateInstance(N);
    }

    Subsetsum(const std::string &fileInstance) {
        Json::Value config = loadInstance(fileInstance); 
        loadJson(config);
    }

    void generateInstance(const unsigned int N) {
        setOfNumbers.clear();
        for (unsigned int i = 1 ; i <= N ; i++) {
            setOfNumbers.push_back(i % 50);
            if (i % 3)
                fitnessObjectif += i;
        }
    };

    virtual ~Subsetsum() {

    }

    void loadJson(const Json::Value &config) {
        std::string encoding = config.get("encoding", "UTF-8").asString();

        fitnessObjectif = config["problem"]["fitnessObjectif"].asUInt();
        for (unsigned int i = 0; i < config["problem"]["set"].size() ; i++) {
            setOfNumbers.push_back(config["problem"]["set"][i].asUInt());
        }
    }

	TYPE_FITNESS_SUBSETSUM getFitnessObjectif(unsigned int numObjectif = 0) const {
		assert(numObjectif = 0);
		return fitnessObjectif;
	}

    void evaluation(SOL_SUBSETSUM &s) {
        assert(setOfNumbers.size() == s.sizeArray());
        unsigned int sum = 0;
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            if (s(i) == 1) {
                sum += setOfNumbers[i];
            }
        }
        s.setFitness(0, sum);
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void resetSolution(SOL_SUBSETSUM &s) const {
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            s(i, 0);
        }
    }

    std::unique_ptr<SOL_SUBSETSUM> new_solution() const {
        std::unique_ptr<SOL_SUBSETSUM> s(std::make_unique<SOL_SUBSETSUM>(setOfNumbers.size()));
        for (unsigned int i = 0 ; i < s->sizeArray() ; i++) {
            s->operator()(i, 0);
        } 
        return std::move(s);
    }

    private:
        std::vector<unsigned int> setOfNumbers;
        unsigned int fitnessObjectif;
};

#endif