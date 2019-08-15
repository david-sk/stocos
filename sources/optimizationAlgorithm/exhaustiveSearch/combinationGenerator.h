///
/// \file combinationGenerator.h
/// \author Jxtopher
/// \version 1
/// \date 2019
/// \brief *
///

#ifndef COMBINATIONGENERATOR_H
#define COMBINATIONGENERATOR_H

#include <iostream>
#include <random>

#include "../../solution/solutionArray.h"
#include "../optimizationAlgorithm.h"
#include "../../problem/problem.h"

using namespace std;

template <typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class CombinationGenerator : public OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL> {
   public:
    CombinationGenerator(std::mt19937 &mt_rand, 
                        std::unique_ptr<Statistic<SOL>> statistic, 
						std::unique_ptr<StoppingCriteria<SOL, TYPE_FITNESS>> stoppingCriteria,
                        shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem, 
                        const unsigned int nbDigit, 
						const unsigned int len_string)
        				: OptimizationAlgorithm<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, move(statistic), move(stoppingCriteria), problem),
          				_nbDigit(nbDigit),
                        _len_string(len_string) {
                        nbCall = 0;
                        _string = std::unique_ptr<unsigned int[]>(new unsigned int[_len_string]);
    }

    virtual ~CombinationGenerator() {}

    void reset() {
        for (unsigned int j = 0; j < _len_string; j++) _string[j] = 0;

        x = false;
        i = 0;

        while (_string[i] == (_nbDigit - 1)) {
            i++;
            x = true;
        }

    }

    void step() {
        _string[i]++;

        if (x) {
            for (unsigned int j = 0; j < i; j++) _string[j] = 0;
            i = 0;
        }

        while (_string[i] == (_nbDigit - 1)) {
            i++;
            x = true;
        }
    }

    bool stop() { return i < (_len_string); }

    std::unique_ptr<SOL> operator()(const SOL &s) {
        reset();

        do {
            step();
            // this-> _problem.filtering(s);

        } while (stop());

        std::unique_ptr<SOL> result;
        return move(result);
    }

    string className() const {
        return "CombinationGenerator";
    }
   private:
    const unsigned int _nbDigit;
    const unsigned int _len_string;

    unsigned int nbCall;
    std::unique_ptr<unsigned int[]> _string;

    bool x;
    unsigned int i;

    const vector<unsigned int> _bijection;
};

#endif

/*int main() {
        CombinationGenerator cg;
        cg(2, 28, CombinationGenerator::f);
}*/
