#!/bin/bash
TIMEFORMAT="%U"
for i in {10..100000..200}; do
	for j in {1..50..1}; do
		TIME=`./rand ${i} | { time ./tp1 > /dev/null; }`
		TIME=${TIME//\\n//};		
		echo "${i} ${i} ${TIME}";  
	done;
done &> tempos.txt


TIMEFORMAT="%U"
for i in {10..100000..200}; do for j in {1..50..1}; do TIME=`./rand ${i} | { time ./tp1 > /dev/null; }` TIME=${TIME//\\n//}; echo "${i} ${i} ${TIME}"; done; done &> tempos.txt