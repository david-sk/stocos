///
/// @file criteria.h
/// @author Jxtopher
/// @version 1
/// @copyright CC-BY-NC-SA
/// @date 2018-10
/// @brief 
///

#ifndef STATISTIC_H
#define STATISTIC_H

#include <iostream>
#include <string>
#include <fstream>

#include "sensor.h"



template<class SOL>
class Statistic {
    public:
    Statistic() : _standardOutput(false) {

    }

    Statistic(bool standardOutput)  : _standardOutput(standardOutput) {
 
    }

    Statistic(std::string namefile)  : 
        _namefile(namefile), 
        _standardOutput(false) {
        outFile.open (_namefile);
    }

    virtual ~Statistic() {
        std::stringstream ss;
        if (_standardOutput || !_namefile.empty()) {
            for(unsigned int i = 0 ; i < sensor.size() ; i++) {
                sensor[i]->finish(ss);
                ss<<" ";
            }
        }
        
        if (_standardOutput)
            std::cout<<ss.str()<<std::endl;
        if(!_namefile.empty()) {
            outFile<<ss.str()<<std::endl;
        }
        
        for(unsigned int i = 0 ; i < sensor.size() ; i++)
            delete sensor[i];

        sensor.clear();
    }

    void operator()(const SOL &s) {
        std::stringstream ss;
        if (_standardOutput || !_namefile.empty()) {
            for(unsigned int i = 0 ; i < sensor.size() ; i++) {
                sensor[i]->operator()(ss, s);
                ss<<" ";
            }
        }
        
        if (_standardOutput)
            std::cout<<ss.str()<<std::endl;
        else if(!_namefile.empty()) {
            outFile<<ss.str()<<std::endl;
        }
    }

    void addSensor(Sensor<SOL> *s) {
        sensor.push_back(s);
    }

    void setPrint(bool standardOutput = false, std::string namefile = "") {
        _namefile = namefile;
        _standardOutput = standardOutput;
    }

    protected:
        std::ofstream outFile;
        std::vector<Sensor<SOL> *> sensor;
        std::string _namefile;
        bool _standardOutput;
};

#endif