///
/// \file unitTest_evalQAP.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_EVALONEMAX_H
#define UNITTEST_EVALONEMAX_H

#include "../solution/solutionArray.h"

#include "oneMax.h"

using namespace CppUnit;

class UnitTest_OneMax : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_OneMax);
    CPPUNIT_TEST(test_full);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void test_full(void) {
        unsigned int n = 10, fitness = 0;
        SolutionArray<unsigned int, bool> s(1, n);
        for (unsigned int i = 0 ; i < n ; i++) {
            if (i % 2)
                s(i, 0);
            else {
                s(i, 1);
                fitness++;
            }
        }

        OneMax eOneMax;

        eOneMax.full_eval(s);

        CPPUNIT_ASSERT(s.getFitness() == fitness);
    }

    private:
};

#endif