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
            "name": "n-queens",
            "instance_number": "4",
            "n": 4,
            "fitnessObjectif": 4
        },
        "parameter_id": 0,
        "Optimization": {
            "0": {
                "className":"TabuSearch",
                "StoppingCriteria": {
                    "budget": 100000,
                    "fitnessObjectif": 10
                },
                "AtomicOperation": {
                    "className": "IntervalInteger",
                    "c": 1,
                    "a": 0,
                    "b": 3
                },
                "sizeOfTabuList": 7
            }
        },            
        "Statistic": {
            "recording":"stdout",
            "sensorNumRound" : False,
            "sensorSolution" : False,
            "sensorStopwatch" : False,
            "sensorFinal" : {
                "name" : "n-queens problem",
                "num" : 6
            }
        }
    }
    
    result = subprocess.run([args.path, "-j", json.dumps(OneMax)], capture_output=True)
    result_data = json.loads(result.stdout)
    assert result_data["Solution"]["fitness"][0] == 4
    # exit(result.returncode)