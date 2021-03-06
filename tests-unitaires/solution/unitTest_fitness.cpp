///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///
#include "../unitTest.h"

#ifndef UNITTEST_SOLUTION_H
#define UNITTEST_SOLUTION_H

#include "solution/fitness.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_fitness : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_fitness);
    CPPUNIT_TEST(constructor);
    CPPUNIT_TEST(operatorEQ);
    CPPUNIT_TEST(numberOfObjective);
    CPPUNIT_TEST(fitness);
    CPPUNIT_TEST(fitnessIsValid);
    CPPUNIT_TEST(asJson);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp(void) {
    }
    void tearDown(void) {
    }

    void constructor(void) {
        Fitness<double> s1(10);
        for(unsigned int i = 0; i < 10; i++) { s1.setFitness(i); }
        Fitness<double> s2(s1);

        for(unsigned int i = 0; i < 10; i++) {
            CPPUNIT_ASSERT(s1.getFitness() == s2.getFitness());
            CPPUNIT_ASSERT(s2.fitnessIsValid() == true);
        }
    }

    void operatorEQ(void) {
        Fitness<double> s1(10);
        Fitness<double> s2(10);
        s1.setFitness(1);
        s2.setFitness(9);

        s1 = s2;
        CPPUNIT_ASSERT(s1.getFitness() == s2.getFitness());
        CPPUNIT_ASSERT(s2.fitnessIsValid() == true);
    }

    void fitnessIsValid(void) {
        Fitness<double> s1;
        CPPUNIT_ASSERT(s1.fitnessIsValid() == false);
        s1.setFitness(32);
        CPPUNIT_ASSERT(s1.fitnessIsValid() == true);
    }

    void fitness(void) {
        Fitness<double> s1;
        s1.setFitness(32);
        CPPUNIT_ASSERT(s1.getFitness() == 32);

        Fitness<double> s2(5);
        for(unsigned int i = 0; i < 5; i++) s2.setFitness(i, 21 * i);

        for(unsigned int i = 0; i < 5; i++) CPPUNIT_ASSERT(s2.getFitness(i) == 21 * i);

        Fitness<double> s3(s2);
        for(unsigned int i = 0; i < 5; i++) CPPUNIT_ASSERT(s3.getFitness(i) == 21 * i);

        Fitness<double> s4;
        Fitness<double> s5(2);
        for(unsigned int i = 0; i < 2; i++) s5.setFitness(i, 21 * i);
        s4 = s5;
        for(unsigned int i = 0; i < 2; i++) { CPPUNIT_ASSERT(s4.getFitness(i) == 21 * i); }

        Fitness<double> s6;
    }

    void numberOfObjective(void) {
        Fitness<double> s1;
        CPPUNIT_ASSERT(s1.numberOfObjective() == 1);

        Fitness<double> s2(5);
        CPPUNIT_ASSERT(s2.numberOfObjective() == 5);

        Fitness<double> s3(s2);
        CPPUNIT_ASSERT(s3.numberOfObjective() == 5);

        Fitness<double> s4;
        Fitness<double> s5(6);
        s4 = s5;
        CPPUNIT_ASSERT(s4.numberOfObjective() == 6);
        CPPUNIT_ASSERT(s4.numberOfObjective() == s5.numberOfObjective());
    }

    void asJson(void) {
        Fitness<double> s1(5);
        for(unsigned int i = 0; i < 5; i++) s1.setFitness(i, 21 * i);

        //--------------
        Fitness<double> s2(5);
        s2.loadJson(s1.asJson());
        CPPUNIT_ASSERT(s1.getFitness(2) == s2.getFitness(2));

        //--------------
        Fitness<double> s3(5);
        s3.loadJson(Json::writeString(Json::StreamWriterBuilder(), s1.asJson()));
        CPPUNIT_ASSERT(s1.getFitness(2) == s3.getFitness(2));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_fitness);

#endif