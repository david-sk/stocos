///
/// @file unitTest_oneMax.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_CONTINUOUSPROBLEM_H
#define UNITTEST_CONTINUOUSPROBLEM_H

#include "solution/solutionArray.hpp"

#include "problem/continuousProblem.hpp"

using namespace CppUnit;

class UnitTest_ContinuousProblem: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_ContinuousProblem);
    CPPUNIT_TEST(full_eval);
    CPPUNIT_TEST(loadInstance);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void full_eval(void) {
    }

    void loadInstance(void) {
        ContinuousProblem gProblem("instances/ContinuousProblem/test.json");
        std::unique_ptr<SOL_CONTINUOUSPROBLEM> s = gProblem.new_solution();
        for (unsigned int i = 0 ; i < s->sizeArray() ; i++) {
            s->operator()(i, i + (7 * i) + 1);
        }
        gProblem.full_eval(*s);
        std::cout<<*s<<std::endl;
    }

    private:
};

#endif