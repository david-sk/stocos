///
/// \file backtracking.h
/// \author Jxtopher
/// \version 1
/// \date 2019
/// \brief *
///

#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <iostream>

#include "../../solution/solutionArray.h"
#include "../optimizationAlgorithm.h"

using namespace std;

template <typename SOL, typename TYPE_CELL>
class Backtraking : public OptimizationAlgorithm<SOL, TYPE_CELL> {
   public:
    Backtraking(std::mt19937 &mt_rand, 
                Statistic<SOL> &statistic, 
				StoppingCriteria<SOL> &stoppingCriteria,
                Problem<SOL, TYPE_CELL> &problem, 
                const unsigned int nbDigit, 
				const unsigned int len_string)
        		: OptimizationAlgorithm<SOL, TYPE_CELL>(mt_rand, statistic, stoppingCriteria, problem),
          		_nbDigit(nbDigit),
                _len_string(len_string) {
                nbCall = 0;
                string = unique_ptr<unsigned int[]>(new unsigned int[_len_string]);
    }

    virtual ~Backtraking() {}



    void operator()(SOL &s) {
        //
    }



	void recursive(unsigned int currentCell) {
		//current_sol.print();
		if (_len_string == currentCell) {
            // for(unsigned int j = 0 ; j < _len_string ; j++)
            //     cout<<string[j];
            // cout<<endl;
			//cout<<"Wine : ";
			//current_sol.print();
		} else {
			unsigned int i = 0;
			while(i < _nbDigit) {
				string[currentCell] = i;

				//Verification des contraites
				//if (filtering(current_sol, currentCell + 1)) {
                //if(this-> _problem.filtering(string)) {
					// Descendre dans l'arbre (parcourt en profondeur)
					recursive(currentCell + 1);
				//}
				i++;
			}
		}
	}

   private:
    const unsigned int _nbDigit;
    const unsigned int _len_string;

    unsigned int nbCall;
    unique_ptr<unsigned int[]> string;

    const vector<unsigned int> _bijection;
};

#endif