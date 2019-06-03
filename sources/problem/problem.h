///
/// \file problem.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief description of the optimization problem
///


#ifndef PROBLEM_H
#define PROBLEM_H

#include "../solution/solution.h"

template<typename SOL, typename TYPE_CELL>
class Problem {
public:
	Problem() {

	}

	~Problem() {

	}
	
	// Loading an instance
	virtual void loadInstance(string file) = 0;
	
	// Generating a solution
	virtual void reset_solution(SOL &s) const = 0;
	//virtual unique_ptr<SOL> new_solution() const = 0;

	// Evaluation of the solution
	virtual void full_eval(SOL &s) const = 0;
	/*virtual void incremental_eval(const SOL &s, const vector<pair<unsigned int, TYPE_CELL>> &_listOfMutations) const {
		cerr<<"[-] not implemented"<<endl;
		exit(EXIT_FAILURE);
	};*/
	virtual bool filtering(SOL &s) const {
		return true;
	}
	
	
private:
	
};

#endif