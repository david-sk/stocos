///
/// \file unitTest_knapsack.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_FLIPBIT_H
#define UNITTEST_FLIPBIT_H

#include "../../../../solution/solutionArray.h"
#include "flipBit.h"

using namespace CppUnit;

class UnitTest_flipBit : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_flipBit);
    CPPUNIT_TEST(operator());
    CPPUNIT_TEST(cancelMutations);
    CPPUNIT_TEST(listOfMutations);
    CPPUNIT_TEST(applyMutation);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {

    }
    void tearDown(void) {

    }

    void operator()(void) {
        unsigned int N = 50;
        SolutionArray<int, bool> s(N);
        
        for (unsigned int i = 0 ; i < N ; i++) {
            s(i, 0);
        }

	    std::mt19937 mt_rand;
	    mt_rand.seed(0);

        FlipBit<SolutionArray<int, bool>, bool> flipbit(mt_rand, 0);
        flipbit(s);
    }


    void cancelMutations(void) {
        unsigned int N = 50;
        SolutionArray<int, bool> s1(1, N);
        SolutionArray<int, bool> s2(1, N);

        for (unsigned int i = 0 ; i < N ; i++) {
            s1(i, 0);
            s2(i, 0);
        }

	    std::mt19937 mt_rand;
	    mt_rand.seed(0);
        
        FlipBit<SolutionArray<int, bool>, bool> flipbit(mt_rand, 0);
        flipbit(s1);
        flipbit.cancelMutations(s1);
        CPPUNIT_ASSERT(s1 == s2);   
    }

    void listOfMutations(void) {
        unsigned int N = 50;
        SolutionArray<int, bool> s1(1, N);
	    
        std::mt19937 mt_rand;
	    mt_rand.seed(0);

        FlipBit<SolutionArray<int, bool>, bool> flipbit(mt_rand, 5);
        unique_ptr<vector<pair<unsigned int, bool>>> mutations = flipbit.listOfMutations(s1);
        
    }

    void applyMutation(void) {
        unsigned int N = 50;
        SolutionArray<int, bool> s1(1, N);
        SolutionArray<int, bool> s2(s1);
	    
        std::mt19937 mt_rand;
	    mt_rand.seed(0);

        FlipBit<SolutionArray<int, bool>, bool> flipbit(mt_rand, 5);
        unique_ptr<vector<pair<unsigned int, bool>>> mutations = flipbit.listOfMutations(s1);
        flipbit.applyMutation(s1, *mutations);

        CPPUNIT_ASSERT(!(s1 == s2));
    }

    private:
};

#endif