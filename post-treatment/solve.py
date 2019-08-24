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

from multiprocessing import Pool

import sys
import time
import numpy
import json
import pymongo
import plot
import os.path
import logging

if (sys.version_info > (3, 0)): # Python 3 code in this block
	import subprocess
else: # Python 2 code in this block
	from commands import getstatusoutput


###############################################################
def parallelExecution(run_function, cmds_exec, nbProcessus = 1, stdout = None, ret = False):
	def secondsToStr(t):
	    return "%d:%02d:%02d.%03d" % \
		reduce(lambda ll,b : divmod(ll[0],b) + ll[1:], [(t*1000,),1000,60,60])

	if stdout != "" and stdout != None:
		sys.stdout = open(stdout, 'a')

	startTime = time.time()
	jobs = []
	retInfo = []
	pool = Pool(processes = nbProcessus)
	
	numpy.random.seed = 0
	numpy.random.shuffle(cmds_exec)

	print("[+] Nomber of execution " + str(len(cmds_exec)))
	print("[+] " + str(cmds_exec[0]))

	try:
		if ret:
			jobs = pool.map_async(run_function, cmds_exec)
			pool.close()
			#pool.join()
			retInfo = jobs.get()
		else:
			pool.map_async(run_function, cmds_exec)
			pool.close()
			#pool.join()
	except KeyboardInterrupt:
		print('parent received control-c')
		pool.terminate()

	#print("[+] Execution time " + secondsToStr(time.time() - startTime))
	if stdout != None:
		if stdout != "":
			if retInfo != []:
				print(retInfo)
			sys.stdout = sys.__stdout__
	return retInfo

# function worker execute des prgrammes exterieurs avec des
# parametres command_line
def worker(command_line):
    try:
        if (sys.version_info > (3, 0)):
            # Python 3 code in this block
            return subprocess.getstatusoutput(command_line)
        else:
            # Python 2 code in this block
            return getstatusoutput(command_line)
 		
    except KeyboardInterrupt:
        return 'KeyboardException'
###############################################################

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
