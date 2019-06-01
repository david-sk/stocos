//
// @Author: Jxtopher
// @License: *
// @Date: 2018-10
// @Version: *
// @Purpose: *
// 

#ifndef PROBLEM_H
#define PROBLEM_H

#include "../solution/solution.h"

template<class SOL>
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
	virtual bool filtering(SOL &s) const {
		return true;
	}
	/*void incremental(const SOL &s) = 0;*/
	
private:
	
};

#endif