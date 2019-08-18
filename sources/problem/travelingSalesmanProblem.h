///
/// @file travelingSalesmanProblem.h
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

#include "problem.h"

using namespace std;

using TYPE_FITNESS_STP = unsigned int;
using TYPE_CELL_STP = unsigned int;
using SOL_STP = SolutionArray<TYPE_FITNESS_STP, TYPE_CELL_STP>;
class TravelingSalesmanProblem : public Problem<SOL_STP, TYPE_FITNESS_STP, TYPE_CELL_STP> {
   public:
    TravelingSalesmanProblem() {}

    virtual ~TravelingSalesmanProblem() {}

    std::unique_ptr<SOL_STP> new_solution() const {
        std::unique_ptr<SOL_STP> s(make_unique<SOL_STP>(nodes.size()));
        for (unsigned int i = 0; i < s->sizeArray(); i++) {
            s->operator()(i, i);
        }
        return move(s);
    }

    virtual void loadInstance(const string &file) {
        Json::Value root;  // will contains the root value after parsing.
        Json::Reader reader;
        std::ifstream test(file, std::ifstream::binary);
        bool parsingSuccessful = reader.parse(test, root, false);

        if (!parsingSuccessful) throw runtime_error(reader.getFormattedErrorMessages());

        std::string encoding = root.get("encoding", "UTF-8").asString();
        numInstance = root["problem"]["numInstance"].asString();
        numberOfNodes = root["problem"]["numberOfNodes"].asUInt();
        for (unsigned int i = 0 ; i < root["problem"]["nodes"].size() ; i++) {
            double x = root["problem"]["nodes"][i]["x"].asDouble();
            double y = root["problem"]["nodes"][i]["y"].asDouble();
            nodes.push_back(pair<double, double>(x, y));
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
    double distance_euclidienne(const pair<double, double> &node_a, const pair<double, double> &node_b) const {
        return sqrt(abs(node_b.second - node_a.second) * abs(node_b.second - node_a.second) +
                    abs(node_b.first - node_a.first) * abs(node_b.first - node_a.first));
    }

    string numInstance;
    unsigned int numberOfNodes;
    vector<pair<double, double>> nodes;
};

#endif