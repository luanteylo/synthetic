#! /bin/bash

# Varing TETA

for i in $(seq $1 $2 $3); do
	make CFLAGS="-DTETA=$i" PROG_NAME=s_teta_$i

	for k in $(seq 1 2); do
		echo "exec: $k"
		./bin/s_teta_$i >> output_teta_$i.txt
	done
done
 
