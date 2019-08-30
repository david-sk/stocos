///
/// @file travelingSalesmanProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-07
/// @brief
///

#ifndef EVALTRAVELINGSALESMANPROBLEM_H
#define EVALTRAVELINGSALESMANPROBLEM_H

#include <cmath>
#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

#include "problem.hpp"



using TYPE_FITNESS_STP = unsigned int;
using TYPE_CELL_STP = unsigned int;
using SOL_STP = SolutionArray<TYPE_FITNESS_STP, TYPE_CELL_STP>;
class TravelingSalesmanProblem : public Problem<SOL_STP, TYPE_FITNESS_STP, TYPE_CELL_STP> {
   public:
    TravelingSalesmanProblem() {}

    TravelingSalesmanProblem(const std::string &fileInstance) { 
        Json::Value config = loadInstance(fileInstance); 
        loadJson(config);
    }

    virtual ~TravelingSalesmanProblem() {}

    std::unique_ptr<SOL_STP> new_solution() const {
        std::unique_ptr<SOL_STP> s(std::make_unique<SOL_STP>(nodes.size()));
        for (unsigned int i = 0; i < s->sizeArray(); i++) {
            s->operator()(i, i);
        }
        return std::move(s);
    }

    void loadJson(const Json::Value &config) {
        numInstance = config["problem"]["numInstance"].asString();
        numberOfNodes = config["problem"]["numberOfNodes"].asUInt();
        for (unsigned int i = 0 ; i < config["problem"]["nodes"].size() ; i++) {
            double x = config["problem"]["nodes"][i]["x"].asDouble();
            double y = config["problem"]["nodes"][i]["y"].asDouble();
            nodes.push_back(std::pair<double, double>(x, y));
        }
    }

    virtual void full_eval(SOL_STP &s) {
        double distance_sum = 0;
        for (unsigned int i = 0; i < s.sizeArray() - 1; i++) {
            distance_sum += distance_euclidienne(nodes[s(i)], nodes[s(i + 1)]);
        }
        s.setFitness(distance_sum);
    }

   private:
    double distance_euclidienne(const std::pair<double, double> &node_a, const std::pair<double, double> &node_b) const {
        return sqrt(abs(node_b.second - node_a.second) * abs(node_b.second - node_a.second) +
                    abs(node_b.first - node_a.first) * abs(node_b.first - node_a.first));
    }

    std::string numInstance;
    unsigned int numberOfNodes;
    std::vector<std::pair<double, double>> nodes;
};

#endif