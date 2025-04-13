#!/bin/bash

path=$PWD
folder_name="/lustre/ific.uv.es/prj/ific/flc/mc-2020/flavortag/"
cd $folder_name
echo $folder_name
echo $fprod

FILES=*

i=0

for f in $FILES
do
    for flavour in b_quark c_quark light_quark #u_quark d_quark s_quark c_quark light_quark
    do
	for isrcut in 35 #-1
	do
	    name="00"$i
	    if [ $i -gt 9 ]; then
		name="0"$i
	    fi
	    
	    if [ $i -gt 99 ]; then
		name=$i
	    fi
	    
	    cp ${path}/test_default_makentuple.xml ${path}/test_${flavour}_${name}_Kisr_${isrcut}.xml
	    sed -i -e 's/NFile/'${f}'/g' ${path}/test_${flavour}_${name}_Kisr_${isrcut}.xml
	    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/test_${flavour}_${name}_Kisr_${isrcut}.xml
	    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/test_${flavour}_${name}_Kisr_${isrcut}.xml
	    sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/test_${flavour}_${name}_Kisr_${isrcut}.xml
	    
	    cp ${path}/run_default.sh ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sh
	    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sh
	    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sh
	    sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sh
	    
	    cp ${path}/run_default.sub ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sub
	    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sub
	    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sub
	    sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${flavour}_${name}_Kisr_${isrcut}.sub	    
	    
	    echo "Submit --- > " ${name} ${flavour}   
	    cd -
	    #echo "sending job: " run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
	    condor_submit run_${flavour}_${name}_Kisr_${isrcut}.sub
	    #echo "job sent"
	    sleep 0.01s 
	    cd -
    	    #rm ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
	    #rm ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
	done	    
    done
    i=$((i+1))
done
cd -


