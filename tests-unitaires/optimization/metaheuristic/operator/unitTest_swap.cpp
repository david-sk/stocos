///
/// @file unitTest_swap.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../../../unitTest.h"

#ifndef UNITTEST_SWAP_H
#define UNITTEST_SWAP_H

#include <memory> // std::shared_ptr std::unique_ptr

#include "optimization/metaheuristic/operator/swap.h"
#include "problem/oneMax.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_swap : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_swap);
    CPPUNIT_TEST(operator());
    CPPUNIT_TEST_SUITE_END();

  public:
    void setUp(void) {
        mt_rand.seed(0);
    }

    void operator()(void) {
        unsigned int N = 50;
        SOL_ONEMAX s1(N);
        for(unsigned int i = 0; i < N; i++) { s1(i, static_cast<int>(i % 2)); }
        SOL_ONEMAX s2(s1);
        Swap<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> swap(mt_rand, 5);
        swap(s1);

        CPPUNIT_ASSERT(!(s1 == s2));
    }

  private:
    std::mt19937 mt_rand;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_swap);

#endif