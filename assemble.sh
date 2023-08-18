#!/bin/bash

ASM='nasm'
ASMFLAGS='-f elf'

ret=0

for x in `find . -name "*.asm"`
do
	dname=`dirname $x`
	bname=`basename $x`

	extension="${bname##*.}"
	filename="${bname%.*}"

	$ASM $ASMFLAGS -o "src/${filename}.o" $x
	ret=$?

	if [ "$ret" != "0" ]
	then
		echo "Assemble fail!"
		exit 1
	fi
done

exit 0
