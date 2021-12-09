#!/bin/sh

a="$(./clikv __ search zz)"
b="$(./clikv __ set zz 7)"
c="$(./clikv __ get zz)"
d="$(./clikv __ search zz)"
 
rm __;

if [ "$a" = "not found" ];
then
	echo "Test A passed"
else
	echo "Test A not passed"
fi;
if [ "$b" = "" ];
then
	echo "Test B passed"
else
	echo "Test B not passed"
fi;
if [ "$c" = "7" ];
then
	echo "Test C passed"
else
	echo "Test C not passed"
fi;
if [ "$d" = "found" ];
then
	echo "Test D passed"
else
	echo "Test D not passed"
fi;
