///
/// @file magicSequence.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief magic sequence Problem
///

#include <problem/magicSequence.h>

namespace stocos {

MagicSequence::MagicSequence() {
}

void MagicSequence::loadJson(const Json::Value& config) {
}

void MagicSequence::evaluation(SOL_MAGICSEQUENCE& s) {
	double resultat = 0;
	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		unsigned int count = 0;
		for(unsigned int j = 0; j < s.sizeArray(); j++) {
			if(s(j) == i) { count++; }
		}

		if(count == s(i)) { resultat += 1; }
	}

	s.setFitness(0, resultat / static_cast<double>(s.sizeArray()));
}

/*void MagicSequence::incremental(const SolutionArray &s, unsigned int mutatedCell) const {

}*/

void MagicSequence::resetSolution(SOL_MAGICSEQUENCE& s) const {
}

bool MagicSequence::solutionSelection(const SOL_MAGICSEQUENCE& s_worst, const SOL_MAGICSEQUENCE& s_best) {
	return solution_selection(s_worst, s_best);
}

unsigned int MagicSequence::solutionSelection(const Population<SOL_MAGICSEQUENCE>& p) {
	return solution_selection(p);
}

} // namespace stocos