PA4: Multithreaded Programs using pthreads   11/19/2017
------------------------------------------------------------------------------------------------------------------------------------------

(1) Reading the input files 
(2) Creation of a shell script 
(3) Running the program
------------------------------------------------------------------------------------------------------------------------------------------

(1) There is a function in prog4.c called int getInput (char *argv[]) which scans the input file that we would like to read. If the file handler is NULL, that is it is an illegal file, there is a message that pops up saying that, "Error opening file. Check the file path and try again". Else, it will scan all the 4 input values (which are the arrival times of the empress and the merchants). That number of inputs should be equal to exactly 4 or else there will again be an error saying, "Error in input file. Example input: 1,2,3,4".
------------------------------------------------------------------------------------------------------------------------------------------

(2) There is also a shell script in our folder called testAllInputs.sh which checks all the 20 input files at one instance. There will be a prompt on the terminal which will ask you to "Enter the last file number:" Please select 20 as there are 20 input files provided. On hitting enter, we will get the desired output for each of them as you can see in the report provided.
------------------------------------------------------------------------------------------------------------------------------------------

(3) To run the program, we need to make sure that the input files and prog4.c and the testAllInputs.sh are in the same directory. We can run every input file separately using the command ./prog4 ./inputs/input1 or you can directly use the shell script ./testAllInputs.sh and the script will allow you to test multiple input files at once.
------------------------------------------------------------------------------------------------------------------------------------------

AUTHORS
	Jonathon Dahl
	Sanyukta Baluni	
	Vibhu C. Patel
 -----------------------------------------------------------------------------------------------------------------------------------------

Supporting Authors:
Ata Fatahi Baarzi, Aman Jain, Diman Tootaghaj and Bhuvan Urgaonkar
------------------------------------------------------------------------------------------------------------------------------------------

BUGS:
	None
 -----------------------------------------------------------------------------------------------------------------------------------------
