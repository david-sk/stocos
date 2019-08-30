///
/// @file unitTest_population.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2019-05
/// @brief 
///

#ifndef UNITTEST_POPULATION_H
#define UNITTEST_POPULATION_H

using namespace CppUnit;

#include "solution/solution.hpp"
#include "solution/solutionArray.hpp"
#include "solution/population.hpp"

class UnitTest_population : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_population);
    CPPUNIT_TEST(constructor);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void constructor(void) {
        SolutionArray<double, bool> s(1, 22);
        Population<SolutionArray<double, bool>> p;
        p.push_back(s);
    }

    private:

};

#endif