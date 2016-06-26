#!/bin/bash




for f in *.ttf; do 
	f=$(basename "$f")
	f="${f%.*}"
	text="
<RCC>
    <qresource prefix=\"/fonts\">
        <file alias=\"$f\">$f.ttf</file>
    </qresource>
</RCC>"

	echo "$text" > "$f.qrc"
done
