///
/// @file latinSquare.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include <problem/latinSquare.h>

namespace stocos {

LatinSquare::LatinSquare() : _N(1) {
}

LatinSquare::LatinSquare(const std::string& fileInstance) {
	Json::Value config = loadInstance(fileInstance);
	loadJson(config);
}

LatinSquare::LatinSquare(unsigned int N) : _N(N) {
}

LatinSquare::~LatinSquare() {
}

void LatinSquare::loadJson(const Json::Value& config) {
	instance_number = config["problem"]["instance_number"].asString();
	_N = config["problem"]["N"].asUInt();
}

std::unique_ptr<SOL_LATINSQUARE> LatinSquare::new_solution() const {
	std::unique_ptr<SOL_LATINSQUARE> s(std::make_unique<SOL_LATINSQUARE>(_N));
	for(unsigned int i = 0; i < s->sizeArray(); i++) { s->operator()(i, 0); }
	return std::move(s);
}

bool LatinSquare::checkSolutionStructure(const SOL_LATINSQUARE& s) const {
	if(s.sizeArray() != _N || s.numberOfObjective() != 1) { return false; }
	return true;
}

void LatinSquare::evaluation(SOL_LATINSQUARE& s) {
	//
}

/*void LatinSquare::incremental(const Solution &s, unsigned int mutatedCell) const {

}*/

void LatinSquare::resetSolution(SOL_LATINSQUARE& s) const {
	for(unsigned int i = 0; i < s.sizeArray(); i++) { s(i, 0); }
}

TYPE_FITNESS_LATINSQUARE LatinSquare::getFitnessObjectif(unsigned int numObjectif) const {
	assert(numObjectif = 0);
	return _N;
}

bool LatinSquare::solutionSelection(const SOL_LATINSQUARE& s_worst, const SOL_LATINSQUARE& s_best) {
	return solution_selection(s_worst, s_best);
}

unsigned int LatinSquare::solutionSelection(const Population<SOL_LATINSQUARE>& p) {
	return solution_selection(p);
}
} // namespace stocos