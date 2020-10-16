///
/// @file unitTest_jobShopProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_JOBSHOPPROBLEM_H
#define UNITTEST_JOBSHOPPROBLEM_H

#include "problem/jobShopProblem.h"
#include "problem/problem.h"
#include "solution/solution.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_jobShopProblem : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_jobShopProblem);
	CPPUNIT_TEST(loadInstance);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
	}
	void tearDown(void) {
	}

	void loadInstance(void) {
		JobShopProblem("instances/JobShopProblem/JobShopProblem-0.json");
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_jobShopProblem);

#endif