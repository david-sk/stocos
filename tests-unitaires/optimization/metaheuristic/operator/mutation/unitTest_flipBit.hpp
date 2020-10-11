///
/// @file unitTest_knapsack.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef UNITTEST_FLIPBIT_H
#define UNITTEST_FLIPBIT_H

#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/mutation/flipBit.h"
#include "problem/oneMax.h"
#include "solution/solutionArray.h"

using namespace CppUnit;

class UnitTest_flipBit : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_flipBit);
	CPPUNIT_TEST(operator());
	CPPUNIT_TEST(cancelMutations);
	CPPUNIT_TEST(listOfMutations);
	CPPUNIT_TEST(applyOperator);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		mt_rand.seed(0);
	}
	void tearDown(void) {
	}

	void operator()(void) {
		unsigned int N = 50;
		SOL_ONEMAX s(N);

		for(unsigned int i = 0; i < N; i++) { s(i, 0); }

		FlipBit<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> flipbit(mt_rand, 0);
		flipbit(s);
	}

	void cancelMutations(void) {
		unsigned int N = 50;
		SOL_ONEMAX s1(1, N);
		SOL_ONEMAX s2(1, N);

		for(unsigned int i = 0; i < N; i++) {
			s1(i, 0);
			s2(i, 0);
		}

		FlipBit<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> flipbit(mt_rand, 0);
		flipbit(s1);
		flipbit.cancelMutations(s1);
		CPPUNIT_ASSERT(s1 == s2);
	}

	void listOfMutations(void) {
		unsigned int N = 50;
		SOL_ONEMAX s1(1, N);

		FlipBit<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> flipbit(mt_rand, 5);
		std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL_ONEMAX>>> mutations =
			flipbit.listOfMutations(s1);
	}

	void applyOperator(void) {
		unsigned int N = 50;
		SOL_ONEMAX s1(1, N);
		SOL_ONEMAX s2(s1);

		FlipBit<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> flipbit(mt_rand, 5);
		std::unique_ptr<std::vector<std::pair<unsigned int, TYPE_CELL_ONEMAX>>> mutations =
			flipbit.listOfMutations(s1);
		flipbit.applyOperator(s1, *mutations);

		CPPUNIT_ASSERT(!(s1 == s2));
	}

  private:
	std::mt19937 mt_rand;
};

#endif