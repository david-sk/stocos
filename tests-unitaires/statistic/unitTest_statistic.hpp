///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef UNITTEST_STATISTIC_H
#define UNITTEST_STATISTIC_H

#include "solution/solution.hpp"
#include "statistic/sensor.hpp"
#include "statistic/sensorNumRound.hpp"
#include "statistic/statistic.hpp"

using namespace CppUnit;
using namespace stocos;

class UnitTest_statistic : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_statistic);
	CPPUNIT_TEST(constructor);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
	}
	void tearDown(void) {
	}

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

#endif