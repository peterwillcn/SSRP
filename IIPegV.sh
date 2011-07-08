if [ "$1" == "00" ]
then
    sspp stat -v 50 -j 10 -w 5 50 -c 100 >> results00.txt &
elif [ "$1" == "01" ]
then
    sspp stat -v 100 -j 20 -w 20 100 -c 100 >> results01.txt &
elif [ "$1" == "02" ]
then
    sspp stat -v 200 -j 100 -w 20 100 -c 100 >> results02.txt &
fi