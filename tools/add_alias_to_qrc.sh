#!/bin/bash

rm 2-qml.qrc
cp {,2-}qml.qrc
sed -i -E 's/<file>(.*)\/([^.]+)\.([^>]+)/<file alias="\2">\1\/\2.\3/g' 2-qml.qrc 
