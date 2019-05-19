///
/// \file unitTest_criteriaBudget.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_COMBINATIONGENERATOR_H
#define UNITTEST_COMBINATIONGENERATOR_H

using namespace CppUnit;

#include "../../problem/problem.h"
#include "../../solution/solution.h"
#include "combinationGenerator.h"

class UnitTest_combinationGenerator : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(UnitTest_combinationGenerator);
    CPPUNIT_TEST(test);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void test(void) {
        typedef SolutionArray<unsigned int, bool> TYPESOL;
        //CPPUNIT_ASSERT(o->operator()(s) == false);
    
	    std::mt19937 mt_rand;
	    mt_rand.seed(0);

        StoppingCriteria<TYPESOL> stoppingCriteria;
        Statistic<TYPESOL> statistic;
        OneMax<TYPESOL> oneMax;

        CombinationGenerator<TYPESOL> cg(mt_rand, statistic, stoppingCriteria, oneMax, 2, 4);

        //cg();
       
        const unique_ptr<unsigned int []> &u = cg.reset();
        for (unsigned int k = 0; k < 4; k++)
            cout<<u[k];
        cout<<endl;
        do {
            const unique_ptr<unsigned int []> &y = cg.step();
            for (unsigned int k = 0; k < 4; k++)
                cout<<y[k];
            cout<<endl;
        } while (cg.stop());
    }

    private:

};

#endif