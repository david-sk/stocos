#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

#
# @Author: *
# @License: *
# @Date: *
# @Version: *
# @Purpose: *
#



import time
import numpy
import json
import pymongo
import plot
import os.path
import logging



class Experiments:
    def __init__(self, name_of_experience : str, path_stocos_binary : str, configuration : dict, database : str, collection : str):
        self._name_of_experience = name_of_experience
        self._path_stocos_binary = path_stocos_binary
        self._configuration = configuration
        self._database = database
        self._collection = collection
        self._configuration["Statistic"]["database"] = self._database
        self._configuration["Statistic"]["collection"]= self._collection
        self.check()

    def check(self) :
        ## Check existing path stocos
        if not(os.path.exists(self._path_stocos_binary)):
            raise RuntimeError(__file__ + ":" + "100" +"[-] Path file stocos " + self._path_stocos_binary + " does not exist")

        ## Check existing path problem instance
        if not(os.path.exists(self._configuration["problem"]["instance"])):
            raise RuntimeError(__file__ + ":" + "103" +"[-] Path file instance problem "+ self._configuration["problem"]["instance"] +" does not exist")

        ## Check existing collection in database
        client = pymongo.MongoClient() # host="host",port=3622, connectTimeoutMS=500
        db = client[self._database]
        collection = db[self._collection]

        if collection.count_documents({}) != 0:
            raise RuntimeError("[-] Collection alerady exist")

    def run(self,  number_of_experiments : int = 100, outfile : str = "output.pdf"):
        list_of_experiments = self.preProcessing(number_of_experiments, self._name_of_experience)
        print(self.callProcessing(list_of_experiments))
        self.postProcessing(outfile)

    def preProcessing(self, number_of_experiments : int, name_of_experience : str) -> list:
        if not(os.path.exists(self._path_stocos_binary)):
            raise RuntimeError(__file__ + ":" + "128" +"[-] File does not exsit")

        list_of_experiments : list = []
        for i in range(0, number_of_experiments):
            self._configuration["Statistic"]["sensorExperience"]["num"] = i
            list_of_experiments = list_of_experiments + [self._path_stocos_binary + " -j \'" + json.dumps(self._configuration) +"\'"]

        return list_of_experiments

    def callProcessing(self, list_of_experiments : list):
        return parallelExecution(worker, list_of_experiments, 6, "", True)

    def postProcessing(self, outfile : str = "output.pdf"):
        ## Connexion
        client = pymongo.MongoClient() # host="host",port=3622, connectTimeoutMS=500
        db = client[self._database]
        collection = db[self._collection]

        ## query in database
        _query = [{"$group":
                {"_id": "$round",
                "averageValue" :{"$avg": {"$arrayElemAt": ["$Solution.fitness", 0 ]}},
                "stdDev": {"$stdDevSamp": {"$arrayElemAt": ["$Solution.fitness", 0 ]} }
                }
                }, {"$sort":{"_id":1}}]
        data = list(collection.aggregate(_query))

        ## Plot
        p = plot.Linesplot()
        p.add(data, name_x= "_id", name_y="averageValue")
        p.legend(xlabel="round", ylabel="fitness")
        p.tofile(outfile)

if __name__ == '__main__':
    OneMax : dict = {
        "seed": 0,
        "problem": {
            "name": "OneMax",
            "instance": "../instances/OneMax/onemax-1000.json"
        },
        "parameter_id": 0,
        "OptimizationAlgorithm": {
            "0": {
                "className" : "OnePlusLambda",
                "StoppingCriteria": {
                    "budget": 10000,
                    "fitnessObjectif": 1000
                },
                "AtomicOperation": {
                    "className": "FlipBit",
                    "c": 1
                },
                "Selection": "max",
                "lambda": 1
            }
        },            
        "Statistic": {
            "recording":"mongodb",
            "hostname":"localhost",
            "database": "db",
            "collection": "c",
            "sensorExperience" : {
                "name" : "oneMax",
                "num" : 6
            }
        }
    }

    e = Experiments(name_of_experience = "OneMax", path_stocos_binary = "../build/stocos", configuration = OneMax, database = "db", collection = "c9")
    e.run()
