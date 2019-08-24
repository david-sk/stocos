///
/// @file unitTest_jobShopProblem.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_JOBSHOPPROBLEM_H
#define UNITTEST_JOBSHOPPROBLEM_H

#include "solution/solutionArray.h"

#include "problem/jobShopProblem.h"

using namespace CppUnit;

class UnitTest_jobShopProblem : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_jobShopProblem);
    CPPUNIT_TEST(loadInstance);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void loadInstance(void) {
        JobShopProblem("instances/JobShopProblem/JobShopProblem-0.json");
    }

    private:
};

#endif