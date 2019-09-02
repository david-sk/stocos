///
/// @file unitTest_travelingSalesmanProblem.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef UNITTEST_EVALTRAVELINGSALESMANPROBLEM__H
#define UNITTEST_EVALTRAVELINGSALESMANPROBLEM__H

using namespace CppUnit;

#include <fstream>		// ifstream
#include <string>
#include "problem/travelingSalesmanProblem.hpp"

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
		if (!std::ifstream(std::string("instances/TravelingSalesmanProblem/TSP-10-1.json.gz").c_str()).good()) {
			throw std::runtime_error(std::string{} + __FILE__ + ":" + std::to_string(__LINE__) + " [-] the file does not exist");
		}
        TravelingSalesmanProblem tsp(std::string("instances/TravelingSalesmanProblem/TSP-10-1.json.gz"));
    }

    void full_eval(void) {
        TravelingSalesmanProblem tsp(std::string("instances/TravelingSalesmanProblem/TSP-10-1.json.gz"));
        std::unique_ptr<SOL_STP> s1 = tsp.new_solution();

        // std::cout<<(*s1)<<std::endl;
        tsp.full_eval((*s1));
        // std::cout<<(*s1)<<std::endl;
    }

    /*void distance_euclidienne(void) {
        pair<double, double> A(2.5, 18.2);
        pair<double, double> B(20.2, 2.4);

        TravelingSalesmanProblem tsp;
        double r = tsp.distance_euclidienne(A, B);
        std::cout<<"**"<<r<<"**"<<std::endl;
    }*/



    private:

};

#endif