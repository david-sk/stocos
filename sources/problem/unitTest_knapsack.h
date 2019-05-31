///
/// \file unitTest_knapsack.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_KNAPSACK_H
#define UNITTEST_KNAPSACK_H

#include "../solution/solutionArray.h"

#include "knapsack.h"

using namespace CppUnit;

class UnitTest_knapsack : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_knapsack);
    CPPUNIT_TEST(test_loadInstance);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void test_loadInstance(void) {
        Knapsack<SolutionArray<int, int> > eknapsack("instances/knapsackProblem/knapsackProblem-instance-5-1.json");
        unsigned int n = eknapsack.sizeArraySolution();
        int fitness = 12;
        SolutionArray<int, int> s(n);
        s(0, 1);
        s(1, 1);
        s(2, 0);
        s(3, 1);
        s(4, 0);
        eknapsack.full_eval(s);
        CPPUNIT_ASSERT(s.getFitness() == fitness);
    }
    private:
};

#endif