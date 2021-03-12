#include <stdio.h>
#include <pthread.h>

#define THREAD_COUNT 20

int shared_var = 0;
pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;

void* func(void *x) {
	int xi = (int)x;
  	pthread_mutex_lock(&my_lock);
	shared_var += (xi * xi);	// critical section
	pthread_mutex_unlock(&my_lock);
	return NULL;
}

int main() {
	pthread_t threads[THREAD_COUNT];
	
	for (int i = 0; i < THREAD_COUNT; ++i) {
		void* res;
		pthread_create(&threads[i], NULL, func, (void*)(i+1));
		pthread_join(threads[i], &res);
	}			

	for (int i = 0; i < THREAD_COUNT; ++i) {
		void* res;
		pthread_join(threads[i], &res);
	}
	
	printf("%d\n", shared_var);
	return 0;
}
