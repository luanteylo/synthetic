#!/bin/bash

EXEC=s1

OMEGA=25  # Application's total number of iterations
ALPHA=120000 # Total number of iterations on computation phase
BETA=5200 # Total number of iterations on communication phase
# GAMA=7000 # Working set size
GAMA=100000 # Working set size
DELTA=512 #Step at which the vector elements in memory Access loop are accessed
TETA=0  # Total number of iterations of compute-intesive loop
LAMBDA=22600 # Amount of data excanged among processes

#mpicc synthetic.c -lm /usr/local/lib/libpapi.a -DPASSO=$DELTA  -DWSS=$GAMA  -DVECTOR_NUM=3 -DTETA=$TETA  -DBYTES_MSG=$LAMBDA -DBETA=$BETA -DALPHA=$ALPHA -DOMEGA=$OMEGA -DLABEL=1 -o s1

mpicc sintetico.c -lpapi -lm  -DPASSO=$DELTA  -DWSS=$GAMA  -DVECTOR_NUM=3 -DTETA=$TETA  -DBYTES_MSG=$LAMBDA -DBETA=$BETA -DALPHA=$ALPHA -DOMEGA=$OMEGA -DLABEL=1 -o $EXEC

if [ -d "bin/" ]; then
	rm -f bin/*
else
	mkdir bin
fi

mv $EXEC bin/
