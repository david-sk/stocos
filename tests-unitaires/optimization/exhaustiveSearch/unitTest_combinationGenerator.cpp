///
/// @file unitTest_criteriaBudget.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../../unitTest.h"

#ifndef UNITTEST_COMBINATIONGENERATOR_H
#define UNITTEST_COMBINATIONGENERATOR_H

#include "optimization/exhaustiveSearch/combinationGenerator.h"
#include "solutionSelection/solutionSelectionBuilder.h"
#include "problem/oneMax.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solution/solutionArray.h"
#include "stoppingCriteria/stoppingCriteria.h"
#include "solutionSelection/maximization.h"
#include "solutionSelection/minimization.h"
#include "statistic/statistic.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_combinationGenerator : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_combinationGenerator);
	CPPUNIT_TEST(test);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		mt_rand.seed(0);
	}

	void test(void) {
		typedef SolutionArray<unsigned int, bool> TYPESOL;
		// //CPPUNIT_ASSERT(o->operator()(s) == false);


		std::unique_ptr<StoppingCriteria<TYPESOL, unsigned int>> stoppingCriteria =
			std::make_unique<StoppingCriteria<TYPESOL, unsigned int>>();
		std::unique_ptr<Statistic<TYPESOL>> statistic = std::make_unique<Statistic<TYPESOL>>();
		std::shared_ptr<OneMax> oneMax = std::make_shared<OneMax>(100);
		TYPESOL s(4);

		CombinationGenerator<TYPESOL, unsigned int, bool> cg(mt_rand, move(statistic),
															 move(stoppingCriteria), oneMax);
		// cg(s);

		/*const std::unique_ptr<unsigned int []> &u = cg.reset();
		for (unsigned int k = 0; k < 4; k++)
			std::cout<<u[k];
		std::cout<<std::endl;
		do {
			const std::unique_ptr<unsigned int []> &y = cg.step();
			for (unsigned int k = 0; k < 4; k++)
				std::cout<<y[k];
			std::cout<<std::endl;
		} while (cg.stop());*/
	}
  private:
	std::mt19937 mt_rand;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_combinationGenerator);

#endif