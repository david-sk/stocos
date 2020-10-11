///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef UNITTEST_SENSORSTOPWATCH_H
#define UNITTEST_SENSORSTOPWATCH_H

#include "statistic/sensorStopwatch.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_sensorStopwatch : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_sensorStopwatch);
	CPPUNIT_TEST(diff_microseconds);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		sensorStopwatch.start();
	}

	void diff_microseconds(void) {
		sensorStopwatch.stop();
		CPPUNIT_ASSERT(sensorStopwatch.diff_microseconds() != 0);
	}

  private:
	SensorStopwatch<unsigned int> sensorStopwatch;
};

#endif