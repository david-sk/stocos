///
/// \file solver.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SOLVER_GENERIC_H
#define	SOLVER_GENERIC_H

#include <cassert>
#include <random>
#include <string>

#include <boost/program_options.hpp>

#include "solver.h"

using namespace std;

class SolverGeneric : public Solver {
	public:
		SolverGeneric(std::mt19937 &mt_rand, 
			boost::program_options::variables_map &vm, 
			boost::program_options::options_description & desc, 
			int argc, 
			char **argv) : 
			Solver(mt_rand, vm, desc, argc, argv) {

		}
		virtual ~SolverGeneric() {
			
		}

	protected:
};

#endif
