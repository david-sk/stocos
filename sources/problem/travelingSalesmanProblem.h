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

            // for (SizeType i = 0; i < _nodes.Size(); i++) {
            //     Value& node = problem[static_cast<unsigned int>(_nodes[i].GetInt())];
            // }
        }

        virtual void full_eval(SOL_STP &s) const {
            double distance_sum = 0;
            for (unsigned int i = 0 ; i < s.sizeArray() - 1 ; i++) {
                distance_sum += distance(nodes[s(i)], nodes[s(i + 1)]);
            }
            s.setFitness(distance_sum);
        }


    private:
        double distance(pair<double, double> node_a, pair<double, double> node_b) const {
            return 0.0;
        }

        string numInstance;
        unsigned int numberOfNodes;
        vector<pair<double, double>> nodes;

};

#endif