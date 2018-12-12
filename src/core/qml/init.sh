#!/bin/bash


echo "module Kaj" > Kaj/qmldir
for f in Kaj/*.qml; do
	f=$(basename "$f")
	f="${f%.*}"
        echo "$f 1.0 $f.qml" >> Kaj/qmldir
done


cat Kaj/qmldir
