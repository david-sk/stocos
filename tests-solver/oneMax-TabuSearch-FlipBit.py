#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

#
# @Author: Jxtopher
# @License: 
# @Date: 2019-08-24
# @Purpose: tests-solver
# @copyright CC-BY-NC-SA
#

import json
import subprocess

if __name__ == '__main__':
    OneMax : dict = {
        "seed": 0,
        "problem": {
            "name": "OneMax",
            "instance": "instances/OneMax/onemax-10.json"
        },
        "parameter_id": 0,
        "OptimizationAlgorithm": {
            "0": {
                "className":"TabuSearch",
                "StoppingCriteria": {
                    "budget": 100000,
                    "fitnessObjectif": 10
                },
                "AtomicOperation": {
                    "className": "FlipBit",
                    "c": 1
                },
                "Selection": "max",
                "sizeOfTabuList": 7
            }
        },            
        "Statistic": {
            "recording":"stdout",
            "sensorNumRound" : False,
            "sensorSolution" : False,
            "sensorStopwatch" : False,
            "sensorFinal" : {
                "name" : "oneMax",
                "num" : 6
            }
        }
    }
    print(OneMax)
    result = subprocess.run(["build/stocos-Release", "-j", json.dumps(OneMax)], capture_output=True)
    result_data = json.loads(result.stdout)
    assert result_data["Solution"]["fitness"][0] == 10
    exit(result.returncode)