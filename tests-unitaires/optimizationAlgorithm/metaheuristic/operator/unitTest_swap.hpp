///
/// @file unitTest_swap.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_SWAP_H
#define UNITTEST_SWAP_H

#include <memory>       // std::shared_ptr std::unique_ptr

#include "problem/oneMax.hpp"
#include "solution/solutionArray.hpp"
#include "optimizationAlgorithm/metaheuristic/operator/swap.hpp"

using namespace CppUnit;

class UnitTest_swap : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_swap);
    CPPUNIT_TEST(operator());
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {

    }
    void tearDown(void) {

    }

    void operator()(void) {
	    std::mt19937 mt_rand;
	    mt_rand.seed(0);

        unsigned int N = 50;
        std::shared_ptr<OneMax> oneMax = std::make_shared<OneMax>(N);
        SOL_ONEMAX s1(1, N);
        for(unsigned int i = 0 ; i < N ; i++) {
            s1(i,static_cast<int>(i%2));
        }
        SOL_ONEMAX s2(s1);
        Swap<SOL_ONEMAX, TYPE_FITNESS_ONEMAX, TYPE_CELL_ONEMAX> swap(mt_rand, oneMax, 5);
        swap(s1);

        CPPUNIT_ASSERT(!(s1 == s2));   
    }
    
    private:
};

#endif