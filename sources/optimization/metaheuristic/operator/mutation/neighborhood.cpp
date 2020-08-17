///
/// @file neighborhood.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include<optimization/metaheuristic/operator/mutation/neighborhood.h>


namespace stocos {

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Neighborhood<SOL,TYPE_FITNESS,TYPE_CELL>::Neighborhood(std::mt19937& mt_rand,
				std::shared_ptr<Problem<SOL, TYPE_FITNESS, TYPE_CELL>> problem)
	: AtomicOperation<SOL, TYPE_FITNESS, TYPE_CELL>(mt_rand, problem) {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
Neighborhood<SOL,TYPE_FITNESS,TYPE_CELL>::~Neighborhood() {
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void Neighborhood<SOL,TYPE_FITNESS,TYPE_CELL>::operator()(SOL& s) {
	std::cerr << "Not implemented" << std::endl;
	exit(EXIT_FAILURE);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>>
	Neighborhood<SOL,TYPE_FITNESS,TYPE_CELL>::listOfMutations(const SOL& s) {
	std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL>>> list(
		std::make_unique<std::vector<std::pair<unsigned int, TYPE_CELL>>>());
	SOL s1 = s;
	for(unsigned int i = 0; i < s.sizeArray(); i++) {
		if(s(i) == 1) {
			s1(i, 0);
			list->push_back(std::pair<unsigned int, SOL>(i, s1));
			s1(i, 1);
		} else {
			s1(i, 1);
			list->push_back(std::pair<unsigned int, SOL>(i, s1));
			s1(i, 0);
		}
	}

	return std::move(list);
}

template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
void
	Neighborhood<SOL,TYPE_FITNESS,TYPE_CELL>::applyOperator(SOL& s,
					const std::vector<std::pair<unsigned int, TYPE_CELL>>& _listOfMutations) {
	std::cerr << "Not implemented" << std::endl;
	exit(EXIT_FAILURE);
}

} // namespace stocos