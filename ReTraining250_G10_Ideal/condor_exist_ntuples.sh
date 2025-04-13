#!/bin/bash

path=$PWD
path_lustre=/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/250/dEdx_Samples

for prod in eL_pR eR_pL
do
    if [ ${prod} == "eL_pR" ]; then
	for nameaux in 00015161 00015162
        do
            folder_name="/lustre/ific.uv.es/prj/ific/flc/mc-2020/250-SetA/2f_hadronic_"${prod}"/ILD_l5_o1_v02/v02-02/"${nameaux}"/000/"
            cd $folder_name
            echo $folder_name            
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
			if [ -f ${path}/${flavour}_${prod}_${nameaux}_${name}_Kisr_${isrcut}.root ];
			then
			    echo "Skip "${name}
			else
			    cp ${path}/test_default_makentuple2.xml ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xNAMEAUX/'${nameaux}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    
			    cp ${path}/run_default2.sh ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    sed -i -e 's/xNAMEAUX/'${nameaux}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    
			    cp ${path}/run_default2.sub ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    sed -i -e 's/xNAMEAUX/'${nameaux}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub	    
	    
			    echo "Submit --- > " ${prod} ${nameaux} ${name} ${flavour}   
			    cd -
			    #echo "sending job: " run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    condor_submit run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    #echo "job sent"
			    sleep 0.01s 
			    cd -
    			    #rm ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    #rm ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh    
			fi
		    done
		done
		i=$((i+1))
	    done
	    cd -
	done
    elif [ ${prod} == "eR_pL" ]; then
        for nameaux in 00015164 00015165 00015275
        do
            folder_name="/lustre/ific.uv.es/prj/ific/flc/mc-2020/250-SetA/2f_hadronic_"${prod}"/ILD_l5_o1_v02/v02-02/"${nameaux}"/000/"
            cd $folder_name
            echo $folder_name

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
                        if [ -f ${path}/${flavour}_${prod}_${nameaux}_${name}_Kisr_${isrcut}.root ];
                        then
			    echo "Skip "${name}
                        else
			    cp ${path}/test_default_makentuple2.xml ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xNAMEAUX/'${nameaux}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
			    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml
                            sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/test_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.xml

                            cp ${path}/run_default2.sh ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
                            sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
                            sed -i -e 's/xNAMEAUX/'${nameaux}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
                            sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh

                            cp ${path}/run_default2.sub ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
                            sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
                            sed -i -e 's/xNAMEAUX/'${nameaux}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
			    sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
                            sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub

                            echo "Submit --- > " ${prod} ${nameaux} ${name} ${flavour}
                            cd -
                            #echo "sending job: " run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
                            condor_submit run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
                            #echo "job sent"                                                                                                                                  
                            sleep 0.01s
                            cd -
                            #rm ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sub
                            #rm ${path}/run_${prod}_${nameaux}_${flavour}_${name}_Kisr_${isrcut}.sh
			fi
                    done
                done
                i=$((i+1))
            done
            cd -
	done
    fi
done

for slp in 60m 60m 60m 60m 60m 60m 60m 30m 60m 60m 60m 60m 60m 60m 30m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 60m 30m 30m 30m 30m 30m
do
    sleep ${slp}
    echo "zzz for" $slp
    mv ${path}/*root ${path_lustre}/.
done
