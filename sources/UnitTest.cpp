///
/// \file UnitTest.cpp
/// \author *
/// \version *
/// \date *
/// \brief http://www.yolinux.com/TUTORIALS/CppUnit.html
///

#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>


#include "stoppingCriteria/unitTest_criteriaBudget.h"
#include "solution/unitTest_solution.h"
#include "solution/unitTest_solutionArray.h"
#include "solution/unitTest_population.h"
#include "problem/unitTest_OneMax.h"
#include "problem/unitTest_knapsack.h"
#include "problem/unitTest_magicSequence.h"
#include "optimizationAlgorithm/metaheuristic/operator/mutation/unitTest_flipBit.h"
#include "optimizationAlgorithm/metaheuristic/operator/mutation/unitTest_kBit.h"
#include "problem/unitTest_QAP.h"
#include "optimizationAlgorithm/exhaustiveSearch/unitTest_combinationGenerator.h"
#include "optimizationAlgorithm/exhaustiveSearch/unitTest_backtracking.h"


CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_criteriaBudget);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_solution);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_solutionArray);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_population);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_OneMax);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_knapsack);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_magicSequence);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_QAP);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_combinationGenerator);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_backtraking);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_flipBit);
CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_kBit);

int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    //ofstream xmlFileOut("cppTestResults.xml");
    //XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    //xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}