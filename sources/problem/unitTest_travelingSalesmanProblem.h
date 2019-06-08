///
/// \file unitTest_evalQAP.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef UNITTEST_EVALTRAVELINGSALESMANPROBLEM__H
#define UNITTEST_EVALTRAVELINGSALESMANPROBLEM__H

using namespace CppUnit;

#include "travelingSalesmanProblem.h"

class UnitTest_travelingSalesmanProblem : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(UnitTest_travelingSalesmanProblem);
    CPPUNIT_TEST(loadInstance);
    CPPUNIT_TEST(full_eval);
    CPPUNIT_TEST_SUITE_END();

    public:

    void setUp(void) {
    }
    void tearDown(void) {
    }

    void loadInstance(void) {
        TravelingSalesmanProblem tsp;
        tsp.loadInstance("instances/TravelingSalesmanProblem/travelingSalesmanProblem-10-1.json");

    }

    void full_eval(void) {
        
    }



    private:

};

#endif