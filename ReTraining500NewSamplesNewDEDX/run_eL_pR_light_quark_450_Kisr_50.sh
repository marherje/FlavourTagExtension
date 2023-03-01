#!/bin/bash
# file name: kt_450.sh

path="/lhome/ific/m/marherje/FlavourTagExtension/ReTraining500NewSamplesNewDEDX"
source ${path}/init_ilcsoft_patch.sh
cp -r ${path}/lib $PWD/.
cp -r ${path}/data $PWD/.
cp -r ${path}/lcfiweights $PWD/.
#cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_eL_pR_light_quark_450_Kisr_50.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libLCFIPlus.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libISRQQ500.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libCheatdEdxDist.so"
echo $PWD
Marlin ${PWD}/test_eL_pR_light_quark_450_Kisr_50.xml
