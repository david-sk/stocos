///
/// \file unitTest_criteriaBudget.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_SOLUTION_H
#define UNITTEST_SOLUTION_H

using namespace CppUnit;

#include "solution.h"

class UnitTest_solution : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_solution);
    CPPUNIT_TEST(test_numberOfObjective);
    CPPUNIT_TEST(test_fitness);
    CPPUNIT_TEST(test_fitnessIsValid);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void test_numberOfObjective(void) {
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

    void test_fitness(void) {
        Solution<double> s1;
        s1.setFitness(32);
        CPPUNIT_ASSERT(s1.getFitness() == 32);

        Solution<double> s2(5);
        for (unsigned int i = 0 ; i < 5 ; i++)
            s2.setFitness(i, 21*i);
        
        for (unsigned int i = 0 ; i < 5 ; i++)
            CPPUNIT_ASSERT(s2.getFitness(i) == 21*i);
            

        Solution<double> s3(s2);
        for (unsigned int i = 0 ; i < 5 ; i++)
            CPPUNIT_ASSERT(s3.getFitness(i) == 21*i);
            

        Solution<double> s4;
        Solution<double> s5(2);
        for (unsigned int i = 0 ; i < 2 ; i++)
            s5.setFitness(i, 21*i);
        s4 = s5;
        for (unsigned int i = 0 ; i < 2 ; i++) {
            CPPUNIT_ASSERT(s4.getFitness(i) == 21*i);
        }

        Solution<double> s6;
            
    }

    void test_fitnessIsValid(void) {
        Solution<double> s1;
        CPPUNIT_ASSERT(s1.fitnessIsValid() == false);
        s1.setFitness(32);
        CPPUNIT_ASSERT(s1.fitnessIsValid() == true);
    }

    private:

};

#endif