#include <pthread.h> //compile with option -pthread
#include <stdio.h>
//#include <wiringPi.h> //probably needs an option
#include <stdint.h>
//use option -std=c99

void* thread_function1(void* arg) {
	uint8_t i;
	for (i = 0; i < 15; i++) {
		puts("thread one");
	}
}

void* thread_function2(void* arg) {
	uint8_t i;
	for (i = 0; i < 15; i++) {
                puts("thread two");
        }
}

void* thread_function3(void* arg) {
	uint8_t i;
	for (i = 0; i < 15; i++) {
                puts("thread three");
        }

}

int main (int argc, char argv[]) {
	//wiringPiSetup();

	int thread_return1, thread_return2, thread_return3;
	pthread_t threads[3];

	//pthread_t thread1, thread2, thread3;
	//int p1, p2, p3;

	char *p1 = "a";
	char *p2 = "b";
	char *p3 = "c";

	thread_return1 = pthread_create(&(threads[0]), NULL, thread_function1, NULL);
	thread_return2 = pthread_create(&threads[1], NULL, thread_function2, NULL);
	thread_return3 = pthread_create(&threads[2], NULL, thread_function3, NULL);
  	
  	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);
	pthread_join(threads[2], NULL);

	puts("program completed");

  	//pthread_exit(NULL);
  	return 0 ;
}
