///
/// @file jobShopProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief https://developers.google.com/optimization/scheduling/job_shop
///

#ifndef EVALJOBSHOPPROBLEM_H
#define EVALJOBSHOPPROBLEM_H

#include <fstream>
#include <map>
#include <utility>

#include <jsoncpp/json/json.h>

#include "../solution/solution.h"
#include "problem.h"

namespace stocos {

using TYPE_FITNESS_JOBSHOPPROBLEM = double;
using TYPE_CELL_JOBSHOPPROBLEM = bool;
using SOL_JOBSHOPPROBLEM = Solution<TYPE_FITNESS_JOBSHOPPROBLEM, TYPE_CELL_JOBSHOPPROBLEM>;
class JobShopProblem
	: public Problem<SOL_JOBSHOPPROBLEM, TYPE_FITNESS_JOBSHOPPROBLEM, TYPE_CELL_JOBSHOPPROBLEM> {
  public:
	JobShopProblem(const std::string& fileInstance);

	~JobShopProblem();

	void loadJson(const Json::Value& config);

	friend std::ostream& operator<<(std::ostream& out, const JobShopProblem& e) {
		std::cout << "job X : (machine_id, processing_time)";
		std::vector<std::vector<std::pair<unsigned int, unsigned int>>> const _instance =
			e.getInstance();
		for(unsigned int i = 0; i < _instance.size(); i++) {
			out << std::endl << "job " << i << ":" << std::endl;
			for(unsigned int j = 0; j < _instance[i].size(); j++) {
				out << "(" << _instance[i][j].first << ", " << _instance[i][j].second << "), ";
			}
		}
		return out;
	}

	const std::vector<std::vector<std::pair<unsigned int, unsigned int>>>& getInstance() const;

	void evaluation(SOL_JOBSHOPPROBLEM& s);

	// void incremental(Solution const &s, unsigned int mutatedCell) const;

	void resetSolution(SOL_JOBSHOPPROBLEM& s) const;

  private:
	std::vector<std::vector<std::pair<unsigned int, unsigned int>>> instance;
};

} // namespace stocos
#endif