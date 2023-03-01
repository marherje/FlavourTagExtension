for pol in eR
do
  Marlin TrainMVA_${pol}_2f250.xml > log_TrainMVA_${pol}_2f250.txt
  Marlin TrainMVA_${pol}_vvH250.xml > log_TrainMVA_${pol}_vvH250.txt
  Marlin TrainMVA_${pol}_2f500.xml > log_TrainMVA_${pol}_2f500.txt
done
