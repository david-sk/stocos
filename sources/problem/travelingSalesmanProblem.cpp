///
/// @file travelingSalesmanProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-07
/// @brief
///         instances : http://elib.zib.de/pub/mp-testdata/tsp/tsplib/tsplib.html
///

#include <problem/travelingSalesmanProblem.h>

namespace stocos {

TravelingSalesmanProblem::TravelingSalesmanProblem() {
}

TravelingSalesmanProblem::TravelingSalesmanProblem(const std::string& fileInstance) {
    Json::Value config = loadInstance(fileInstance);
    loadJson(config);
}

TravelingSalesmanProblem::~TravelingSalesmanProblem() {
}

void TravelingSalesmanProblem::loadJson(const Json::Value& config) {
    instance_number = config["problem"]["instance_number"].asString();
    numberOfNodes = config["problem"]["number_of_nodes"].asUInt();

    for(unsigned int i = 0; i < config["problem"]["node_coord_section"].size(); i++) {
        double x = config["problem"]["node_coord_section"][i]["x"].asDouble();
        double y = config["problem"]["node_coord_section"][i]["y"].asDouble();
        nodes.push_back(std::pair<double, double>(x, y));
    }
}

std::unique_ptr<SOL_STP> TravelingSalesmanProblem::new_solution() const {
    std::unique_ptr<SOL_STP> s(std::make_unique<SOL_STP>(nodes.size()));
    for(unsigned int i = 0; i < s->sizeArray(); i++) { s->operator()(i, i); }
    return std::move(s);
}

bool TravelingSalesmanProblem::checkSolutionStructure(const SOL_STP& s) const {
    if(s.sizeArray() != nodes.size() || s.numberOfObjective() != 1) { return false; }
    return true;
}

void TravelingSalesmanProblem::evaluation(SOL_STP& s) {
    // Validation de la solution
    std::map<TYPE_CELL_STP, unsigned int> count; // <id, count>

    for(unsigned int i = 0; i < s.sizeArray(); i++) {
        if(count.find(s(i)) != count.end()) { // Key found
            count[s(i)] += 1;
            s.setFitness(std::numeric_limits<double>::max());
            // s.setFitness(std::numeric_limits<double>::infinity());
            return;
        } else { // Key not found
            count[s(i)] = 1;
        }
    }

    // Calcul de la fitness
    double distance_sum = 0;
    for(unsigned int i = 0; i < s.sizeArray() - 1; i++) {
        distance_sum += distance_euclidienne(nodes[s(i)], nodes[s(i + 1)]);
    }
    s.setFitness(distance_sum);
}

bool TravelingSalesmanProblem::solutionSelection(const SOL_STP& s_worst, const SOL_STP& s_best) {
    return solution_selection(s_worst, s_best);
}

unsigned int TravelingSalesmanProblem::solutionSelection(const Population<SOL_STP>& p) {
    return solution_selection(p);
}

double
    TravelingSalesmanProblem::distance_euclidienne(const std::pair<double, double>& node_a,
                                                   const std::pair<double, double>& node_b) const {
    return sqrt(abs(node_b.second - node_a.second) * abs(node_b.second - node_a.second) +
                abs(node_b.first - node_a.first) * abs(node_b.first - node_a.first));
}

} // namespace stocos