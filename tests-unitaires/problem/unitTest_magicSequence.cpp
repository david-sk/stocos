///
/// @file unitTest_magicSequence.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_MAGICSEQUENCE_H
#define UNITTEST_MAGICSEQUENCE_H

#include "problem/magicSequence.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solution/solutionArray.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_magicSequence : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_magicSequence);
	CPPUNIT_TEST(test_loadInstance);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
	}
	void tearDown(void) {
	}

	void test_loadInstance(void) {
	}

  private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_magicSequence);

#endif