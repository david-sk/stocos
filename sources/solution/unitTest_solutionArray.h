///
/// \file unitTest_solutionArray.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_SOLUTIONARRAY_H
#define UNITTEST_SOLUTIONARRAY_H

using namespace CppUnit;

#include "solution.h"
#include "solutionArray.h"

class UnitTest_solutionArray : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_solutionArray);
    CPPUNIT_TEST(sizeArray);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void sizeArray(void) {
        SolutionArray<double, unsigned int> s1(2, 100);
        CPPUNIT_ASSERT(s1.sizeArray() == 100);

        SolutionArray<double, unsigned int> s2(s1);
        CPPUNIT_ASSERT(s2.sizeArray() == 100);

        SolutionArray<double, unsigned int> s3(20, 1000);
        s3 = s1;
        CPPUNIT_ASSERT(s3.sizeArray() == 100);
    }

    private:

};

#endif