#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define BUFFER_SIZE 10

typedef struct
{
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
	// do nothing -- no free buffer item
	}
	memcpy(&buffer[first], i,sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
	// do nothing -- nothing to consume
	}
	memcpy(i, &buffer[last],sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	return i;
}

void *threadProduceFunction(void *params) {
	printf("This is a produce thread.\n");
	printf("At Beginning : First:%d Last%d\n",first,last );
	item* item1 = malloc(sizeof(item));
	item1->type = 1;
	item1->amount =5;
	item1->unit =0;
	printf("item 1: Type: %d\tAmount: %d\tUnit: %d\n",item1->type,item1->amount,item1->unit );
	item* item2 = malloc(sizeof(item));
	item2->type = 0;
	item2->amount =100;
	item2->unit =1;
	printf("item 2: Type: %d\tAmount: %d\tUnit: %d\n",item2->type,item2->amount,item2->unit );
	item* item3 = malloc(sizeof(item));
	item3->type = 0;
	item3->amount =100;
	item3->unit =1;
	printf("item 3: Type: %d\tAmount: %d\tUnit: %d\n",item3->type,item3->amount,item3->unit );

	produce(item1);
	printf("Produce First item\nFirst:%d Last%d\n",first,last );
	produce(item2);
	printf("Produce Second item\nFirst:%d Last%d\n",first,last );
	produce(item3);
	printf("Produce Third item\nFirst:%d Last%d\n",first,last );
	return 0;
}

void *threadConsumeFunction(void *params) {
	printf("This is a consume thread\n");
	
	consume();
	printf("Consume an item\nFirst:%d Last:%d\n",first,last );
	consume();
	printf("Consume an item\nFirst:%d Last:%d\n",first,last );
}



int main() 
{
	// create a background thread to execute threadFunction
	pthread_t tid1,tid2;
	pthread_create(
		&tid1,
		// get thread id
		NULL,
		// skip the attributes
		threadProduceFunction,
		// thread function name
		NULL
	);
	// argument to thread function
	// main thread execution continues here
	// [optional] wait for thread to finish
	
	printf("Main thread after produce 3\n");

	pthread_create(
		&tid2,
		// get thread id
		NULL,
		// skip the attributes
		threadConsumeFunction,
		// thread function name
		NULL
	);

	printf("Main thread after consume 2\n");	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	return 0;
}