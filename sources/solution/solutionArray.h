///
/// \file solutionArray.h
/// \author Jxtopher
/// \version 1
/// \copyright CC-BY-NC-SA
/// \date 2018-10
/// \brief 
///

#ifndef SOLUTIONARRAY_H
#define SOLUTIONARRAY_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include "solution.h"

using namespace std;

template<typename TYPE_FITNESS, typename TYPE_CELL>
class SolutionArray : public Solution<TYPE_FITNESS> {
public:
	SolutionArray() : 
	Solution<TYPE_FITNESS>(1),
	_sizeArray(1) {
		DEBUG_TRACE("Creation SolutionArray");
		array = new TYPE_CELL[_sizeArray];
	}

	SolutionArray(const unsigned int sizeArray) : 
	Solution<TYPE_FITNESS>(1),
	_sizeArray(sizeArray) {
		DEBUG_TRACE("Creation SolutionArray");
		array = new TYPE_CELL[sizeArray];
		
	}

	SolutionArray(const unsigned int numberOfObjective, const unsigned int sizeArray) : 
	Solution<TYPE_FITNESS>(numberOfObjective),
	_sizeArray(sizeArray) {
		DEBUG_TRACE("Creation SolutionArray");
		array = new TYPE_CELL[sizeArray];
		
	}
	
	SolutionArray(const SolutionArray & s) :
		Solution<TYPE_FITNESS>(s),
		_sizeArray(s._sizeArray) {
		
		array = new TYPE_CELL[_sizeArray];
		
		for (unsigned int i = 0 ; i < _sizeArray ; i++) {
			array[i] = s.array[i];
		}
	}

	// Deserialization
	SolutionArray(const unsigned char *deserialization) :
		Solution<TYPE_FITNESS>(deserialization) {
			unsigned long long sizeSolution = 0;
			unsigned long long sizeSolutionArray = 0;

			const unsigned char *cursorData = deserialization;
			memcpy(static_cast<void *>(&sizeSolution), static_cast<const void *>(cursorData), sizeof(unsigned long long));
			//std::cout<<"[x] "<<sizeSolution<<std::endl;
			cursorData += sizeSolution;

			memcpy(static_cast<void *>(&sizeSolutionArray), static_cast<const void *>(cursorData), sizeof(unsigned long long));
			cursorData += sizeof(unsigned long long);

			memcpy(static_cast<void *>(&_sizeArray), static_cast<const void *>(cursorData), sizeof(unsigned long long));
			cursorData += sizeof(unsigned int);

			array = new TYPE_CELL[_sizeArray];
			for (unsigned int i = 0 ; i < _sizeArray ; i++) {
				memcpy(static_cast<void *>(&array[i]), static_cast<const void *>(cursorData), sizeof(TYPE_CELL));
				cursorData += sizeof(TYPE_CELL);
			}
			//std::cout<<"[x] "<<sizeSolutionArray<<std::endl;
			
	}

	SolutionArray(const string &solution) : 
		Solution<TYPE_FITNESS>() {
        std::string token;
		std::istringstream ss(solution);
		vector<string> x;

        while(std::getline(ss, token, ':')) {
			x.push_back(token);
        }

		//delete[] this->_fitness;
		//delete[] this->_fitnessIsValid;

		this->_fitness = nullptr;
		this->_fitnessIsValid = nullptr;
		this->_numberOfObjective = 0;

		// fitness
		unsigned int i = 0;
        std::istringstream ssFitness(x[0]);
        while(std::getline(ssFitness, token, ' ')) {
			this->_numberOfObjective++;
			if (this->_fitness == nullptr) {
				//this->_fitness = new TYPE_FITNESS[this->_numberOfObjective];
				this->_fitness = unique_ptr<TYPE_FITNESS []>(new TYPE_FITNESS[this->_numberOfObjective]);
				//this->_fitnessIsValid = new bool[this->_numberOfObjective];
				this->_fitnessIsValid = unique_ptr<bool []>(new bool[this->_numberOfObjective]);
			} else {
				//this->_fitness = static_cast<TYPE_FITNESS *>(realloc (this->_fitness, this->_numberOfObjective * sizeof(TYPE_FITNESS)));
				this->_fitness.reset(static_cast<TYPE_FITNESS *>(realloc(static_cast<void*>(this->_fitness.release()), this->_numberOfObjective * sizeof(TYPE_FITNESS))));
				//this->_fitnessIsValid = static_cast<bool *>(realloc (this->_fitnessIsValid, this->_numberOfObjective * sizeof(bool)));
				this->_fitnessIsValid.reset(static_cast<bool *>(realloc(static_cast<void*>(this->_fitnessIsValid.release()), this->_numberOfObjective * sizeof(bool))));
			}
			std::stringstream convert(token);
			TYPE_FITNESS value;
			convert >> value;
			this->setFitness(i++, value);
        }
		assert(i  == this->numberOfObjective());

		array = nullptr;
		_sizeArray = 0;

		// solution
		i = 0;
        std::istringstream ssSolutionString(x[1]);
        while(std::getline(ssSolutionString, token, ' ')) {
			if (!token.empty()) {
				_sizeArray++;
				if (array == nullptr) {
					array = new TYPE_CELL[_sizeArray];
				} else {
					array = static_cast<TYPE_CELL *>(realloc (array, _sizeArray * sizeof(TYPE_CELL)));
				}
				std::stringstream convert(token);
				TYPE_CELL value;
				convert >> value;
				array[i++] = value;
			}
        }
		
		assert(i  == _sizeArray);
	}
	
	~SolutionArray() {
		DEBUG_TRACE("Delete SolutionArray");
		delete[] array;
	}
	
	SolutionArray & operator=(const SolutionArray & s) {
		Solution<TYPE_FITNESS>::operator=(s);
		if (_sizeArray != s._sizeArray) {
			//this->~SolutionArray();
			_sizeArray = s._sizeArray;
			array = new TYPE_CELL[_sizeArray];
		}
		
		for (unsigned int i = 0 ; i < _sizeArray ; i++) {
			array[i] = s.array[i];
		}
		
		return *this;
	}

	bool operator==(const SolutionArray & s) const {
		if (sizeArray() != s.sizeArray())
			return false;
		else {
			for (unsigned int i = 0 ; i < s.sizeArray() ; i++) {
				if (array[i] != s(i))
					return false;
			}
		}
		return true;
	}
	
	// Serialization
	unsigned char *serialization() {
		DEBUG_TRACE("Serialization");
		unsigned char *data = Solution<TYPE_FITNESS>::serialization();

		unsigned long long sizeSolution;
		memcpy(static_cast<void *>(&sizeSolution), static_cast<void *>(data), sizeof(unsigned long long));

		unsigned long long sizeSolutionArray = sizeof(unsigned long long ) + sizeof(unsigned int) + sizeof(TYPE_CELL) * _sizeArray;
		
		data = static_cast<unsigned char *>(realloc(data, sizeSolution + sizeSolutionArray));
		unsigned char *cursorData = data + sizeSolution;

		//memset(cursorData, 'A',  sizeSolutionArray);
		//std::cout<<"*************"<<std::endl;

		memcpy(static_cast<void *>(cursorData), static_cast<void *>(&sizeSolutionArray), sizeof(unsigned long long));
		cursorData += sizeof(unsigned long long);

		memcpy(static_cast<void *>(cursorData), static_cast<void *>(&_sizeArray), sizeof(unsigned int));
		cursorData += sizeof(unsigned int);

		for (unsigned int i = 0 ; i < _sizeArray ; i++) {
			memcpy(static_cast<void *>(cursorData), static_cast<void *>(&array[i]), sizeof(TYPE_CELL));
			cursorData += sizeof(TYPE_CELL);
		}

		//for (unsigned int i = 0 ; i < sizeSolution + sizeSolutionArray ; i++) {
		//	printf("%X ", data[i]);
		//}

		return data;
	}
	
	void operator()(const unsigned int index, const TYPE_CELL value) {
		assert(index < _sizeArray);
		if (array[index] != value) {
			for (unsigned int i = 0 ; i < this->_numberOfObjective ; i++)
				this->_fitnessIsValid[i] = false;
			array[index] = value;
		}
	}
	
	TYPE_CELL operator()(const unsigned int index) const {
		assert(index < _sizeArray);
		return array[index];
	}
	
	unsigned int sizeArray() const {
		return _sizeArray;
	}
	
	friend std::ostream & operator << (std::ostream &out,  SolutionArray<TYPE_FITNESS, TYPE_CELL> const &s) {
		for (unsigned int i = 0 ; i < s.numberOfObjective() ; i++)
			out << s.getFitness(i)<<" ";
		out <<": ";
		for (unsigned int i = 0 ; i < s.sizeArray() ; i++)
			out<<s(i)<<" ";
		return out;
	}
private:
	TYPE_CELL *array;
	unsigned int _sizeArray;
	
};

#endif