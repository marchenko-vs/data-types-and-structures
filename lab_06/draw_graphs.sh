#!/bin/bash

for src_file in *.gv
do
	dot -Tpng ${src_file} -o ${src_file//gv/png}
	start ${src_file//gv/png}
done
