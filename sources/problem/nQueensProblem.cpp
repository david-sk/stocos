///
/// @file nQueensProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <problem/nQueensProblem.h>

namespace stocos {

NQueensProblem::NQueensProblem() : _n(1) {
}

NQueensProblem::NQueensProblem(const std::string& fileInstance) {
    Json::Value config = loadInstance(fileInstance);
    loadJson(config);
}

NQueensProblem::NQueensProblem(unsigned int n) : _n(n) {
}

NQueensProblem::~NQueensProblem() {
}

void NQueensProblem::loadJson(const Json::Value& config) {
    instance_number = config["problem"]["instance_number"].asString();
    _n = config["problem"]["n"].asUInt();
}

std::unique_ptr<SOL_NQUEENSPROBLEM> NQueensProblem::new_solution() const {
    std::unique_ptr<SOL_NQUEENSPROBLEM> s(std::make_unique<SOL_NQUEENSPROBLEM>(_n));
    for(unsigned int i = 0; i < s->sizeArray(); i++) { s->operator()(i, 0); }
    return std::move(s);
}

bool NQueensProblem::checkSolutionStructure(const SOL_NQUEENSPROBLEM& s) const {
    if(s.sizeArray() != _n || s.numberOfObjective() != 1) { return false; }
    return true;
}

void NQueensProblem::evaluation(SOL_NQUEENSPROBLEM& s) {
    unsigned int fitness = 0;
    bool stat = true;
    for(unsigned int i = 0; i < _n; i++) {
        for(unsigned int j = i + 1; j < _n; j++) {
            if(abs(s(i) - s(j)) == abs(static_cast<int>(i) - static_cast<int>(j))) stat = false;
            if(s(i) == s(j)) stat = false;
        }
        if(stat) fitness++;
    }
    s.setFitness(0, fitness);
}

void NQueensProblem::resetSolution(SOL_NQUEENSPROBLEM& s) const {
    for(unsigned int i = 0; i < s.sizeArray(); i++) { s(i, 0); }
}

TYPE_FITNESS_NQUEENSPROBLEM NQueensProblem::getFitnessObjectif(unsigned int numObjectif) const {
    assert(numObjectif = 0);
    return _n;
}

bool NQueensProblem::solutionSelection(const SOL_NQUEENSPROBLEM& s_worst,
                                       const SOL_NQUEENSPROBLEM& s_best) {
    return solution_selection(s_worst, s_best);
}

unsigned int NQueensProblem::solutionSelection(const Population<SOL_NQUEENSPROBLEM>& p) {
    return solution_selection(p);
}

bool NQueensProblem::evaluationSubSolution(SOL_NQUEENSPROBLEM& s) const {
    if(s.sizeArray() == 1) return true;
    return check_diagonal(s) && check_line(s);
}

bool NQueensProblem::check_diagonal(const SOL_NQUEENSPROBLEM& solution) const {
    for(unsigned int i = 0; i < solution.sizeArray(); i++) {
        for(unsigned int j = i + 1; j < solution.sizeArray(); j++) {
            if(abs(solution(i) - solution(j)) == abs(static_cast<int>(i) - static_cast<int>(j))) {
                return false;
            }
        }
    }
    return true;
}

bool NQueensProblem::check_line(const SOL_NQUEENSPROBLEM& solution) const {
    for(unsigned int i = 0; i < solution.sizeArray(); i++) {
        for(unsigned int j = i + 1; j < solution.sizeArray(); j++) {
            if(solution(i) == solution(j)) return false;
        }
    }
    return true;
}

} // namespace stocos