///
/// @file jobShopProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief https://developers.google.com/optimization/scheduling/job_shop
///
#include <problem/jobShopProblem.h>

namespace stocos {

JobShopProblem::JobShopProblem(const std::string& fileInstance) {
	Json::Value config = loadInstance(fileInstance);
	loadJson(config);
}

JobShopProblem::~JobShopProblem() {
}

void JobShopProblem::loadJson(const Json::Value& config) {
	// std::cout<<root<<std::endl;
	// for (auto name : root["problem"].getMemberNames()) {
	//     std::cout<<name<<std::endl;
	// }

	// _N = root["problem"]["N"].asUInt();
}

const std::vector<std::vector<std::pair<unsigned int, unsigned int>>>&
	JobShopProblem::getInstance() const {
	return instance;
}

void JobShopProblem::evaluation(SOL_JOBSHOPPROBLEM& s) {
}

/*void JobShopProblem::incremental(SolutionArray const &s, unsigned int mutatedCell) const {

}*/

void JobShopProblem::resetSolution(SOL_JOBSHOPPROBLEM& s) const {
}

} // namespace stocos