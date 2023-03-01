#!/bin/bash

path=$PWD

for prod in "eL_pR" #"eR_pL" 
do
    if [ $prod == "eL_pR" ]; then
	for fprod in "00015902" "00015903" 
        do
            folder_name="/lustre/ific.uv.es/prj/ific/flc/500-TDR_ws/2f_Z_hadronic/ILD_l5_o1_v02/v02-02-03/"${fprod}"/000"
            cd $folder_name
            echo $folder_name
            echo $fprod
            
            FILES=*
            
            i=0
        
	    for f in $FILES
	    do
		for flavour in b_quark c_quark light_quark #u_quark d_quark s_quark c_quark light_quark
		do
		    for isrcut in 50 #-1
		    do
			name="00"$i
			if [ $i -gt 9 ]; then
			    name="0"$i
			fi
	    
			if [ $i -gt 99 ]; then
			    name=$i
			fi
			
			cp ${path}/test_default_makentuple.xml ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
			sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
			sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
			sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
			sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
			sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
			sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
			
			cp ${path}/run_default.sh ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
			sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
			sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
			sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
			sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
			sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
			
			cp ${path}/run_default.sub ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
			sed -i -e 's/xFPROD/'${fprod}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
			sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
			sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
			sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
			sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub	    
			
			echo "Submit --- > " ${name} ${flavour}   
			cd -
			#echo "sending job: " run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
			condor_submit run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
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
	done
    fi
    if [ $prod == "eR_pL" ]; then
        for fprod in "00015905" "00015906"
        do
            folder_name="/lustre/ific.uv.es/prj/ific/flc/500-TDR_ws/2f_Z_hadronic/ILD_l5_o1_v02/v02-02-03/"${fprod}"/000"
            cd $folder_name
            echo $folder_name
            echo $fprod
            FILES=*
            i=0
            for f in $FILES
	    do
                for flavour in b_quark c_quark light_quark #u_quark d_quark s_quark c_quark light_quark
                do
                    for isrcut in 50 #-1
                    do
                        name="00"$i
                        if [ $i -gt 9 ]; then
                            name="0"$i
                        fi

                        if [ $i -gt 99 ]; then
                            name=$i
                        fi
                        if [ -f ${path}/${prod}_${flavour}_${name}_Kisr_${isrcut}.slcio ];
                        then
                            echo "Skip "${name}
                        else
                            cp ${path}/test_default_makentuple.xml ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
                            sed -i -e 's/xPROD/'${prod}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
                            sed -i -e 's/NFile/'${f}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
                            sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
                            sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml
                            sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/test_${prod}_${flavour}_${name}_Kisr_${isrcut}.xml

                            cp ${path}/run_default.sh ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
                            sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
                            sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
                            sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh
                            sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh

                            cp ${path}/run_default.sub ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
                            sed -i -e 's/xPROD/'${prod}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
                            sed -i -e 's/xNAMEfile/'${name}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
                            sed -i -e 's/xFLAVOUR/'${flavour}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
                            sed -i -e 's/xISRCUT/'${isrcut}'/g' ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub

                            echo "Submit --- > " ${name} ${flavour}
                            cd -
                            #echo "sending job: " run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub                                                                                            
                            condor_submit run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
                            #echo "job sent"
                            sleep 0.01s
                            cd -
                        fi
                        #rm ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sub
                        #rm ${path}/run_${prod}_${flavour}_${name}_Kisr_${isrcut}.sh                                                                                                                                          
                    done
                done
                i=$((i+1))
            done
            cd -
	done
    fi
done

