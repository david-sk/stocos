# STOChastic Optimization Solver (stocos)

Stocos est un solvers clé en main. Il intègre en particuler les algorithmes évolutionnaires. La description du plan d'optimisation s'écrite dans le format JSON : les algorithmes utilisés, le problème à résoudre et la façon d’enregistrer les résultats de l'optimisation.

- C++20
- Json like
- Keep data in mongodb


#### Branch Master 
- **Build Status** (CircleCI) : [![CircleCI](https://circleci.com/gh/Jxtopher/stocos.svg?style=svg)](https://circleci.com/gh/Jxtopher/stocos)
- **CodeFactor** : [![CodeFactor](https://www.codefactor.io/repository/github/jxtopher/stocos/badge)](https://www.codefactor.io/repository/github/jxtopher/stocos)
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

