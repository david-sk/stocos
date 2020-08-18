///
/// @file flipBit.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include<optimization/metaheuristic/operator/mutation/flipBit.h>
namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
FlipBit<SOL,TYPE_FITNESS,TYPE_CELL>::FlipBit(std::mt19937& mt_rand, std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem,
		unsigned int c)
	: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem), _c(c), N(0) {
	urd = std::make_unique<std::uniform_real_distribution<>>(0, 1);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
FlipBit<SOL,TYPE_FITNESS,TYPE_CELL>::~FlipBit() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void FlipBit<SOL,TYPE_FITNESS,TYPE_CELL>::operator()(SOL& s) {
	backup.clear();
	if(s.sizeArray() != N) {
		N = s.sizeArray();
		mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
		backup.reserve(N);
	}

	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		if(urd->operator()(this->_mt_rand) < mutation_rate) {
			if(s(i) == 1)
				s(i, 0);
			else
				s(i, 1);
			backup.push_back(i);
		}
	}
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void FlipBit<SOL,TYPE_FITNESS,TYPE_CELL>::cancelMutations(SOL& s) const {
	for(unsigned int i = 0; i < backup.size(); i++) {
		if(s(backup[i]) == 1)
			s(backup[i], 0);
		else
			s(backup[i], 1);
	}
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> FlipBit<SOL,TYPE_FITNESS,TYPE_CELL>::listOfMutations(const SOL& s) {
	std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> list(
		std::make_unique<std::vector<std::pair<unsigned int, TYPE_CELL>>>());

	if(s.sizeArray() != N) {
		N = s.sizeArray();
		mutation_rate = static_cast<double>(_c) / static_cast<double>(N);
	}

	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		if(urd->operator()(this->_mt_rand) < mutation_rate) {
			if(s(i) == 1)
				list->push_back(std::pair<unsigned int, TYPE_CELL>(i, 0));
			else
				list->push_back(std::pair<unsigned int, TYPE_CELL>(i, 1));
		}
	}
	return std::move(list);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void FlipBit<SOL,TYPE_FITNESS,TYPE_CELL>::applyOperator(SOL& s,
					const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations) {
	backup.clear();
	for(unsigned int i = 0; i < _listOfMutations.size(); i++) {
		s(_listOfMutations[i].first, _listOfMutations[i].second);
		backup.push_back(i);
	}
}

template class FlipBit<SolutionArray<double, double>, double, double>;
template class FlipBit<SolutionArray<double, bool>, double, bool>;
template class FlipBit<SolutionArray<int, bool>, int, bool>;
template class FlipBit<SolutionArray<unsigned int, bool>, unsigned int, bool>;
template class FlipBit<SolutionArray<double, unsigned int>, double, unsigned int>;
template class FlipBit<SolutionArray<unsigned int, unsigned int>, unsigned int, unsigned int>;
} // namespace stocos