///
/// @file unitTest_oneMax.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_EVALONEMAX_H
#define UNITTEST_EVALONEMAX_H

#include <string>

#include "solution/solutionArray.hpp"

#include "problem/oneMax.hpp"

using namespace CppUnit;

class UnitTest_OneMax : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_OneMax);
    CPPUNIT_TEST(evaluation);
    CPPUNIT_TEST(loadInstance);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void evaluation(void) {
        unsigned int n = 10, fitness = 0;
        OneMax eOneMax(n);
        SolutionArray<unsigned int, bool> s(1, n);
        for (unsigned int i = 0 ; i < n ; i++) {
            if (i % 2) {
                s(i, 0);
            } else {
                s(i, 1);
                fitness++;
            }
        }
        
        eOneMax.evaluation(s);
        CPPUNIT_ASSERT(s.getFitness() == fitness);
    }

    void loadInstance(void) {
        std::string file = "instances/OneMax/onemax-50.json";
        OneMax eOneMax(file);
    }

    private:
};

#endif