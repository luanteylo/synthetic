#!/bin/bash

EXEC=s1

OMEGA=25  # Application's total number of iterations default=25
ALPHA=12000 # Total number of iterations on computation phase default=120000
BETA=0 # Total number of iterations on communication phase default=5200
GAMA=100000 # Working set size default=7000
DELTA=1 #Step at which the vector elements in memory Access loop are accessed default=512
TETA=0  # Total number of iterations of compute-intesive loop default=0
LAMBDA=22600 # Amount of data excanged among processes default=22600

#mpicc synthetic.c -lm /usr/local/lib/libpapi.a -DPASSO=$DELTA  -DWSS=$GAMA  -DVECTOR_NUM=3 -DTETA=$TETA  -DBYTES_MSG=$LAMBDA -DBETA=$BETA -DALPHA=$ALPHA -DOMEGA=$OMEGA -DLABEL=1 -o s1

mpicc sintetico.c -lpapi -lm  -DPASSO=$DELTA  -DWSS=$GAMA  -DVECTOR_NUM=3 -DTETA=$TETA  -DBYTES_MSG=$LAMBDA -DBETA=$BETA -DALPHA=$ALPHA -DOMEGA=$OMEGA -DLABEL=1 -o $EXEC

if [ -d "bin/" ]; then
	rm -f bin/*
else
	mkdir bin
fi

mv $EXEC bin/
