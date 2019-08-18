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
	virtual void loadInstance(const string &file) = 0;
	
	// Generating a solution
	virtual void reset_solution(SOL &s) const {
		cerr<<"[-] Not implemented : reset_solution()"<<endl;
		exit(EXIT_FAILURE);
	}
	virtual std::unique_ptr<SOL> new_solution() const {
		cerr<<"[-] Not implemented : new_solution()"<<endl;
		exit(EXIT_FAILURE);
	}

	// Evaluation of the solution
	virtual void full_eval(SOL &s) = 0;
	/*virtual void incremental_eval(const SOL &s, const vector<pair<unsigned int, TYPE_CELL>> &_listOfMutations) const {
		cerr<<"[-] not implemented"<<endl;
		exit(EXIT_FAILURE);
	};*/
	virtual bool filtering(SOL &s) const {
		cerr<<"[-] Not implemented : getFitnessObjectif()"<<endl;
		exit(EXIT_FAILURE);
		return true;
	}
	virtual TYPE_FITNESS getFitnessObjectif() const {
		cerr<<"[-] Not implemented : getFitnessObjectif()"<<endl;
		exit(EXIT_FAILURE);
	}

	virtual TYPE_FITNESS getFitnessObjectif(unsigned int numObjectif) const {
		cerr<<"[-] Not implemented : getFitnessObjectif(unsigned int numObjectif)"<<endl;
		exit(EXIT_FAILURE);
	}
	
	
private:
	
};

#endif