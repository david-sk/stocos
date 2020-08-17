///
/// @file subsetSum.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief https://en.wikipedia.org/wiki/Subset_sum_problem
///
#include <problem/subsetSum.h>

namespace stocos {

Subsetsum::Subsetsum() {
	generateInstance(1);
}

Subsetsum::Subsetsum(const unsigned int N) {
	generateInstance(N);
}

Subsetsum::Subsetsum(const std::string& fileInstance) {
	Json::Value config = loadInstance(fileInstance);
	loadJson(config);
}

void Subsetsum::generateInstance(const unsigned int N) {
	setOfNumbers.clear();
	for(unsigned int i = 1; i <= N; i++) {
		setOfNumbers.push_back(i % 50);
		if(i % 3) fitnessObjectif += i;
	}
};

Subsetsum::~Subsetsum() {
}

void Subsetsum::loadJson(const Json::Value& config) {
	std::string encoding = config.get("encoding", "UTF-8").asString();

	fitnessObjectif = config["problem"]["fitnessObjectif"].asUInt();
	for(unsigned int i = 0; i < config["problem"]["set"].size(); i++) {
		setOfNumbers.push_back(config["problem"]["set"][i].asUInt());
	}
}

TYPE_FITNESS_SUBSETSUM Subsetsum::getFitnessObjectif(unsigned int numObjectif) const {
	assert(numObjectif = 0);
	return fitnessObjectif;
}

void Subsetsum::evaluation(SOL_SUBSETSUM& s) {
	assert(setOfNumbers.size() == s.sizeArray());
	unsigned int sum = 0;
	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		if(s(i) == 1) { sum += setOfNumbers[i]; }
	}
	s.setFitness(0, sum);
}

void Subsetsum::resetSolution(SOL_SUBSETSUM& s) const {
	for(unsigned int i = 0; i < s.sizeArray(); i++) { s(i, 0); }
}

std::unique_ptr<SOL_SUBSETSUM> Subsetsum::new_solution() const {
	std::unique_ptr<SOL_SUBSETSUM> s(std::make_unique<SOL_SUBSETSUM>(setOfNumbers.size()));
	for(unsigned int i = 0; i < s->sizeArray(); i++) { s->operator()(i, 0); }
	return std::move(s);
}

} // namespace stocos