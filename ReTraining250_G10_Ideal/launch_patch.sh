#!/bin/bash

source init_ilcsoft_patch.sh
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libLCFIPlus.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libISRQQ500.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libCheatdEdxDist.so"
