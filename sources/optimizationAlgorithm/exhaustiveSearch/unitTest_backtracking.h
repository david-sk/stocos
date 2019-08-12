///
/// \file unitTest_criteriaBudget.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_BACKTRACKING_H
#define UNITTEST_BACKTRACKING_H

#include <typeinfo>

using namespace CppUnit;

#include "../../problem/problem.h"
#include "../../solution/solution.h"
#include "../../problem/oneMax.h"
#include "backtracking.h"

class UnitTest_backtraking : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_backtraking);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void test(void) {
        using TYPESOL = SolutionArray<unsigned int, bool>;
        //CPPUNIT_ASSERT(o->operator()(s) == false);
    
	    std::mt19937 mt_rand;
	    mt_rand.seed(0);

        unique_ptr<StoppingCriteria<TYPESOL, unsigned int>> stoppingCriteria = make_unique<StoppingCriteria<TYPESOL, unsigned int>>();
        unique_ptr<Statistic<TYPESOL>> statistic = make_unique<Statistic<TYPESOL>>();
        shared_ptr<OneMax> oneMax = make_shared<OneMax>(100);
        TYPESOL s(4);

        Backtraking<TYPESOL, unsigned int, bool> backtraking(mt_rand, move(statistic), move(stoppingCriteria), oneMax, 2, 4);
        backtraking.recursive(0);
    }

    private:

};

#endif