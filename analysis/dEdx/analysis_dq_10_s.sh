#!/bin/sh

mkdir output_y
# file,outputname,ignoreoverlay true or false,min momentum ,quark pdg

#overlay false mean with include the overlay
for overlay in false #true false
do
    for vtx in secondary
    do
	for mom in 10 #3 4 
	do
	    for quark in 3 4 5
	    do
		for cat in all catA catB catC catD
		do
		    root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/merged_small_eL_pR_500GeV_Old.root\",\"500GeV_eL_pR\",\"${vtx}\",${overlay},${mom},${quark},\"${cat}\"\)
		    mv *cut_${mom}*root output_y/.
		    
		    root -l -q analysis.cc\(\"/lustre/ific.uv.es/prj/ific/flc/ntuples-2022/merged_small_eR_pL_500GeV_Old.root\",\"500GeV_eR_pL\",\"${vtx}\",${overlay},${mom},${quark},\"${cat}\"\)
		    mv *cut_${mom}*root output_y/.
		done
	    done
	done
    done
done
#mv *root DQplots/.
