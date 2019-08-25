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
    configuration : dict = {
        "seed": 0,
        "problem": {
            "name": "GenericProblem",
            "numInstance": "0",
            "objectif": [
                {
                    "name": "objectif1",
                    "function": "sin(2 * pi * x) + cos(x / 2 * pi) + 1.0",
                    "variables": [
                        "x"
                    ],
                    "maximization": True
                }
            ]
        },
        "parameter_id": 0,
        "OptimizationAlgorithm": {
            "0": {
                "className": "FirstImprovement",
                "StoppingCriteria": {
                    "budget": 1000,
                },
                "AtomicOperation": {
                    "className": "IntervalReal",
                    "c": 1,
                    "a": -1,
                    "b": 1
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

    result = subprocess.run(["build/stocos-Release", "-j", json.dumps(configuration)], capture_output=True)
    result_data = json.loads(result.stdout)
    assert (2.9282 - result_data["Solution"]["fitness"][0]) < 0.01
    exit(result.returncode)