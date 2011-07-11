rm -f compute-0-* results*
NUMRUNS=10
for node in compute-0-0 compute-0-1 compute-0-2 compute-0-3 compute-0-4 compute-0-5 compute-0-6 compute-0-7 compute-0-8 compute-0-9
do
  COUNTER=0
  JOURNEYS=25
  VERTICES=50
  while [ -e "${node}-lock" ]; do
    sleep 4
  done
  while [ $COUNTER -lt $NUMRUNS ]; do
    touch "${node}-lock"
    mpirun -np 1 --host $node sh IIPegV.sh $VERTICES $JOURNEYS $node
    rm "${node}-lock"
    let JOURNEYS=JOURNEYS+25
    let VERTICES=VERTICES+50
    let COUNTER=COUNTER+1
  done 
done
