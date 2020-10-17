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
                    "function": "sin(2 * pi * x) + cos(x / 2 * pi) + 1.0",
                    "variables": [
                        "x"
                    ],
                    "domain" : [
                        [-64,64],
                    ],
                    "solutionSelection": "max"
                }
            ]
        },
        "parameter_id": 0,
        "Optimization": {
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
                "name" : "eq2",
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
                64
            ]
        }
    }

    result = subprocess.run([args.path, "-j", json.dumps(configuration)], capture_output=True)
    result_data = json.loads(result.stdout)
    assert (2.9282 - result_data["Solution"]["fitness"][0]) < 0.01
    exit(result.returncode)