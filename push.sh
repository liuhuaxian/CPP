#!/bin/sh
set -x
cleanother(){
RMOBJF="*.pro.user *.Debug *.Release Makefile .qmake.stash"
RMOBJD="debug release build*-Debug"
for file in $RMOBJF
do
	find . -type f -name "$file" | xargs rm -fr 
done
for dir in $RMOBJD
do
	find . -type d -name "$dir" | xargs rm -fr 
done
}
cleanother
git add *
git commit -m "`date` push $1"
git push origin master