///
/// @file knapsack.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief Knapsack Problem
///

#include <problem/knapsack.h>

namespace stocos {

Knapsack::Knapsack() {
}

Knapsack::Knapsack(const std::string& fileInstance) {
	Json::Value config = loadInstance(fileInstance);
	loadJson(config);
}

Knapsack::~Knapsack() {
}

void Knapsack::loadJson(const Json::Value& config) {
	instance_number = config["problem"]["instance_number"].asString();
	capacity = config["problem"]["capacity"].asInt();
	nbItems = config["problem"]["#items"].asUInt();

	for(unsigned int i = 0; i < nbItems; i++) {
		weight.push_back(config["problem"]["weight"][i].asInt());
		profit.push_back(config["problem"]["profit"][i].asInt());
	}

	assert(nbItems == weight.size());
	assert(weight.size() == profit.size());
}

void Knapsack::evaluation(SOL_KNAPSACK& s) {
	int fitness = 0;
	int W = 0;

	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		fitness += profit[i] * s(i);
		W += weight[i] * s(i);
	}

	if(capacity < W) fitness = -1;
	s.setFitness(fitness);
}

/*void Knapsack::incremental(const SolutionArray &s, unsigned int mutatedCell) const {

}*/

void Knapsack::resetSolution(SOL_KNAPSACK& s) const {
	for(unsigned int i = 0; i < s.sizeArray(); i++) { s(i, 0); }
}

std::unique_ptr<SOL_KNAPSACK> Knapsack::new_solution() const {
	std::unique_ptr<SOL_KNAPSACK> s(std::make_unique<SOL_KNAPSACK>(nbItems));
	for(unsigned int i = 0; i < s->sizeArray(); i++) { s->operator()(i, 0); }
	return std::move(s);
}

unsigned int Knapsack::sizeArraySolution() const {
	return nbItems;
}

TYPE_FITNESS_KNAPSACK Knapsack::getFitnessObjectif(unsigned int numObjectif) const {
	assert(numObjectif = 0);
	return fitnessObjectif;
}

bool Knapsack::solutionSelection(const SOL_KNAPSACK& s_worst, const SOL_KNAPSACK& s_best) {
	return solution_selection(s_worst, s_best);
}

unsigned int Knapsack::solutionSelection(const Population<SOL_KNAPSACK>& p) {
	return solution_selection(p);
}

} // namespace stocos