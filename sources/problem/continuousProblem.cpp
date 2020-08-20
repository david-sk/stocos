///
/// @file continuousProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-08
/// @brief
///

#include <problem/continuousProblem.h>

namespace stocos {

ContinuousProblem::ContinuousProblem() : _domain(nullptr) {
}

ContinuousProblem::ContinuousProblem(std::string fileInstance) : _domain(nullptr) {
	Json::Value config = loadInstance(fileInstance);
	loadJson(config);
}

ContinuousProblem::~ContinuousProblem() {
}

void ContinuousProblem::loadJson(const Json::Value& config) {
	instance_number = config["problem"]["instance_number"].asString();

	for(unsigned int i = 0; i < config["problem"]["objectif"].size(); i++) {
		objectif.push_back(Objectif(config["problem"]["objectif"][i]["function"].asString(),
									config["problem"]["objectif"][i]["variables"]));
	}

	// Définition du nombre de varaibles
	nomberOfVariable = 0;
	for(unsigned int i = 0; i < objectif.size(); i++) {
		nomberOfVariable += objectif[i].getValueSize();
	}

	// Définie pour chaque variables son domaine
	_domain =
		std::make_unique<std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>[]>(
			nomberOfVariable);
	// solution_selection = std::make_unique<SolutionSelection<SOL_CONTINUOUSPROBLEM>
	// []>(objectif.size());
	for(unsigned int i = 0; i < config["problem"]["objectif"].size(); i++) {
		unsigned int domainSize = config["problem"]["objectif"][i]["domain"].size();
		for(unsigned int j = 0; j < domainSize; j++) {
			_domain[j] = std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>(
				config["problem"]["objectif"][i]["domain"][j][0].asDouble(),
				config["problem"]["objectif"][i]["domain"][j][1].asDouble());
		}
		solution_selection.push_back(
			SolutionSelectionBuilder<SOL_CONTINUOUSPROBLEM, TYPE_FITNESS_CONTINUOUSPROBLEM,
									 TYPE_CELL_CONTINUOUSPROBLEM>::
				build(*this, config["problem"]["objectif"][i]["solutionSelection"]));
	}
}

std::unique_ptr<SOL_CONTINUOUSPROBLEM> ContinuousProblem::new_solution() const {
	std::unique_ptr<SOL_CONTINUOUSPROBLEM> s =
		std::make_unique<SOL_CONTINUOUSPROBLEM>(objectif.size(), nomberOfVariable);
	return std::move(s);
}

void ContinuousProblem::evaluation(SOL_CONTINUOUSPROBLEM& s) {
	unsigned int offset = 0;
	for(unsigned int i = 0; i < objectif.size(); i++) {
		objectif[i].setValue(s, i + offset);
		offset += objectif[i].getValueSize() - 1;

		s.setFitness(i, objectif[i].getFitness());
	}
}

std::pair<TYPE_CELL_CONTINUOUSPROBLEM, TYPE_CELL_CONTINUOUSPROBLEM>
	ContinuousProblem::domain(unsigned index) const {
	assert(index < nomberOfVariable);

	if(_domain == nullptr)
		throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) +
								 "[-] Not implemented : domain()");
	return _domain[index];
}

bool ContinuousProblem::solutionSelection(const SOL_CONTINUOUSPROBLEM& s_worst,
										  const SOL_CONTINUOUSPROBLEM& s_best) {
	// ! Need to implement multi-objectif !
	return solution_selection[0]->operator()(s_worst, s_best);
}

unsigned int ContinuousProblem::solutionSelection(const Population<SOL_CONTINUOUSPROBLEM>& p) {
	// ! Need to implement multi-objectif !
	return solution_selection[0]->operator()(p);
}

} // namespace stocos