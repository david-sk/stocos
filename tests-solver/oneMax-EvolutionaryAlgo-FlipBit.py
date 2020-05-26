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

    OneMax : dict = {
        "seed": 0,
        "problem": {
            "name": "OneMax",
            "instance": "instances/OneMax/onemax-10.json"
        },
        "parameter_id": 0,
        "OptimizationAlgorithm": {
            "0": {
                "className":"EvolutionaryAlgorithm",
                "StoppingCriterias": {
                    "budget": 100,
                    "fitnessObjectif": 10
                },
                "AtomicOperation": {
                    "className": "FlipBit",
                    "c": 1
                },
                "mu": 50,
                "lambda": 50
            },
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

    result = subprocess.run([args.path, "-j", json.dumps(OneMax)], capture_output=True)
    result_data = json.loads(result.stdout)
    assert result_data["Solution"]["fitness"][0] == 10
    exit(result.returncode)