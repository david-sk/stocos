///
/// \file combinationGenerator.h
/// \author Jxtopher
/// \version 1
/// \date 2019
/// \brief *
///

#ifndef COMBINATIONGENERATOR_H
#define COMBINATIONGENERATOR_H


#include <iostream>

#include "../../solution/solutionArray.h"
#include "../optimizationAlgorithm.h"

using namespace std;

template<class SOL>
class CombinationGenerator : public OptimizationAlgorithm<SOL> {
  public:
	CombinationGenerator(std::mt19937 &mt_rand,
						 Statistic<SOL> &statistic,
						 StoppingCriteria<SOL> &stoppingCriteria,
						 Problem<SOL> &problem,
						 const unsigned int nbDigit,
						 const unsigned int len_string) :
						 OptimizationAlgorithm<SOL>(mt_rand, statistic, stoppingCriteria, problem),
						_nbDigit(nbDigit),
						_len_string(len_string) {
		nbCall = 0;
		string = unique_ptr<unsigned int []>(new unsigned int[_len_string]);
	}
	
	virtual ~CombinationGenerator() {

	}

	const unique_ptr<unsigned int []> & reset() {
		for (unsigned int j = 0; j < _len_string; j++)
			string[j] = 0;

		x = false;
		i = 0;

		while (string[i] == (_nbDigit - 1)) {
			i++;
			x = true;
		}

		return string;
	}

	const unique_ptr<unsigned int []> & step() {
		string[i]++;

		if (x) {
			for (unsigned int j = 0; j < i; j++)
				string[j] = 0;
			i = 0;
		}

		while (string[i] == (_nbDigit - 1)) {
			i++;
			x = true;
		}
		return string;
	}

	bool stop() {
		return i < (_len_string);
	}

	

	void operator()(SOL &s) {
        reset();
		
        do {
            step();
			
        } while (stop());
	}

	/*void operator()(const unsigned int nbDigit, unsigned int len_string, void (*f)(unsigned int, unsigned int *, unsigned int)) {
		unsigned int nbCall = 0;
		unsigned int *string = new unsigned int[len_string];

		for (unsigned int i = 0; i < len_string; i++)
			string[i] = 0;

		bool x = false;
		unsigned int i = 0;

		f(nbCall++, string, len_string);

		while (string[i] == (nbDigit - 1)) {
			i++;
			x = true;
		}

		while (i < (len_string)) {
			string[i]++;

			if (x) {
				for (unsigned int j = 0; j < i; j++)
					string[j] = 0;
				i = 0;
			}

			f(nbCall++, string, len_string);

			while (string[i] == (nbDigit - 1)) {
				i++;
				x = true;
			}
		}

		delete[] string;
	}

	static void f(unsigned int nbCall, unsigned int *string, unsigned int size) {
		unsigned int c[28] = {324,540,598,2537,3240,5104,540,598,2537,5104,1508,1056,1152,38,1131,1152,3182,1131,3182};
		unsigned int s = 0;

		for (unsigned int i = 0; i < size; i++)
			s += c[i] * string[i];

		if (s == 9552) {
		std::cout << nbCall << " "<< s << " ";

		for (unsigned int i = 0; i < size; i++)
			std::cout << c[i] * string[i] << " ";

		std::cout << std::endl;
		
		}
	}*/
	private:
		const unsigned int _nbDigit;
		const unsigned int _len_string;

		unsigned int nbCall;
		unique_ptr<unsigned int []> string;

		bool x;
		unsigned int i;

		const vector<unsigned int> _bijection;
};

#endif

/*int main() {
	CombinationGenerator cg;
	cg(2, 28, CombinationGenerator::f);
}*/
