#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

from multiprocessing import Pool
import sys
import time
import numpy

if (sys.version_info > (3, 0)): # Python 3 code in this block
	import subprocess
else: # Python 2 code in this block
	from commands import getstatusoutput

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

def parallelExecution(cmds_exec, nbProcessus = 1, run_function = worker, stdout = None, ret = False):
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

