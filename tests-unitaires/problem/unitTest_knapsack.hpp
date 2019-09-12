///
/// @file unitTest_knapsack.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_KNAPSACK_H
#define UNITTEST_KNAPSACK_H

#include "solution/solutionArray.hpp"

#include "problem/knapsack.hpp"

using namespace CppUnit;

class UnitTest_knapsack : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_knapsack);
    CPPUNIT_TEST(loadInstance);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void loadInstance(void) {
        Knapsack eknapsack("instances/knapsackProblem/knapsackProblem-5-1.json");
        unsigned int n = eknapsack.sizeArraySolution();
        int fitness = 12;
        SOL_KNAPSACK s(n);
        s(0, 1);
        s(1, 1);
        s(2, 0);
        s(3, 1);
        s(4, 0);
        eknapsack.evaluation(s);
        CPPUNIT_ASSERT(s.getFitness() == fitness);
    }

    private:
};

#endif