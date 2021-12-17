#!/bin/bash/

cd out/

for gv_file in *.gv
do
	dot -Tpng $gv_file -o ${gv_file//gv/png}
	start ${gv_file//gv/png}
done

rm *.gv
