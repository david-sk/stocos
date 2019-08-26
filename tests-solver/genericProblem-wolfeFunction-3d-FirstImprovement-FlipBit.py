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
# @brief http://benchmarkfcns.xyz/benchmarkfcns/wolfefcn.html
# The global minima f(x*) = 0 located at x* = (0, 0, 0)
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
                    "function": "(4/3)*(((x^2 + y^2) - (x * y))^(0.75)) + z",
                    "variables": [
                        "x", "y", "z"
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
                    "budget": 1000,
                },
                "AtomicOperation": {
                    "className": "IntervalReal",
                    "c": 1,
                    "a": -1,
                    "b": 1
                },
                "Selection": "min"
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
    def f(x : float, y : float, z : float) -> float:
        return  (4/3)*( math.pow((( math.pow(x,2) + math.pow(y,2)) - (x * y)),(0.75))) + z

    result = subprocess.run(["build/stocos-Release", "-j", json.dumps(configuration)], capture_output=True)
    result_data = json.loads(result.stdout)

    result_stocos = result_data["Solution"]["fitness"][0]
    restat_f = np.around(f(result_data["Solution"]["solution"][0], result_data["Solution"]["solution"][1], result_data["Solution"]["solution"][2]))

    print(result_data)
    print(f(0,0,0))
    print(result_stocos)
    print(restat_f)
    # assert abs(result_stocos - 0) < 0.01
    # assert abs(result_stocos - restat_f) < 0.01
    # exit(result.returncode)