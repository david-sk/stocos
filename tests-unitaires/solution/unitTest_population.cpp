///
/// @file unitTest_population.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief
///
#include "../unitTest.h"

#ifndef UNITTEST_POPULATION_H
#define UNITTEST_POPULATION_H

#include "solution/population.h"
#include "solution/solution.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_population : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_population);
	CPPUNIT_TEST(constructor);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
	}
	void tearDown(void) {
	}

	void constructor(void) {
		Solution<double, bool> s(22);
		Population<Solution<double, bool>> p;
		p.push_back(s);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_population);

#endif