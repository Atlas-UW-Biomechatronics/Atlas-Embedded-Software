#include <pthread.h> //compile with option -pthread
#include <stdio.h>
#include <wiringPi.h> //probably needs an option

void* thread_function1(void* arg) {
	return;
}

void* thread_function2(void* arg) {
	return;
}

void* thread_function3(void* arg) {
	return;
}

int main (int argc, char argv[]) {
	wiringPiSetup();

	int thread_return1, thread_return2, thread_return3;
	pthread_t threads[3];

	thread_return1 = pthread_create(&threads[0], NULL, thread_return1, NULL);
	thread_return2 = pthread_create(&threads[1], NULL, thread_return2, NULL);
	thread_return3 = pthread_create(&threads[2], NULL, thread_return3, NULL);
  	
  	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);

  	pthread_exit(NULL);
  	return 0 ;
}