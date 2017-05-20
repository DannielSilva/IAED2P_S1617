#!/bin/bash  

gcc -o bla /home/themrkiko/ist186416/2o_Semestre/IAED/2o\ Projecto/*.c -Wall
#gcc -o bla ~/2o_Semestre/IAED/2o\ Projecto/*.c -Wall
for arg in "$@"
do
	echo ""
  	echo "Running $arg"
  	time ./bla < "${arg%.*}".in > "${arg%.*}".out.bla
  	diff -q "${arg%.*}".out "${arg%.*}".out.bla
done

rm *.bla
rm bla
