///
/// @file unitTest_swap.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_SWAP_H
#define UNITTEST_SWAP_H

#include "../../../solution/solutionArray.h"
#include "swap.h"

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
        SolutionArray<int, int> s1(1, N);
        for(unsigned int i = 0 ; i < N ; i++) {
            s1(i,static_cast<int>(i));
        }
        SolutionArray<int, int> s2(s1);
        Swap<SolutionArray<int, int>, int, int> swap(mt_rand, 5);
        swap(s1);
        swap.cancelMutations(s1);

        CPPUNIT_ASSERT(s1 == s2);   
    }
    
    private:
};

#endif