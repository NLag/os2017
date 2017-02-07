#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int main()
{
	printf("At Beginning \nFirst:%d Last%d\n",first,last );
	item* item1 = malloc(sizeof(item));
	item1->type = 1;
	item1->amount =5;
	item1->unit =0;
	printf("item 1:\nType: %d\nAmount:%d\nUnit: %d\n",item1->type,item1->amount,item1->unit );
	item* item2 = malloc(sizeof(item));
	item2->type = 0;
	item2->amount =100;
	item2->unit =1;
	printf("item 2:\nType: %d\nAmount:%d\nUnit: %d\n",item2->type,item2->amount,item2->unit );
	produce(item1);
	printf("Produce First item\nFirst:%d Last%d\n",first,last );
	produce(item2);
	printf("Produce Second item\nFirst:%d Last%d\n",first,last );
	item1 = consume();
	printf("Consume First item\nFirst:%d Last%d\n",first,last );
	return 0;
}