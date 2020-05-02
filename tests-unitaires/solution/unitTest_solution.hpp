///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#ifndef UNITTEST_SOLUTION_H
#define UNITTEST_SOLUTION_H

#include "solution/solution.hpp"

using namespace CppUnit;
using namespace stocos;

class UnitTest_solution : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_solution);
	CPPUNIT_TEST(constructor);
	CPPUNIT_TEST(operatorEQ);
	CPPUNIT_TEST(numberOfObjective);
	CPPUNIT_TEST(fitness);
	CPPUNIT_TEST(fitnessIsValid);
	CPPUNIT_TEST(asJson);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {}
	void tearDown(void) {}

	void constructor(void) {
		Solution<double> s1(10);
		for(unsigned int i = 0; i < 10; i++) { s1.setFitness(i); }
		Solution<double> s2(s1);

		for(unsigned int i = 0; i < 10; i++) {
			CPPUNIT_ASSERT(s1.getFitness() == s2.getFitness());
			CPPUNIT_ASSERT(s2.fitnessIsValid() == true);
		}
	}

	void operatorEQ(void) {
		Solution<double> s1(10);
		Solution<double> s2(10);
		s1.setFitness(1);
		s2.setFitness(9);

		s1 = s2;
		CPPUNIT_ASSERT(s1.getFitness() == s2.getFitness());
		CPPUNIT_ASSERT(s2.fitnessIsValid() == true);
	}

	void fitnessIsValid(void) {
		Solution<double> s1;
		CPPUNIT_ASSERT(s1.fitnessIsValid() == false);
		s1.setFitness(32);
		CPPUNIT_ASSERT(s1.fitnessIsValid() == true);
	}

	void fitness(void) {
		Solution<double> s1;
		s1.setFitness(32);
		CPPUNIT_ASSERT(s1.getFitness() == 32);

		Solution<double> s2(5);
		for(unsigned int i = 0; i < 5; i++) s2.setFitness(i, 21 * i);

		for(unsigned int i = 0; i < 5; i++) CPPUNIT_ASSERT(s2.getFitness(i) == 21 * i);

		Solution<double> s3(s2);
		for(unsigned int i = 0; i < 5; i++) CPPUNIT_ASSERT(s3.getFitness(i) == 21 * i);

		Solution<double> s4;
		Solution<double> s5(2);
		for(unsigned int i = 0; i < 2; i++) s5.setFitness(i, 21 * i);
		s4 = s5;
		for(unsigned int i = 0; i < 2; i++) { CPPUNIT_ASSERT(s4.getFitness(i) == 21 * i); }

		Solution<double> s6;
	}

	void numberOfObjective(void) {
		Solution<double> s1;
		CPPUNIT_ASSERT(s1.numberOfObjective() == 1);

		Solution<double> s2(5);
		CPPUNIT_ASSERT(s2.numberOfObjective() == 5);

		Solution<double> s3(s2);
		CPPUNIT_ASSERT(s3.numberOfObjective() == 5);

		Solution<double> s4;
		Solution<double> s5(6);
		s4 = s5;
		CPPUNIT_ASSERT(s4.numberOfObjective() == 6);
		CPPUNIT_ASSERT(s4.numberOfObjective() == s5.numberOfObjective());
	}

	void asJson(void) {
		Solution<double> s1(5);
		for(unsigned int i = 0; i < 5; i++) s1.setFitness(i, 21 * i);

		//--------------
		Solution<double> s2(5);
		s2.loadJson(s1.asJson());
		CPPUNIT_ASSERT(s1.getFitness(2) == s2.getFitness(2));

		//--------------
		Solution<double> s3(5);
		s3.loadJson(Json::writeString(Json::StreamWriterBuilder(), s1.asJson()));
		CPPUNIT_ASSERT(s1.getFitness(2) == s3.getFitness(2));
	}

  private:
};

#endif