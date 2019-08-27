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
                "className": "FirstImprovement",
                "StoppingCriteria": {
                    "budget": 100,
                    "fitnessObjectif": 10
                },
                "AtomicOperation": {
                    "className": "FlipBit",
                    "c": 1
                },
                "Selection": "max"
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

    ## TEST 1
    result = subprocess.run(["build/stocos-Release", "-j", json.dumps(OneMax)], capture_output=True)
    #print(result)
    result_data = json.loads(result.stdout)
    assert result_data["Solution"]["fitness"][0] == 10

    if result.returncode != 0 :
        exit(result.returncode)


    ## TEST 2
    OneMax["initial_solution"] = {
        "fitness": [
            10
        ],
        "fitnessIsValid": [
            True
        ],
        "solution": [
            True,
            True,
            True,
            True,
            True,
            True,
            True,
            True,
            True,
            True,
        ]
    }
    result = subprocess.run(["build/stocos-Release", "-j", json.dumps(OneMax)], capture_output=True)
    result_data = json.loads(result.stdout)
    assert result_data["round"] == 1
    exit(result.returncode)