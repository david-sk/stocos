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
# \see : https://en.wikipedia.org/wiki/Ackley_function
# \see : https://en.wikipedia.org/wiki/Test_functions_for_optimization
# \see : https://github.com/kthohr/optim/tree/master/tests
# \see : http://benchmarkfcns.xyz/fcns
#

import json
import subprocess
import math
import numpy as np


if __name__ == '__main__':
    configuration : dict = {
        "seed": 0,
        "problem": {
            "name": "GenericProblem",
            "numInstance": "0",
            "objectif": [
                {
                    "name": "objectif1",
                    "function": "-200 * exp(-0.02 * sqrt(( x^ 2) + (y^ 2)))",
                    "variables": [
                        "x", "y"
                    ],
                    "maximization": False
                }
            ]
        },
        "parameter_id": 0,
        "OptimizationAlgorithm": {
            "0": {
                "className": "FirstImprovement",
                "StoppingCriteria": {
                    "budget": 4000,
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
                "name" : "ackley function",
                "num" : 6
            }
        }
    }
#
    def f(x : float, y : float) -> float:
        return  -200 * math.exp(-0.02 * math.sqrt(( math.pow(x, 2)) + (math.pow(y,2))))

    result = subprocess.run(["build/stocos-Release", "-j", json.dumps(configuration)], capture_output=True)
    result_data = json.loads(result.stdout)

    print(result_data)

    # print(f(0.0, 0.0))
    print(np.around(f(result_data["Solution"]["solution"][0], result_data["Solution"]["solution"][1])))
    # result_data = json.loads(result.stdout)
    # assert (-6.25 - result_data["Solution"]["fitness"][0]) < 0.01
    # exit(result.returncode)