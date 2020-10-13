///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_STATISTIC_H
#define UNITTEST_STATISTIC_H

#include "solution/solution.h"
#include "statistic/sensor.h"
#include "statistic/sensorNumRound.h"
#include "statistic/statistic.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_statistic : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_statistic);
	CPPUNIT_TEST(constructor);
	CPPUNIT_TEST_SUITE_END();

  public:
	void constructor(void) {
		Solution<int> s;
		Sensor<Solution<int>>* sensorNumRound = new SensorNumRound<Solution<int>>();
		Statistic<Solution<int>> statistic(true);
		statistic.addSensor(sensorNumRound);
		statistic(s);
		Json::Value result = statistic.asJson(s);
		CPPUNIT_ASSERT(result["round"].asInt() == 2);
	}
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_statistic);

#endif