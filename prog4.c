#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *fun_empress(void *arg) {
  //blah
  printf("Empress creation successful!");
  return NULL;
}

void *fun_merchant(void *arg) {
  //blah
  printf("Merchant creation successful!");
  return NULL;
}

int main(int argc, char *argv[]) {
  // input file read here
  // set date to -1, when empress arrives set day.
  // for each merchant, check date. if negative empress not there
  // when empress arrives set the date
  int e_arrive, m1_arrive, m2_arrive, m3_arrive;

  FILE *fin;
  //fin = fopen(argv[1], "r");
  fin = fopen("input/input1", "r");
  if(fin == NULL) {
    printf("Error opening file, check file and try again");
    return (-1);
  } else {
    // get, separate, and store values
    if(fscanf(fin, "%d, %d, %d, %d", &e_arrive, &m1_arrive, &m2_arrive, &m3_arrive)) {
	// error
	printf("Error in input file, example input: 1, 2, 3, 4");
	return (-1);
    }
    printf("Empress: %d", e_arrive);
    printf("M1: %d", m1_arrive);
    printf("M2: %d", m2_arrive);
    printf("M3: %d", m3_arrive);
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
