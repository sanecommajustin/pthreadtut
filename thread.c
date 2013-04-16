#include<stdio.h>			//If you don't know this include, you shouldn't be here.
#include<pthread.h>		//For threading. You need to compile with -lpthread

//reference char* as a simple string.
typedef char * string;

/*
 * To start out this program will run 2 threads that, each,
 * take a number and then adds 1 to it a specified number of times
 * using a for loop.
 */


//	In threading you need to think of the thread as just a function
//		that runs in a seperate thread than the original.
//
//	We can create a function that gets called upon the start of a
//		new posix thread.
//
//	pthread_create(will be the function that we use to launch a new thread.
//		The issue with this function is that it only allows us to pass one
//		variable to the function. Therefor we will need to create a struct 
//		If we wish to pass in multiple variables.
//
// This struct takes in a variable that we wish to start at (num).
//		As well as the number to add too it.
//		We will also give it an id to print as well.
typedef struct _threadHandler
{
	int id;
	int num;
	int adder;
} threadHandler;

//	This is the function that we will tell pthread_create to run.
//		It's job will just be to add adder to num one at a time.
//
// It returns a "void *" which is just c's way of saying that it returns an 
//		object that can be cast as anything.
//
// It takes in a parameter that is also "void *", 
//		so again it can be cast to whatever it needs to be
void *addingNums(void* th)
{
	//Here is the cast. We need to convert the "void *" to the struct as a pointer.
	//Trust me, do it this way it's a lot less wordy.
	threadHandler* data = (threadHandler*)th;

	//The algorithm adds the numbers together.
	int i;
	for(i = 0; i < data->adder; i++)
	{
		data->num += 1;
	}

	//	Print out which thread we are as well as the value of num.
	//		This will be used to show that the thread the finishes first prints first
	//		and that both run at the same time. Even though the stuct with
	//		adder = 10000000 was started first, the struct with adder = 1
	//		did not need to wait for the other one to process before it ran.
	printf("thread %d: done with num = %d\n", data->id, data->num);
}

//It all begins here
int main(int args, string argv[])
{
	threadHandler data[2];		//Create an array of structs to pass different data to different threads
	pthread_t thread[2];			//Create an array of threads with the max total of threads you wish to run.

	//We will be creating 2 threads so we will be needing to create 2 sets of data

	data[0].num = 0;
	data[0].adder = 10000000;
	data[1].num = 0;
	data[1].adder = 1;

	int i;
	for(i = 0; i < 2; i++)
	{
		data[i].id = i;	//Give the data an id.

		//pthread_create takes in 4 variables
		// Parameter 1
		//		A reference to a pthread_t struct. We created an array of these so we
		//			need to pass a reference to one of these.
		//
		// Parameter 2
		//		This is thread settings. Passing in NULL is just saying use default settings
		//
		//	Parameter 3
		//		The function to process the data with.
		//
		// Parameter 4
		//		A reference to the data to be passed to the function. (One of the structs we made)
		pthread_create(&thread[i], NULL, addingNums, &data[i]);
	}

	//This is where the program will sit and wait for all the threads to combine.
	for(i = 0; i < 2; i++)
	{
		//pthread_join waits for the specified thread function to return.
		//The loop then will go to the next thread to get that info.
		//	Parameter 1
		//		The thread to wait for. Again we have an array of these.
		//
		// Parameter 2
		//		The return data that the "void *" will pass back to from the function.
		//		you can have an int pass back with an error code and instead of NULL you just say &myIntVariable.
		pthread_join(thread[i], NULL);
	}
	
	printf("\nHere is the numbers in the struct order.\n");

	for(i = 0; i < 2; i++)
	{
		printf("Object %d: %d\n", i, data[i].num);
	}

	printf("Notice that the threads printed in opposite order.\n");
	printf("It's because the threads printed the one that took the least amount of time first,\n");
	printf("compared to object order where data[0] will always print first in the for loop designed\n");

	return(0);
}
