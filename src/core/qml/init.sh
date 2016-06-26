#!/bin/bash


echo "module Tooj" > Tooj/qmldir
for f in Tooj/*.qml; do 
	f=$(basename "$f")
	f="${f%.*}"
	echo "$f 1.0 $f.qml" >> Tooj/qmldir
done


cat Tooj/qmldir