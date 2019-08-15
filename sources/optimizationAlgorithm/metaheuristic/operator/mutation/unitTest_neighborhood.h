///
/// \file unitTest_neighborhood.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_NEIGHBORHOOD_H
#define UNITTEST_NEIGHBORHOOD_H

#include "../../../../solution/solutionArray.h"
#include "../atomicOperation.h"
#include "neighborhood.h"

using namespace CppUnit;

class UnitTest_neighborhood : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_neighborhood);
    CPPUNIT_TEST(listOfMutations);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {

    }
    void tearDown(void) {

    }

    void listOfMutations(void) {
        SolutionArray<int, bool> s1(1, 5);
        s1(0, 1);
        s1(1, 0);
        s1(2, 1);
        s1(3, 0);
        s1(4, 0);
        SolutionArray<int, bool> s2(1, 5);
        s2(0, 1);
        s2(1, 1);
        s2(2, 1);
        s2(3, 0);
        s2(4, 0);

	    std::mt19937 mt_rand;
	    mt_rand.seed(10);
        AtomicOperation<SolutionArray<int, bool>, int, SolutionArray<int, bool>> *atomicOperations = new Neighborhood<SolutionArray<int, bool>, int, SolutionArray<int, bool>>(mt_rand);
        std::unique_ptr<vector<pair<unsigned int, SolutionArray<int, bool>>>> l = atomicOperations->listOfMutations(s1);

        
        CPPUNIT_ASSERT((*l)[1].second == s2);
    }



    private:
};

#endif