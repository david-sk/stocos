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
	
	virtual void full_eval(SOL &s) const = 0;
	virtual void reset_solution(SOL &s) const = 0;
	
	/*void incremental(const SOL &s) = 0;*/
	
private:
	
};

#endif