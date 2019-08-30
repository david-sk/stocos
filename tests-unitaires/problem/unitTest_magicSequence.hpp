///
/// @file unitTest_magicSequence.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_MAGICSEQUENCE_H
#define UNITTEST_MAGICSEQUENCE_H

#include "solution/solutionArray.hpp"

#include "problem/magicSequence.hpp"

using namespace CppUnit;

class UnitTest_magicSequence : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_magicSequence);
    CPPUNIT_TEST(test_loadInstance);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }


    void test_loadInstance(void) {
    }


    private:
};

#endif