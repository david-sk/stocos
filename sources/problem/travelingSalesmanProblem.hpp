///
/// @file travelingSalesmanProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-07
/// @brief 
///         instances : http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsplib.html
///

#ifndef EVALTRAVELINGSALESMANPROBLEM_H
#define EVALTRAVELINGSALESMANPROBLEM_H

#include <cmath>
#include <string>
#include <vector>

#include <jsoncpp/json/json.h>

#include "problem.hpp"
#include "../solutionSelection/minimization.hpp"

namespace stocos 
{

using TYPE_FITNESS_STP = double;
using TYPE_CELL_STP = double;
using SOL_STP = SolutionArray<TYPE_FITNESS_STP, TYPE_CELL_STP>;
class TravelingSalesmanProblem : public Problem<SOL_STP, TYPE_FITNESS_STP, TYPE_CELL_STP> {
   public:
    TravelingSalesmanProblem() {}

    TravelingSalesmanProblem(const std::string &fileInstance) { 
        Json::Value config = loadInstance(fileInstance); 
        loadJson(config);
    }

    virtual ~TravelingSalesmanProblem() {}

    void loadJson(const Json::Value &config) {
        instance_number = config["problem"]["instance_number"].asString();
        numberOfNodes = config["problem"]["number_of_nodes"].asUInt();

        for (unsigned int i = 0 ; i < config["problem"]["node_coord_section"].size() ; i++) {
            double x = config["problem"]["node_coord_section"][i]["x"].asDouble();
            double y = config["problem"]["node_coord_section"][i]["y"].asDouble();
            nodes.push_back(std::pair<double, double>(x, y));
        }
    }

    std::unique_ptr<SOL_STP> new_solution() const {
        std::unique_ptr<SOL_STP> s(std::make_unique<SOL_STP>(nodes.size()));
        for (unsigned int i = 0; i < s->sizeArray(); i++) {
            s->operator()(i, i);
        }
        return std::move(s);
    }

    bool checkSolutionStructure(const SOL_STP &s) const {
        if (s.sizeArray() != nodes.size() || s.numberOfObjective() != 1) {
            return false;
        }
        return true;
    }

    virtual void evaluation(SOL_STP &s) {
        double distance_sum = 0;
        for (unsigned int i = 0; i < s.sizeArray() - 1; i++) {
            distance_sum += distance_euclidienne(nodes[s(i)], nodes[s(i + 1)]);
        }
        s.setFitness(distance_sum);
    }

	bool solutionSelection(const SOL_STP &s_worst, const SOL_STP &s_best) {
        return solution_selection(s_worst, s_best);
	}

	unsigned int solutionSelection(const Population<SOL_STP> &p) {
        return solution_selection(p);
	}

   private:
    
    double distance_euclidienne(const std::pair<double, double> &node_a, const std::pair<double, double> &node_b) const {
        return sqrt(abs(node_b.second - node_a.second) * abs(node_b.second - node_a.second) +
                    abs(node_b.first - node_a.first) * abs(node_b.first - node_a.first));
    }

    Minimization<SOL_STP> solution_selection;
    std::string instance_number;
    unsigned int numberOfNodes;
    std::vector<std::pair<double, double>> nodes;
};

}
#endif