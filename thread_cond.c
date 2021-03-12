#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int fuel = 0;
pthread_mutex_t lock   =  PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t checker =  PTHREAD_COND_INITIALIZER; 

void* car(void *nothing) {
	pthread_mutex_lock(&lock);
	while (fuel < 40) {
		printf("No fuel!\n");
		pthread_cond_wait(&checker, &lock);
	}
	fuel -= 40;
	printf("Car %d\n", fuel);
	pthread_mutex_unlock(&lock);
	return nothing;
}

void* filler(void *nothing) {
	for (int i = 0; i < 5; ++i) {
		pthread_mutex_lock(&lock);
		fuel += 15;
		printf("Filler %d\n", fuel);
		pthread_mutex_unlock(&lock);
  		pthread_cond_signal(&checker);
	  	sleep(1);
  }
  return nothing;
} 

int main() {
	pthread_t threads[2];
	for (int i = 0; i < 2; ++i) {
		if(i % 2) {
			pthread_create(&threads[i], NULL, filler, NULL);
    	}
		else {
			pthread_create(&threads[i], NULL, car, NULL);
		}
	}
	
	for (int i = 0; i < 2; ++i) {
		void *nothing;
		pthread_join(threads[i], &nothing);
	}
	return 0;
}
