

default:
	gcc -o prog4 prog4.c -std=c99 -lpthread
clean:
	rm -rf *.o
	rm -rf .so 
