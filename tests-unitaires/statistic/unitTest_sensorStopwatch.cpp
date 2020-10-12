///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_SENSORSTOPWATCH_H
#define UNITTEST_SENSORSTOPWATCH_H

#include <unistd.h>

#include "statistic/sensorStopwatch.cpp"

using namespace CppUnit;
using namespace stocos;

class UnitTest_sensorStopwatch : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_sensorStopwatch);
	CPPUNIT_TEST(diff_microseconds);
	CPPUNIT_TEST_SUITE_END();

  public:
	void diff_microseconds(void) {
		unsigned int microseconds = 1;
		sensorStopwatch.start();
		usleep(microseconds);
		sensorStopwatch.stop();
		CPPUNIT_ASSERT(sensorStopwatch.diff_microseconds() > 0);
		CPPUNIT_ASSERT(sensorStopwatch.diff_microseconds() < 500);
	}

  private:
	SensorStopwatch<unsigned int> sensorStopwatch;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_sensorStopwatch);

#endif