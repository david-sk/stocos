///
/// \file knapsackProblem.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2019-05
/// \brief Knapsack Problem
///

#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <map>
#include <utility>
#include <unistd.h>
#include <vector>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include "../solution/solutionArray.h"
#include "problem.h"

using namespace std;

using TYPE_FITNESS_KNAPSACK = int;
using TYPE_CELL_KNAPSACK = bool;
using SOL_KNAPSACK = SolutionArray<TYPE_FITNESS_KNAPSACK, TYPE_CELL_KNAPSACK>;

class Knapsack : public Problem<SOL_KNAPSACK, TYPE_FITNESS_KNAPSACK, TYPE_CELL_KNAPSACK> {
    public:
    Knapsack() {
        
    }
    
    Knapsack(string pathfile_instance) {
        loadInstance(pathfile_instance);
    }
    
    ~Knapsack() {

    }

    void loadInstance(const string &file) {
        using namespace rapidjson;

        // check if a file exist
        assert(access(file.c_str(), F_OK ) != -1);

        FILE* fp = fopen(file.c_str(), "rb");
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Document d;
        d.ParseStream(is);
        Value& problem = d["problem"];
        numInstance = problem["numInstance"].GetString();
        capacity = problem["capacity"].GetInt();
        nbItems =  problem["#items"].GetInt64();

        Value& _weight = problem["weight"];
        Value& _profit = problem["profit"];

        //assert(static_cast<int>(problem["#items"].GetInt()) != static_cast<int>(_weight.Size()));
        //assert(_weight.Size() != _profit.Size());

        weight.clear();
        profit.clear();
        for (unsigned int i = 0; i < nbItems ; i++) {
            weight.push_back(_weight[i].GetInt());
            profit.push_back(_profit[i].GetInt());
        }

        for (unsigned int i = 0 ; i < profit.size() ; i++)
            fitnessObjectif += profit[i];
        

    }

    void full_eval(SOL_KNAPSACK &s) const {
        int fitness = 0;
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++)
            fitness += profit[i] * s(i);

        int W = 0;
		for (unsigned int i = 0 ; i < s.sizeArray() ; i++)
			W += weight[i] * s(i);
		
		if (capacity < W)
			fitness = -1;
		s.setFitness(fitness);
    }

    /*void incremental(const SolutionArray &s, unsigned int mutatedCell) const {

    }*/

    void reset_solution(SOL_KNAPSACK &s) const {
        for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
            s(i, 0);
        }
    }

    unique_ptr<SOL_KNAPSACK> new_solution() const {
        unique_ptr<SOL_KNAPSACK> s(make_unique<SOL_KNAPSACK>(nbItems));
        for (unsigned int i = 0 ; i < s->sizeArray() ; i++) {
            s->operator()(i, 0);
        } 
        return move(s);
    }

    unsigned int sizeArraySolution() const{
        return nbItems;
    }

    TYPE_FITNESS_KNAPSACK getFitnessObjectif() const {
        return fitnessObjectif;
    }

	TYPE_FITNESS_KNAPSACK getFitnessObjectif(unsigned int numObjectif) const {
		assert(numObjectif = 0);
		return fitnessObjectif;
	}

    private:
        string numInstance;
        int capacity;
        unsigned int nbItems;
        vector<int> weight;
        vector<int> profit;
        int fitnessObjectif;
};

#endif