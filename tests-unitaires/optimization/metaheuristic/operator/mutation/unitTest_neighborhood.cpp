///
/// @file unitTest_neighborhood.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../../../../unitTest.h"

#ifndef UNITTEST_NEIGHBORHOOD_H
#define UNITTEST_NEIGHBORHOOD_H

#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/atomicOperation.h"
#include "optimization/metaheuristic/operator/mutation/neighborhood.h"
#include "problem/oneMax.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solution/solutionArray.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_neighborhood : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_neighborhood);
	CPPUNIT_TEST(listOfMutations);
	CPPUNIT_TEST_SUITE_END();

  public:
	void listOfMutations(void) {
		// unsigned int N = 5;
		// std::shared_ptr<OneMax> oneMax = std::make_shared<OneMax>(N);
		// SOL_ONEMAX s1(1, N);
		// s1(0, 1);
		// s1(1, 0);
		// s1(2, 1);
		// s1(3, 0);
		// s1(4, 0);
		// SOL_ONEMAX s2(1, N);
		// s2(0, 1);
		// s2(1, 1);
		// s2(2, 1);
		// s2(3, 0);
		// s2(4, 0);

		// std::mt19937 mt_rand;
		// mt_rand.seed(10);
		// AtomicOperation<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> *atomicOperations =
		// new Neighborhood<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX>(mt_rand, oneMax);
		// std::unique_ptr<std::vector<std::pair<unsigned int, SOL_ONEMAX>>> l =
		// atomicOperations->listOfMutations(s1);

		// CPPUNIT_ASSERT((*l)[1].second == s2);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_neighborhood);

#endif