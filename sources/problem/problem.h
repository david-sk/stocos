///
/// @file problem.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief description of the optimization problem
///


#ifndef PROBLEM_H
#define PROBLEM_H

#include "../solution/solution.h"


template<typename SOL, typename TYPE_FITNESS, typename TYPE_CELL>
class Problem {
public:
	Problem() {

	}

	virtual ~Problem() {

	}
	
	// Loading an instance
	virtual void loadInstance(const std::string &file) = 0;
	
	// Generating a solution
	virtual void reset_solution(SOL &s) const {
		std::cerr<<"[-] Not implemented : reset_solution()"<<std::endl;
		exit(EXIT_FAILURE);
	}
	virtual std::unique_ptr<SOL> new_solution() const {
		std::cerr<<"[-] Not implemented : new_solution()"<<std::endl;
		exit(EXIT_FAILURE);
	}

	// Evaluation of the solution
	virtual void full_eval(SOL &s) = 0;
	/*virtual void incremental_eval(const SOL &s, const std::vector<std::pair<unsigned int, TYPE_CELL>> &_listOfMutations) const {
		std::cerr<<"[-] not implemented"<<std::endl;
		exit(EXIT_FAILURE);
	};*/
	virtual bool filtering(SOL &s) const {
		std::cerr<<"[-] Not implemented : getFitnessObjectif()"<<std::endl;
		exit(EXIT_FAILURE);
		return true;
	}
	virtual TYPE_FITNESS getFitnessObjectif() const {
		std::cerr<<"[-] Not implemented : getFitnessObjectif()"<<std::endl;
		exit(EXIT_FAILURE);
	}

	virtual TYPE_FITNESS getFitnessObjectif(unsigned int numObjectif) const {
		std::cerr<<"[-] Not implemented : getFitnessObjectif(unsigned int numObjectif)"<<std::endl;
		exit(EXIT_FAILURE);
	}
	
	
private:
	
};

#endif