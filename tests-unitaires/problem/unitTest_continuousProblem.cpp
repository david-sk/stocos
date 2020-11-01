///
/// @file unitTest_oneMax.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_CONTINUOUSPROBLEM_H
#define UNITTEST_CONTINUOUSPROBLEM_H

#include "problem/continuousProblem.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solutionSelection/maximization.h"
#include "solutionSelection/minimization.h"
#include "solutionSelection/solutionSelectionBuilder.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_ContinuousProblem : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_ContinuousProblem);
    CPPUNIT_TEST(evaluation);
    CPPUNIT_TEST(loadInstance);
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp(void) {
    }
    void tearDown(void) {
    }

    void evaluation(void) {
    }

    void loadInstance(void) {
        ContinuousProblem gProblem("instances/ContinuousProblem/test.json");
        std::unique_ptr<SOL_CONTINUOUSPROBLEM> s = gProblem.new_solution();
        for(unsigned int i = 0; i < s->sizeArray(); i++) s->operator()(i, i + (7 * i) + 1);
        gProblem.evaluation(*s);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_ContinuousProblem);

#endif