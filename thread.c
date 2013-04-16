#include<stdio.h>
#include<pthread.h>

typedef char * string;

typedef struct _threadHandler
{
	int num;
	int adder;
} threadHandler;

void *addingNums(void* th)
{
	threadHandler* data = (threadHandler*)th;

	int i;
	for(i = 0; i < data->adder; i++)
	{
		data->num += 1;
	}
}

int main(int args, string argv[])
{
	threadHandler data[2];
	pthread_t thread[2];

	data[0].num = 0;
	data[0].adder = 10;
	data[1].num = 0;
	data[1].adder = 100000;

	int i;
	for(i = 0; i < 2; i++)
	{
		pthread_create(&thread[i], NULL, addingNums, &data[i]);
	}

	for(i = 0; i < 2; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	for(i = 0; i < 2; i++)
	{
		printf("thread %d: %d\n", i, data[i].num);
	}

	return(0);
}
