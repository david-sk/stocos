///
/// @file oneMax.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <problem/oneMax.h>

namespace stocos {

OneMax::OneMax() : _N(1) {
}

OneMax::OneMax(const std::string& fileInstance) {
    Json::Value config = loadInstance(fileInstance);
    loadJson(config);
}

OneMax::OneMax(unsigned int N) : _N(N) {
}

OneMax::~OneMax() {
}

void OneMax::loadJson(const Json::Value& config) {
    instance_number = config["problem"]["instance_number"].asString();
    _N = config["problem"]["N"].asUInt();
}

std::unique_ptr<SOL_ONEMAX> OneMax::new_solution() const {
    std::unique_ptr<SOL_ONEMAX> s(std::make_unique<SOL_ONEMAX>(_N));
    for(unsigned int i = 0; i < s->sizeArray(); i++) { s->operator()(i, 0); }
    return std::move(s);
}

bool OneMax::checkSolutionStructure(const SOL_ONEMAX& s) const {
    if(s.sizeArray() != _N || s.numberOfObjective() != 1) { return false; }
    return true;
}

void OneMax::evaluation(SOL_ONEMAX& s) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < s.sizeArray(); i++) { sum += s(i); }
    s.setFitness(0, sum);
}

/*void OneMax::incremental(const Solution &s, unsigned int mutatedCell) const {

}*/

void OneMax::resetSolution(SOL_ONEMAX& s) const {
    for(unsigned int i = 0; i < s.sizeArray(); i++) { s(i, 0); }
}

TYPE_FITNESS_ONEMAX OneMax::getFitnessObjectif(unsigned int numObjectif) const {
    assert(numObjectif = 0);
    return _N;
}

bool OneMax::solutionSelection(const SOL_ONEMAX& s_worst, const SOL_ONEMAX& s_best) {
    return solution_selection(s_worst, s_best);
}

unsigned int OneMax::solutionSelection(const Population<SOL_ONEMAX>& p) {
    return solution_selection(p);
}

} // namespace stocos