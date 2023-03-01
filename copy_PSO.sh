#!/bin/bash 
shopt -s extglob
mkdir ParticleSwarmOptimization
cp -rv ../ParticleSwarmOptimization/!(data|250GeV_PSO_Performance|500GeV_PSO_Performance|TestingROC|TestingKSTest) ParticleSwarmOptimization
