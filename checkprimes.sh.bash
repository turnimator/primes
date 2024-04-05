#!/bin/bash
# 
# File:   checkprimes.sh.bash
# Author: atle
#
# Created on Apr 4, 2024, 10:42:56 PM
#
for f in `dist/Debug/GNU-Linux/pprimes 10000000` ; do echo -n "$f " ; ../pprimes/isprime/dist/Debug/GNU-Linux/isprime "$f" ; done 