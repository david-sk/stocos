///
/// @file UnitTest.cpp
/// @author *
/// @version *
/// @date *
/// @brief http://www.yolinux.com/TUTORIALS/CppUnit.html
///

#define BOOST_LOG_DYN_LINK 0

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <netinet/in.h>

#include "solution/unitTest_domain.hpp"
#include "solution/unitTest_population.hpp"
#include "solution/unitTest_solution.hpp"
#include "solution/unitTest_solutionArray.hpp"
#include "stoppingCriteria/unitTest_criteriaBudget.hpp"

#include "optimization/exhaustiveSearch/unitTest_backtracking.hpp"
#include "optimization/exhaustiveSearch/unitTest_combinationGenerator.hpp"
#include "optimization/metaheuristic/operator/mutation/unitTest_flipBit.hpp"
#include "optimization/metaheuristic/operator/mutation/unitTest_kBit.hpp"
#include "optimization/metaheuristic/operator/mutation/unitTest_neighborhood.hpp"
#include "optimization/metaheuristic/operator/unitTest_shuffle.hpp"
#include "optimization/metaheuristic/operator/unitTest_swap.hpp"

#include "problem/unitTest_QAP.hpp"
#include "problem/unitTest_continuousProblem.hpp"
#include "problem/unitTest_jobShopProblem.hpp"
#include "problem/unitTest_knapsack.hpp"
#include "problem/unitTest_magicSequence.hpp"
#include "problem/unitTest_oneMax.hpp"
#include "problem/unitTest_subsetsum.hpp"
#include "problem/unitTest_travelingSalesmanProblem.hpp"

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_criteriaBudget);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_solution);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_solutionArray);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_domain);

// Algorithm d'optimisation
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_combinationGenerator);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_backtraking);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_flipBit);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_kBit);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_swap);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_shuffle);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_neighborhood);

// Problem
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_population);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_OneMax);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_knapsack);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_magicSequence);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_QAP);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_ContinuousProblem);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_jobShopProblem);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_subsetsum);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_travelingSalesmanProblem);

int main(int argc, char* argv[]) {
	boost::log::core::get()->set_logging_enabled(false);

	// informs test-listener about testresults
	CPPUNIT_NS::TestResult testresult;

	// register listener for collecting the test-results
	CPPUNIT_NS::TestResultCollector collectedresults;
	testresult.addListener(&collectedresults);

	// register listener for per-test progress output
	CPPUNIT_NS::BriefTestProgressListener progress;
	testresult.addListener(&progress);

	// insert test-suite at test-runner by registry
	CPPUNIT_NS::TestRunner testrunner;
	testrunner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testresult);

	// output results in compiler-format
	CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	compileroutputter.write();

	// Output XML for Jenkins CPPunit plugin
	// ofstream xmlFileOut("cppTestResults.xml");
	// XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	// xmlOut.write();

	// return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;
}
