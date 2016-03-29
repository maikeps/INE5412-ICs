#include <iostream>
#include <pthread.h>


using namespace std;

pthread_mutex_t mymutex;

void *inc_(void *void_ptr)
{
	/* increment x to 100 */
	int *ptr = (int *)void_ptr;
	int i=0;
	for (; i<100; i++) 
	{
		/* enter critical region */
		pthread_mutex_lock(&mymutex);
		++(*ptr);
		/* leave critical region */
		pthread_mutex_unlock(&mymutex);
	}
	cout << "increment finished" << endl;
	return NULL;
}

void *dec_(void *void_ptr)
{
    /* decrement x to 100 */
    int *ptr = (int *)void_ptr;
	int i=0;
	for (; i<100; i++)
	{
		/* enter critical region */
		pthread_mutex_lock(&mymutex);
		--(*ptr);
		/* leave critical region */
		pthread_mutex_unlock(&mymutex);
	}        
    cout << "decrement finished" << endl;
    return NULL;
}


int main()
{
	int x = 0;
	cout << "x: " << x << endl;

	pthread_t inc_thread, dec_thread;
	/* init mutexex */
	/*
	 * args in order:
	 * mutex to be initialized
	 * mutex attributes(default attributes if NULL)
	 */
	pthread_mutex_init(&mymutex, NULL);

    /* create a first thread which executes inc_(&x) */
    /* 
     * args in order:
     * thread to be created
     * thread attributes(default attributes if NULL)
     * start routine(routine to be called on thread creation)
     * args for the above routine
     */
    pthread_create(&inc_thread, NULL, inc_, &x);

	/* create a second thread which executes dec_(&x) */
	pthread_create(&dec_thread, NULL, dec_, &x);

    /* wait for the first thread to finish */
    /*
	 * args in order:
	 * thread to wait for terminate
	 * thread return value
     */
    pthread_join(inc_thread, NULL);

	/* wait for the second thread to finish */
	pthread_join(dec_thread, NULL);

	/* destroy miutex */
	pthread_mutex_destroy(&mymutex);

	cout << "x: " << x << endl;
	return 0;
}
