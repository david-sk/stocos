///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_CRITERIAS_H
#define UNITTEST_CRITERIAS_H

#include "stoppingCriteria/criteriaBudget.h"
#include "stoppingCriteria/stoppingCriteria.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_criterias : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_criterias);
	CPPUNIT_TEST(constructor);
	CPPUNIT_TEST_SUITE_END();

  public:
	void constructor(void) {
		Fitness<int> s;
		CriteriaBudget<Fitness<int>, unsigned int>* criteriaBudget;
		criteriaBudget = new CriteriaBudget<Fitness<int>, unsigned int>(100);

		StoppingCriteria<Fitness<int>, unsigned int> stoppingCriteria;
		stoppingCriteria.addCriteria(criteriaBudget);
		for(unsigned int i = 0; i < 100; i++) CPPUNIT_ASSERT(stoppingCriteria(s));

		for(unsigned int i = 100; i < 200; i++) CPPUNIT_ASSERT(!stoppingCriteria(s));
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_criterias);

#endif