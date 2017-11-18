CC=gcc -g -std=c99 -Wall -Wextra -Wno-unused-parameter

default:
	$(CC) -c prog4.c -lpthtread 
clean:
	rm -rf *.o
	rm -rf .so 
