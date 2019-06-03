///
/// \file evalSubsetSum.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief https://en.wikipedia.org/wiki/Subset_sum_problem
///

#ifndef EVALSUBSETSUM_H
#define EVALSUBSETSUM_H

#include <vector>
#include <unistd.h>

#include "../solution/solutionArray.h"
#include "problem.h"

using namespace std;

using TYPE_CELL_SUBSETSUM = bool;
using SOL_SUBSETSUM = SolutionArray<unsigned int, TYPE_CELL_SUBSETSUM>;
class Subsetsum : public Problem<SOL_SUBSETSUM, TYPE_CELL_SUBSETSUM> {
    public:
    
    Subsetsum(const unsigned int N) {
        generateInstance(N);
    }

    Subsetsum(string pathfile_instance) {
        loadInstance(pathfile_instance);
    }

    void generateInstance(const unsigned int N) {
        for (unsigned int i = 1 ; i <= N ; i++) {
            setOfNumbers.push_back(i % 50);
            if (i % 3)
                fitnessObjectif += i;
        }
    };

    virtual ~Subsetsum() {

    }

    void loadInstance(string file) {
        using namespace rapidjson;

        // check if a file exist
        assert(access(file.c_str(), F_OK ) != -1);

        FILE* fp = fopen(file.c_str(), "rb"); // non-Windows use "r"
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);

        Value& problem = d["problem"];
        cerr<<"**"<<problem["name"].GetString()<<"**"<<endl;

        fitnessObjectif = static_cast<unsigned int>(problem["fitnessObjectif"].GetInt());

        Value& set = problem["set"];

        for (SizeType i = 0; i < set.Size(); i++) {
            setOfNumbers.push_back(static_cast<unsigned int>(set[i].GetInt()));
        }
        fclose(fp);
    }

    unsigned int getFitnessObjectif() {
        return fitnessObjectif;
    }

    void full_eval(SOL_SUBSETSUM &s) const {
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

    void reset_solution(SOL_SUBSETSUM &s) const {
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            s(i, 0);
        }
    }

    private:
        vector<unsigned int> setOfNumbers;
        unsigned int fitnessObjectif;
};

#endif