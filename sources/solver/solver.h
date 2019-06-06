///
/// \file solver.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SOLVER_H
#define	SOLVER_H

#include <random>
#include <string>

#include <boost/program_options.hpp>

using namespace std;

class Solver {
	public:
		Solver(std::mt19937 &mt_rand, 
			boost::program_options::variables_map &vm, 
			boost::program_options::options_description & desc, 
			int argc, 
			char **argv) : 
			_mt_rand(mt_rand), 
			_vm(vm),
			_desc(desc) {

		}
		virtual ~Solver() {
			
		}

		virtual void operator()(string &solution, int numParameter) = 0;
		virtual void initializationSolution() = 0;
		virtual void settings(int argc, char **argv) = 0;
		virtual void operator()() = 0;

	protected:
		std::mt19937 &_mt_rand;
		boost::program_options::variables_map _vm;
		boost::program_options::options_description _desc;
};

#endif
