///
/// @file unitTest_knapsack.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../../../../unitTest.h"

#ifndef UNITTEST_KBIT_H
#define UNITTEST_KBIT_H

#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/mutation/KBit.h"
#include "problem/oneMax.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_kBit : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_kBit);
	CPPUNIT_TEST(cancelMutations);
	CPPUNIT_TEST(listOfMutations);
	CPPUNIT_TEST_SUITE_END();

  public:
	void cancelMutations(void) {
		unsigned int N = 50;
		SOL_ONEMAX s1(N);
		SOL_ONEMAX s2(N);
		for(unsigned int i = 0; i < N; i++) {
			s1(i, 0);
			s2(i, 0);
		}

		mt_rand.seed(0);
		KBit<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> kbit(mt_rand, 20);
		kbit(s1);
		kbit.cancelMutations(s1);
		CPPUNIT_ASSERT(s1 == s2);
	}

	//! TODO need to fixed
	void listOfMutations(void) {
		unsigned int N = 50;
		SOL_ONEMAX s1(N);
		SOL_ONEMAX s2(N);
		unsigned int checklist[] = {39, 15, 1,  25, 32, 22, 38, 42, 29, 11, 10, 36, 13, 8,  4,
									7,  34, 48, 41, 0,  17, 26, 45, 31, 44, 14, 37, 46, 27, 6,
									21, 19, 9,  5,  3,  33, 2,  30, 16, 28, 20, 43, 50, 23, 18};

		mt_rand.seed(10);
		KBit<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> kbit(mt_rand, 45);
		// std::unique_ptr<vector<unsigned int>> list = kbit.listOfMutations(s1);

		// for (unsigned int i = 0 ; i < list->size() ; i++) {
		//     CPPUNIT_ASSERT((*list)[i] == checklist[i]);
		// }
	}

  private:
	std::mt19937 mt_rand;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_kBit);

#endif