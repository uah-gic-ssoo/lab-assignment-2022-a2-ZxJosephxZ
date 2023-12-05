#include "compute.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* Number of hits */
unsigned int hits;

/* Mutex Semaphore */
pthread_mutex_t mutex;

/* Thread function */
void *thread_function(void *data) {
  /* The input variable contains the number of points that the thread must
   * calculate */
  int points = *((int *)data);

  /* The local variable that shall be used to store the number of points within
   * the circular section */
  int count = 0;
  double aleatorio;
  struct drand48_data rand_buffer;
  srand48_r(time(NULL), &rand_buffer);

  /* TODO: Implement the loop that obtains the random points and counts how
   * many of those lay within the circumference of radius 1 */

  /* TODO: Add the count to the global variable hits in mutual exclusion */
  for (int i = 0; i < points; ++i) {
    drand48_r(&rand_buffer, &aleatorio);
    double x = aleatorio;
    
    drand48_r(&rand_buffer, &aleatorio);
    double y = aleatorio;

    double distance = x * x + y * y;

    if (distance <= 1.0) {
      count++;
    }
  }
  pthread_mutex_lock(&mutex);
  hits += count;
  pthread_mutex_unlock(&mutex);
  return NULL;
}

void compute(int npoints, int nthreads) {
  /* TODO: Erase the following line: */
  printf("compute(%d, %d)\n", npoints, nthreads);

  /* TODO: Launch the threads that will count the points */

  /* TODO: Wait for all threads to finish */

  /* TODO: print the ratio of points that meet the criteria */

  /* The following print string can be used to print the calculated value:
   * printf("%.8f\n", VALUE_OF_PI);
   * where VALUE_OF_PI is the floating-point value to be printed.
   */
  pthread_t threads[nthreads];
  int points_per_thread = npoints / nthreads;

  for (int i = 0; i < nthreads; ++i) {
    pthread_create(&threads[i], NULL, thread_function, &points_per_thread);
  }

  /* Wait for all threads to finish */
  for (int i = 0; i < nthreads; ++i) {
    pthread_join(threads[i], NULL);
  }
  double ratio = (double)hits / npoints;
  printf("%.8f\n", 4.0 * ratio);
}
