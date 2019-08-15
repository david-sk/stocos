///
/// @file unitTest_knapsack.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_KBIT_H
#define UNITTEST_KBIT_H

#include "../../../../solution/solutionArray.h"
#include "KBit.h"

using namespace CppUnit;

class UnitTest_kBit : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_kBit);
    CPPUNIT_TEST(operator());
    CPPUNIT_TEST(cancelMutations);
    CPPUNIT_TEST(listOfMutations);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {

    }
    void tearDown(void) {

    }

    void operator()(void) {

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
        KBit<SolutionArray<int, bool>, int, bool> kbit(mt_rand, 20);
        kbit(s1);
        kbit.cancelMutations(s1);
        CPPUNIT_ASSERT(s1 == s2);
    }

    void listOfMutations(void) {
        unsigned int N = 50;
        SolutionArray<int, bool> s1(1, N);
        SolutionArray<int, bool> s2(1, N);
        unsigned int checklist[] = {39,15,1,25,32,22,38,42,29,11,10,36,13,8,4,7,34,48,41,0,17,26,45,31,44,14,37,46,27,6,21,19,9,5,3,33,2,30,16,28,20,43,50,23,18};

	    std::mt19937 mt_rand;
	    mt_rand.seed(10);
        KBit<SolutionArray<int, bool>, int, bool> kbit(mt_rand, 45);
        // std::unique_ptr<vector<unsigned int>> list = kbit.listOfMutations(s1);

        // for (unsigned int i = 0 ; i < list->size() ; i++) {
        //     CPPUNIT_ASSERT((*list)[i] == checklist[i]);
        // }

    }

    private:
};

#endif