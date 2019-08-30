///
/// @file unitTest_subsetsum.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_SUBSETSUM_H
#define UNITTEST_SUBSETSUM_H

#include "solution/solutionArray.hpp"

#include "problem/subsetSum.hpp"

using namespace CppUnit;

class UnitTest_subsetsum : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_subsetsum);
    CPPUNIT_TEST(loadInstance);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }


    void loadInstance(void) {
        Subsetsum sss("instances/SubSetSum/SubSetSum-5.json");
    }


    private:
};

#endif