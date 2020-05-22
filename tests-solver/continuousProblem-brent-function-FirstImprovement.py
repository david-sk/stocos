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
# The global minima f(x*) = exp(-200) located at x* = (-10, -10)
#

import json
import subprocess
import math
import numpy as np
import argparse


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('path', type=str,  help='Path stocos executable')
    args = parser.parse_args()

    configuration : dict = {
        "seed": 0,
        "problem": {
            "name": "ContinuousProblem",
            "instance_number": "0",
            "objectif": [
                {
                    "name": "objectif1",
                    "function": "(x + 10)^2 + (y + 10)^2 + exp(-x^2 - y^2)",
                    "variables": [
                        "x", "y"
                    ],
                    "domain" : [
                        [-20,0],
                        [-20,0]
                    ],
                    "solutionSelection": "min"
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
                }
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
        },
        "initial_solution" : {
            "fitness": [
                0
            ],
            "fitnessIsValid": [
                False
            ],
            "solution": [
                0,
                0
            ]
        }
    }
#
    def f(x : float, y : float) -> float:
        return (x + 10)**2 + (y + 10)**2 + math.exp(-x**2 - y**2)

    result = subprocess.run([args.path, "-j", json.dumps(configuration)], capture_output=True)
    result_data = json.loads(result.stdout)

    result_stocos = result_data["Solution"]["fitness"][0]
    restat_f = np.around(f(result_data["Solution"]["solution"][0], result_data["Solution"]["solution"][1]))
    objectif_fitness = math.exp(-200)

    assert abs(result_stocos - objectif_fitness) < 0.01
    assert abs(result_stocos - restat_f) < 0.01
    exit(result.returncode)