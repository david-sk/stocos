///
/// @file unitTest_oneMax.hpp
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief
///

#include "../unitTest.h"

#ifndef UNITTEST_NQUEENSPROBLEM_H
#define UNITTEST_NQUEENSPROBLEM_H

#include <string>

#include "problem/nQueensProblem.h"
#include "problem/problem.h"
#include "solution/solution.h"
#include "solution/solutionArray.h"
#include "solutionSelection/maximization.h"

using namespace CppUnit;
using namespace stocos;

class UnitTest_NQueensProblem : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(UnitTest_NQueensProblem);
	CPPUNIT_TEST(check_diagonal);
	CPPUNIT_TEST(check_line);
	CPPUNIT_TEST(evaluationSubSolution);
	CPPUNIT_TEST(getFitnessObjectif);
	CPPUNIT_TEST(evaluation);
	CPPUNIT_TEST_SUITE_END();

  public:
	void setUp(void) {
		n = 4;
		s_valid = SOL_NQUEENSPROBLEM(n);

		s_valid(0, 1);
		s_valid(1, 3);
		s_valid(2, 0);
		s_valid(3, 2);

		s_invalid = SOL_NQUEENSPROBLEM(n);
		s_invalid(0, 0);
		s_invalid(0, 0);
		s_invalid(0, 0);
		s_invalid(0, 0);

		s_semi_valid = SOL_NQUEENSPROBLEM(n);
		s_semi_valid(0, 0);
		s_semi_valid(1, 3);
		s_semi_valid(2, 3);
		s_semi_valid(3, 2);
	}

	void check_diagonal(void) {
		NQueensProblem eNQueensProblem(n);
		CPPUNIT_ASSERT(eNQueensProblem.check_diagonal(s_valid));
		CPPUNIT_ASSERT(eNQueensProblem.check_diagonal(s_invalid));
	}

	void check_line(void) {
		NQueensProblem eNQueensProblem(n);
		CPPUNIT_ASSERT(eNQueensProblem.check_line(s_valid));
		CPPUNIT_ASSERT(!eNQueensProblem.check_line(s_invalid));
	}

	void evaluation(void) {
		NQueensProblem eNQueensProblem(n);
		eNQueensProblem.evaluation(s_valid);
		CPPUNIT_ASSERT(s_valid.getFitness() == 4);
		eNQueensProblem.evaluation(s_invalid);
		CPPUNIT_ASSERT(s_invalid.getFitness() == 0);
		eNQueensProblem.evaluation(s_semi_valid);
		CPPUNIT_ASSERT(s_semi_valid.getFitness() == 1);
	}

	void evaluationSubSolution(void) {
		NQueensProblem eNQueensProblem(n);
		CPPUNIT_ASSERT(eNQueensProblem.evaluationSubSolution(s_valid));
		CPPUNIT_ASSERT(!eNQueensProblem.evaluationSubSolution(s_invalid));
	}

	void getFitnessObjectif(void) {
		NQueensProblem eNQueensProblem(n);
		CPPUNIT_ASSERT(eNQueensProblem.getFitnessObjectif() == n);
	}

  private:
	unsigned int n;
	SOL_NQUEENSPROBLEM s_valid;
	SOL_NQUEENSPROBLEM s_invalid;
	SOL_NQUEENSPROBLEM s_semi_valid;
};

CPPUNIT_TEST_SUITE_REGISTRATION(UnitTest_NQueensProblem);

#endif