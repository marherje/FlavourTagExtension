#!/bin/bash

source init_ilcsoft_patch.sh
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libLCFIPlus.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libISRQQ500.so"
Marlin TrainMVA_2f250_catC.xml > Train_catC.log
