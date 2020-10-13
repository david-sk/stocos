///
/// @file unitTest_domain.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_DOMAIN_H
#define UNITTEST_DOMAIN_H

#include <memory>
#include <unordered_set>

#include "solution/domain.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_domain : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_domain);
	CPPUNIT_TEST(in_domain);
	CPPUNIT_TEST(remove_element);
	CPPUNIT_TEST(get_size_domain);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
	}
	void tearDown(void) {
	}

	void in_domain(void) {
		Domain<int> dom(2, 25);
		CPPUNIT_ASSERT(dom.in_domain(5, 1) == false);
		CPPUNIT_ASSERT(dom.in_domain(5, 2) == true);
		CPPUNIT_ASSERT(dom.in_domain(5, 22) == true);
		CPPUNIT_ASSERT(dom.in_domain(5, 25) == false);
		CPPUNIT_ASSERT(dom.in_domain(5, 36) == false);
	}

	void remove_element(void) {
		Domain<int> dom(2, 25);
		dom.remove_element(5, 4);
		CPPUNIT_ASSERT(dom.in_domain(5, 4) == false);
	}

	void add_element(void) {
		Domain<int> dom(2, 25);
		dom.add_element(5, 55);
		CPPUNIT_ASSERT(dom.in_domain(5, 55) == true);
		CPPUNIT_ASSERT(dom.in_domain(2, 55) == false);
	}

	void get_size_domain(void) {
		Domain<int> dom(2, 25);
		CPPUNIT_ASSERT(dom.get_size_domain(5) == 23);
	}

  private:
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_domain);

#endif