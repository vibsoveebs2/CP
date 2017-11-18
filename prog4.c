#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>



void *fun_empress(void *arg) {
  //blah
  printf("Empress creation successful!\n");
  return NULL;
}

void *fun_merchant(void *arg) {
  //blah
  printf("Merchant creation successful!\n");
  return NULL;
}

int main(int argc, char *argv[]) {
  int e_arrive, m1_arrive, m2_arrive, m3_arrive;

  FILE *fin;
  fin = fopen(argv[1], "r");
  if(fin == NULL) {
    printf("Error opening file, check file and try again\n");
    return (-1);
  } else {
    // get, separate, and store values
    if(fscanf(fin, "%d, %d, %d, %d", &e_arrive, &m1_arrive, &m2_arrive, &m3_arrive) == 0) {
	// error
	printf("Error in input file, example input: 1, 2, 3, 4\n");
	return (-1);
    }
    printf("Empress: %d\n", e_arrive);
    printf("M1: %d\n", m1_arrive);
    printf("M2: %d\n", m2_arrive);
    printf("M3: %d\n", m3_arrive);
  }  
  fclose(fin);

  pthread_t empress, merchant1, merchant2, merchant3;
  int rc;
  printf("main: begin creation\n");
  rc = pthread_create(&empress, NULL, fun_empress, &e_arrive); assert(rc == 0);
  rc = pthread_create(&merchant1, NULL, fun_merchant, &m1_arrive); assert(rc == 0);
  rc = pthread_create(&merchant2, NULL, fun_merchant, &m2_arrive); assert(rc == 0);
  rc = pthread_create(&merchant3, NULL, fun_merchant, &m3_arrive); assert(rc == 0);

  // join waits for the threads to finish
  rc = pthread_join(empress, NULL); assert(rc == 0);
  rc = pthread_join(merchant1, NULL); assert(rc == 0);
  rc = pthread_join(merchant2, NULL); assert(rc == 0);
  rc = pthread_join(merchant3, NULL); assert(rc == 0); 
  printf("main: exiting\n");
  return 0;   // return successfully
}
