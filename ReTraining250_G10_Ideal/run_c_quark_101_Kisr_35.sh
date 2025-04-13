#!/bin/bash
# file name: kt_101.sh

path="/lhome/ific/m/marherje/FlavourTagExtension/ReTraining250_G10_Improved"
source ${path}/init_ilcsoft_patch.sh
cp -r ${path}/lib $PWD/.
cp -r ${path}/data $PWD/.
cp -r ${path}/lcfiweights $PWD/.
#cp ${path}/GearOutput.xml $PWD/.
cp ${path}/test_c_quark_101_Kisr_35.xml .

export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libLCFIPlus.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libISRQQ500.so"
export MARLIN_DLL="$MARLIN_DLL:$PWD/lib/libCheatdEdxDist.so"
echo $PWD
Marlin ${PWD}/test_c_quark_101_Kisr_35.xml
