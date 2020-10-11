///
/// @file unitTest_neighborhood.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef UNITTEST_INTERVALREAL_H
#define UNITTEST_INTERVALREAL_H

#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/atomicOperation.h"
#include "optimization/metaheuristic/operator/mutation/intervalReal.h"
#include "problem/oneMax.h"
#include "solution/solutionArray.h"

using namespace CppUnit;

class UnitTest_intervalReal : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_intervalReal);
	// CPPUNIT_TEST(listOfMutations);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
	}
	void tearDown(void) {
	}

  private:
};

#endif