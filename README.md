# STOChastic Optimization Solver (stocos)

- C++20
- Json like
- Keep data in mongodb


#### Branch Master 
- **Linux Build Status** : [![Build Status](https://travis-ci.org/Jxtopher/stocos.svg?branch=master)](https://travis-ci.org/Jxtopher/stocos)
- **lgtm** : --
- **Doc** : --

## Exemple

Le solver se configure de deux manières différents : 
- prendre un ficher json
- prendre une string json


* Solve the oneMax problem :

```bash
$ ./build/stocos-Release -c configuration/stocos-oneMax.json
```

```bash
$ ./build/stocos-Release -j '{ "seed": 0, "problem": { "name": "OneMax", "instance": "instances/OneMax/onemax-50.json" }, "parameter_id": 0, "OptimizationAlgorithm": { "0": { "className":"IteratedLocalSearch", "StoppingCriteria": { "budget": 100, "fitnessObjectif": 50 }, "AtomicOperation": { "className": "FlipBit", "c": 1 }, "OptimizationAlgorithm": { "className": "FirstImprovement", "StoppingCriteria": { "budget": 100, "fitnessObjectif": 50 }, "AtomicOperation": { "className": "FlipBit", "c": 1 } } }  }, "Statistic": { "recording":"stdout", "sensorNumRound" : true, "sensorSolution" : true, "sensorStopwatch" : false, "sensorFinal" : { "name" : "oneMax", "num" : 6 } } }'
```

