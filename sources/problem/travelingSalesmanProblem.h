///
/// \file travelingSalesmanProblem.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2019-07
/// \brief
///

#ifndef EVALTRAVELINGSALESMANPROBLEM_H
#define EVALTRAVELINGSALESMANPROBLEM_H

#include <vector>
#include <string>
#include <cmath>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>

#include "problem.h"


using namespace std;

using TYPE_FITNESS_STP =unsigned int;
using TYPE_CELL_STP = unsigned int;
using SOL_STP = SolutionArray<TYPE_FITNESS_STP, TYPE_CELL_STP>;
class TravelingSalesmanProblem : public Problem<SOL_STP, TYPE_FITNESS_STP, TYPE_CELL_STP>  {
    public:
        TravelingSalesmanProblem() {

        }

        virtual ~TravelingSalesmanProblem() {

        }

        unique_ptr<SOL_STP> new_solution() const {
            unique_ptr<SOL_STP> s(make_unique<SOL_STP>(nodes.size()));
            for (unsigned int i = 0 ; i < s->sizeArray() ; i++) {
                s->operator()(i, i);
            } 
            return move(s);
        }

        virtual void loadInstance(const string &file) {
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
            numberOfNodes = static_cast<unsigned int>(problem["numberOfNodes"].GetInt());
            Value& _nodes = problem["nodes"];

            for (SizeType i = 0; i < _nodes.Size(); i++) {
                double x = _nodes[i]["x"].GetDouble();
                double y = _nodes[i]["y"].GetDouble();
                nodes.push_back(pair<double, double>(x, y));
            }
        }

        virtual void full_eval(SOL_STP &s) const {
            double distance_sum = 0;
            for (unsigned int i = 0 ; i < s.sizeArray() - 1 ; i++) {
                distance_sum += distance_euclidienne(nodes[s(i)], nodes[s(i + 1)]);
            }
            s.setFitness(distance_sum);
        }


    private:
        double distance_euclidienne(const pair<double, double> &node_a, const pair<double, double> &node_b) const {
            return sqrt(abs(node_b.second - node_a.second) * abs(node_b.second - node_a.second) + abs(node_b.first - node_a.first) * abs(node_b.first - node_a.first));
        }

        string numInstance;
        unsigned int numberOfNodes;
        vector<pair<double, double>> nodes;

};

#endif