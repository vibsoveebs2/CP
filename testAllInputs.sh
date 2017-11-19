######################################################################
## 	Author: 	Jonathon R Dahl 			    ##
## 	Purpose: 	Allow for batch input tests		    ##
##	Date:		11/19/17				    ##
######################################################################
echo "This script will allow you to test multiple input files at once"

echo "...Removing old output files..."
rm -rf output.txt

echo "NOTE: The input folder path is ./inputs/"
path="./inputs/"

echo "NOTE: the files must be in this format: input#"
echo "Enter the number of files: "
read number

x=1
while [ $x -le $number ]
do
	file=$path"input"$x
	echo -e "\nRunning: $file" | tee -a output.txt
	./prog4 $file | tee -a output.txt
	x=`expr $x + 1`
	echo -e "Execution of $file complete!\n\n" | tee -a output.txt
done
