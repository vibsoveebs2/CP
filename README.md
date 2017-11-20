#######################################################################################
PA4: Write a Multi-threaded Program using Pthreads			       11/19/17
---------------------------------------------------------------------------------------
README

(1) Quick Overview
(2) Running the Program
(3) Semaphores!
---------------------------------------------------------------------------------------
(1)	This program attempts to simulate the Problem Description found in the PA4.pdf
	file. The parent creates four children threads, one of which represents Captain
	John Smith's ship and is referred to as the "Empress". The other three threads 
	simulate the merchants Smith needs to trade with. All of the children were
	assigned thread ids for accessing shared global variables. The program 
	simulates the Empress's perspective with the day variable changing within this 
	thread. The Empress is unaware of the merchants activities until the day of 
	arrival, which is assumed to be midnight of the previous day. The code 
	simulates this by checking the merchant's schedules at the end of day prior to 
	arrival.
---------------------------------------------------------------------------------------
(2)	* Use the included Makefile to compile and clean *
	There are currently two methods to running the program:
	(a) Passing a filename
		The program accepts a file path at the command line. The file contents
		should be formatted as such:
			1, 2, 3, 4	
		Where the first value is the Empress's arrival time, the second number
		is the first merchants arrival time, and etc. The program will output a
		message to stdout in case of failure. The repository contains some
		sample input files located in the inputs folder.
 
		To run the program at the command line using the input1 file:
			./prog4 ./inputs/input1

	(b) Running a batch of files
		A bash shell script called testAllInputs has been included to allow for
		the testing of batches of input files. When run, this script will ask
		for the last file number to execute. If I wanted to run files input1
		through input15, I would enter 15. If the range does not start at
		input1, then comments in the shell script will indicate which variable
		to adjust. For convenience, the output is not only displayed to the
		terminal, but also saved in a file called output.txt. If this file
		does not exist, the script will create it; However if the file EXISTS, 
		it wil be DELETED.
		
		Running the script:
			./testAllInputs.sh
			20
---------------------------------------------------------------------------------------
(3)     A Pthread program with...Semaphores!?
	The Pthreads library has its uses, but spin locks are really inefficient. With
	the uncertainty of the target system, we decided it would be inept to implement
	them needlessly. Thus for our implementation, we chose to use semaphores. They
	required less complexity and were the more efficient choice. You'll find them 
	used as the lock and condition variables.
=======================================================================================
AUTHORS

	Jonathon Dahl
	Vibhu C. Patel
	Sanyukta Baluni

---------------------------------------------------------------------------------------
Supporting Authors: 

	Bhuvan Urgaonkar
	Ata Fatahi Baarzi
	Aman Jain
	Diman Tootaghaj

=======================================================================================
BUGS

	* 11/19/17 * The Empress outputs "We bought some goods!" on days that no goods
		were purchased. In future releases, this issue should be patched with
		a better signaling method.

#######################################################################################
