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
    //CPPUNIT_TEST(distance_euclidienne);
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
        TravelingSalesmanProblem tsp;
        tsp.loadInstance("instances/TravelingSalesmanProblem/travelingSalesmanProblem-10-1.json");
        unique_ptr<SOL_STP> s1 = tsp.new_solution();

        // cout<<(*s1)<<endl;
        tsp.full_eval((*s1));
        // cout<<(*s1)<<endl;
    }

    /*void distance_euclidienne(void) {
        pair<double, double> A(2.5, 18.2);
        pair<double, double> B(20.2, 2.4);

        TravelingSalesmanProblem tsp;
        double r = tsp.distance_euclidienne(A, B);
        cout<<"**"<<r<<"**"<<endl;
    }*/



    private:

};

#endif