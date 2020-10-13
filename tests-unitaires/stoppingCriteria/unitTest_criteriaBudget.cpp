///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_CRITERIABUDGET_H
#define UNITTEST_CRITERIABUDGET_H

#include "solution/solution.h"
#include "stoppingCriteria/criteriaBudget.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_criteriaBudget : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_criteriaBudget);
	CPPUNIT_TEST(constructor);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		o = new CriteriaBudget<Solution<int>, unsigned int>(1000);
	}
	void tearDown(void) {
		delete o;
	}

	void constructor(void) {
		Solution<int> s;
		for(unsigned int i = 0; i < 200; i++) { o->operator()(s); }

		CPPUNIT_ASSERT(o->getConsumedBudget() == 200);
		CPPUNIT_ASSERT(o->operator()(s) == true);
		CPPUNIT_ASSERT(o->getConsumedBudget() == 201);

		for(unsigned int i = 0; i < 1200; i++) { o->operator()(s); }

		CPPUNIT_ASSERT(o->operator()(s) == false);

		o->resetConsumedBudget();

		for(unsigned int i = 0; i < 999; i++) { o->operator()(s); }

		CPPUNIT_ASSERT(o->operator()(s) == true);
		CPPUNIT_ASSERT(o->operator()(s) == false);
	}

  private:
	CriteriaBudget<Solution<int>, unsigned int>* o;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_criteriaBudget);
#endif