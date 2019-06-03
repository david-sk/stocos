///
/// \file solution.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SOLUTION_H
#define SOLUTION_H

#include <cassert>
#include <cstring>
#include <cstdio>
#include <string>
#include <memory>

#include "../macro.h"

using namespace std;

template<typename TYPE_FITNESS>
class Solution {
	public:
		Solution(const Solution & s) :
			_numberOfObjective(s._numberOfObjective) {
			DEBUG_TRACE("Constructeur de copie Solution");
			assert(0 < _numberOfObjective);
			_fitness = make_unique<TYPE_FITNESS []>(_numberOfObjective);
			_fitnessIsValid = make_unique<bool []>(_numberOfObjective);
			for(unsigned int i = 0 ; i < _numberOfObjective ; i++) {
				_fitness[i] = s._fitness[i];
				_fitnessIsValid[i] = s._fitnessIsValid[i];
			}
		}
		
		Solution(): 
			_numberOfObjective(1) {
			DEBUG_TRACE("Creation Solution");
			_fitness = make_unique<TYPE_FITNESS []>(_numberOfObjective);
			_fitnessIsValid = make_unique<bool []>(_numberOfObjective);
			for(unsigned int i = 0 ; i < _numberOfObjective ; i++)
				_fitnessIsValid[i] = false;
		}

		Solution(const unsigned int numberOfObjective): 
			_numberOfObjective(numberOfObjective) {
			DEBUG_TRACE("Creation Solution");
			assert(0 < _numberOfObjective);
			_fitness = make_unique<TYPE_FITNESS []>(_numberOfObjective);
			_fitnessIsValid = make_unique<bool []>(_numberOfObjective);
			for(unsigned int i = 0 ; i < _numberOfObjective ; i++)
				_fitnessIsValid[i] = false;
		}

		// Deserialization
		Solution(const unsigned char *deserialization) {
			DEBUG_TRACE("Constructeur de deserialization");
			unsigned long long size = 0;
			const unsigned char *cursorData = deserialization;

			memcpy(static_cast<void *>(&size), static_cast<const void *>(cursorData), sizeof(unsigned long long));
			cursorData += sizeof(unsigned long long);
			
			memcpy(static_cast<void *>(&_numberOfObjective), static_cast<const void *>(cursorData), sizeof(unsigned int));
			cursorData += sizeof(unsigned int);
			
			//std::cout<<size<<std::endl;
			//std::cout<<_numberOfObjective<<std::endl;

			_fitness = new TYPE_FITNESS[_numberOfObjective];
			for (unsigned int i = 0 ; i < _numberOfObjective ; i++) {
				memcpy(static_cast<void *>(&_fitness[i]), static_cast<const void *>(cursorData), sizeof(TYPE_FITNESS));
				cursorData += sizeof(TYPE_FITNESS);
			}

			//_fitnessIsValid = new bool[_numberOfObjective];
			_fitnessIsValid = unique_ptr<bool []>(new bool[_numberOfObjective]);
			for (unsigned int i = 0 ; i < _numberOfObjective ; i++) {
				memcpy( static_cast<void *>(&_fitnessIsValid[i]), static_cast<const void *>(cursorData), sizeof(bool));
				cursorData += sizeof(bool);
			}
			
			//for (unsigned int i = 0 ; i < 62 ; i++) {
			//	printf("%X ", deserialization[i]);
			//}
		}
		
		Solution & operator=(const Solution & s) {
			if (_numberOfObjective != s._numberOfObjective) {
				//this->~Solution();
				_numberOfObjective = s._numberOfObjective;
				//_fitness = new TYPE_FITNESS[_numberOfObjective];
				_fitness = unique_ptr<TYPE_FITNESS []>(new TYPE_FITNESS[_numberOfObjective]);
				//_fitnessIsValid = new bool[_numberOfObjective];
				_fitnessIsValid = unique_ptr<bool []>(new bool[_numberOfObjective]);
				for(unsigned int i = 0 ; i < _numberOfObjective ; i++)
					_fitnessIsValid[i] = false;
			} 
			
			for(unsigned int i = 0 ; i < _numberOfObjective ; i++) {
				_fitness[i] = s._fitness[i];
				_fitnessIsValid[i] = s._fitnessIsValid[i];
			}
			return *this;
		}
		
		~Solution() {
			DEBUG_TRACE("Delete Solution");
			//delete [] _fitness;
			//delete [] _fitnessIsValid;
		}

		// Serialization
		// Return : unsigned char
		// Total size - numberOfObjective - Fitness * numberOfObjective - FitnessIsValid * numberOfObjective
		unsigned char *serialization() {
			unsigned long long size = sizeof(unsigned long long) + sizeof(unsigned int) + (_numberOfObjective * sizeof(TYPE_FITNESS)) + (_numberOfObjective * sizeof(bool));
			unsigned char *data = new unsigned char[size];
			unsigned char *cursorData = data;

			//memset(data, 'A',  size);
			
			memcpy(static_cast<void *>(cursorData), static_cast<void *>(&size), sizeof(unsigned long long));
			cursorData += sizeof(unsigned long long);
			
			memcpy(static_cast<void *>(cursorData), static_cast<void *>(&_numberOfObjective), sizeof(unsigned int));
			cursorData += sizeof(unsigned int);

			for (unsigned int i = 0 ; i < _numberOfObjective ; i++) {
				memcpy(static_cast<void *>(cursorData), static_cast<void *>(&_fitness[i]), sizeof(TYPE_FITNESS));
				cursorData += sizeof(TYPE_FITNESS);
			}
			
			for (unsigned int i = 0 ; i < _numberOfObjective ; i++) {
				memcpy(static_cast<void *>(cursorData), static_cast<void *>(&_fitnessIsValid[i]), sizeof(bool));
				cursorData += sizeof(bool);
			}

			//std::cout<<size<<std::endl;

			//for (unsigned int i = 0 ; i < size ; i++) {
			//	printf("%X ", data[i]);
			//}
			//std::cout<<std::endl;
			return data;
		}


		bool fitnessIsValid(unsigned int numObjectif) const {
			assert(numObjectif < _numberOfObjective);
			return _fitnessIsValid[numObjectif];	
		}

		bool fitnessIsValid() const {
			unsigned int numObjectif = 0;
			assert(numObjectif < _numberOfObjective);
			return _fitnessIsValid[numObjectif];	
		}
		
		void setFitness(unsigned int numObjectif, TYPE_FITNESS value) {
			assert(numObjectif < _numberOfObjective);
			_fitness[numObjectif] = value;
			_fitnessIsValid[numObjectif] = true;
		}

		void setFitness(TYPE_FITNESS value) {
			unsigned int numObjectif = 0;
			assert(numObjectif < _numberOfObjective);
			_fitness[numObjectif] = value;
			_fitnessIsValid[numObjectif] = true;
		}
		
		TYPE_FITNESS getFitness() const {
			unsigned int numObjectif = 0;
			assert(numObjectif < _numberOfObjective);
			return _fitness[numObjectif];
		}

		TYPE_FITNESS getFitness(unsigned int numObjectif) const {
			assert(numObjectif < _numberOfObjective);
			return _fitness[numObjectif];
		}

		unsigned int numberOfObjective() const {
			return _numberOfObjective;
		}
		
		friend std::ostream & operator << (std::ostream &out, const Solution<TYPE_FITNESS> &s) {
			for (unsigned int i = 0 ; i < s.numberOfObjective() ; i++)
				out << s.getFitness(i);
			return out;
		}
		
	protected:
		unsigned int _numberOfObjective;
		unique_ptr<TYPE_FITNESS []> _fitness;
		unique_ptr<bool []>_fitnessIsValid;
};

#endif