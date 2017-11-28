
#!/bin/bash  

# example of using arguments to a script

DaylightDir="$1"


FILES=./*
for f in $FILES
do

	TARGETED_FILE="${DaylightDir}$f"

	echo "File name in current direcotry: $f"
	echo "Targeted File $TARGETED_FILE"

	diff $f $TARGETED_FILE 	

	read -n1 -r -p "Press any to continue..." key
	clear

  # take action on each file. $f store current file name
done

