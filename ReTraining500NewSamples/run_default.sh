#!/bin/bash
# file name: kt_xNAMEfile.sh

path="/lhome/ific/m/marherje/FlavourTagExtension/ReTraining500NewSamples"
source ${path}/init_ilcsoft_patch.sh
cp -r ${path}/lib $PWD/.
cp -r ${path}/data $PWD/.
cp -r ${path}/lcfiweights $PWD/.
#cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_xPROD_xFLAVOUR_xNAMEfile_Kisr_xISRCUT.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libLCFIPlus.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libISRQQ500.so"
echo $PWD
Marlin ${PWD}/test_xPROD_xFLAVOUR_xNAMEfile_Kisr_xISRCUT.xml