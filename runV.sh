rm -f compute-0-* results*
for node in compute-0-0 compute-0-1 compute-0-2 compute-0-3 compute-0-4 compute-0-5 compute-0-6 compute-0-7 compute-0-8 compute-0-9
do
  mpirun -np 1 --host $node sh IIPegV.sh 00 &
  sleep 4
  mpirun -np 1 --host $node sh IIPegV.sh 01 &
  sleep 4
  mpirun -np 1 --host $node sh IIPegV.sh 02 &
done