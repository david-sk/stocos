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

NQueensProblem::NQueensProblem() : _N(1) {
}

NQueensProblem::NQueensProblem(const std::string& fileInstance) {
	Json::Value config = loadInstance(fileInstance);
	loadJson(config);
}

NQueensProblem::NQueensProblem(unsigned int N) : _N(N) {
}

NQueensProblem::~NQueensProblem() {
}

void NQueensProblem::loadJson(const Json::Value& config) {
	instance_number = config["problem"]["instance_number"].asString();
	_N = config["problem"]["N"].asUInt();
}

std::unique_ptr<SOL_NQUEENSPROBLEM> NQueensProblem::new_solution() const {
	std::unique_ptr<SOL_NQUEENSPROBLEM> s(std::make_unique<SOL_NQUEENSPROBLEM>(_N));
	for(unsigned int i = 0; i < s->sizeArray(); i++) { s->operator()(i, 0); }
	return std::move(s);
}

bool NQueensProblem::checkSolutionStructure(const SOL_NQUEENSPROBLEM& s) const {
	if(s.sizeArray() != _N || s.numberOfObjective() != 1) { return false; }
	return true;
}

void NQueensProblem::evaluation(SOL_NQUEENSPROBLEM& s) {
	unsigned int sum = 0;
	for(unsigned int i = 0; i < s.sizeArray(); i++) { sum += s(i); }
	s.setFitness(0, sum);
}

/*void NQueensProblem::incremental(const SolutionArray &s, unsigned int mutatedCell) const {

}*/

void NQueensProblem::resetSolution(SOL_NQUEENSPROBLEM& s) const {
	for(unsigned int i = 0; i < s.sizeArray(); i++) { s(i, 0); }
}

TYPE_FITNESS_NQUEENSPROBLEM NQueensProblem::getFitnessObjectif(unsigned int numObjectif) const {
	assert(numObjectif = 0);
	return _N;
}

bool NQueensProblem::solutionSelection(const SOL_NQUEENSPROBLEM& s_worst, const SOL_NQUEENSPROBLEM& s_best) {
	return solution_selection(s_worst, s_best);
}

unsigned int NQueensProblem::solutionSelection(const Population<SOL_NQUEENSPROBLEM>& p) {
	return solution_selection(p);
}

} // namespace stocos