///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef UNITTEST_CRITERIAS_H
#define UNITTEST_CRITERIAS_H

#include "solution/solution.hpp"
#include "stoppingCriteria/criteriaBudget.hpp"
#include "stoppingCriteria/stoppingCriterias.hpp"

using namespace CppUnit;
using namespace stocos;

class UnitTest_criterias : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_criterias);
	CPPUNIT_TEST(constructor);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {}
	void tearDown(void) {  }

	void constructor(void) {
		Solution<int> s;
        CriteriaBudget<Solution<int>, unsigned int>* criteriaBudget;
        criteriaBudget = new CriteriaBudget<Solution<int>, unsigned int>(100);
        

		StoppingCriterias<Solution<int>, unsigned int> stoppingCriterias;
		stoppingCriterias.addCriteria(criteriaBudget);
		for(unsigned int i = 0; i < 100; i++)
			CPPUNIT_ASSERT(stoppingCriterias(s));
		
		for(unsigned int i = 100; i < 200; i++) 
			CPPUNIT_ASSERT(!stoppingCriterias(s));
	}
};

#endif