/* Short test program to test the pthread_setaffinity_np
* (which sets the affinity of threads to processors).
* Compile: gcc pthread_setaffinity_np_test.c -o pthread_setaffinity_np_test -lm -lpthread
* Usage: ./pthread_setaffinity_test
*
* Open a "top"-window at the same time and see all the work
* being done on CPU 0 first and after a short wait on CPU 1.
* Repeat with different numbers to make sure, it is not a
* coincidence.
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

cpu_set_t cpuset,cpuget;
double total;
double wastetime1,wastetime2;
double waste_time(long n)
{
	double res = 0;
	long i = 0;
	while (i <n * 100000000) {
		i++;
		res += sqrt(i);
	}
	return res;
}
double waste_time2(long n)
{
	double res = 0;
	long i = 0;
	for (i=n*100000000; i<n * 200000000;i++) {
		res += sqrt(i);
	}
	return res;
}
void *thread_func(void *param)
{   
	/* bind process to processor 0 */
	if ( pthread_setaffinity_np( pthread_self() , sizeof(cpu_set_t), &cpuset ) !=0 ) {
		perror("pthread_setaffinity_np");
	}  
	printf("fun1 Core 0 is running!\n");
	/* waste some time so the work is visible with "top" */
	wastetime1=waste_time(5);
	pthread_exit(NULL);
}
void *thread_func2(void *param)
{   
	/* bind process to processor 0 */
	if ( pthread_setaffinity_np( pthread_self() , sizeof(cpu_set_t), &cpuset ) !=0 ) {
		perror("pthread_setaffinity_np");
	}  
	printf("fun2 Core 0 is running!\n");
	/* waste some time so the work is visible with "top" */
	wastetime2=waste_time2(5);
	pthread_exit(NULL);
}
 
int main(int argc, char *argv[])
{ 
	long clocktime=0;
	int num = sysconf(_SC_NPROCESSORS_CONF);
   	printf("system has %d processor(s)\n", num);
	pthread_t my_thread;
	pthread_t my_thread2;
	time_t startwtime, endwtime;
	CPU_ZERO(&cpuset);//This macro initializes the CPU set set to be the empty set.
	CPU_SET(0, &cpuset); /* cpu 0 is in cpuset now */
	startwtime = time (NULL); 
	if (pthread_create(&my_thread, NULL, thread_func,NULL) != 0) {
		perror("pthread_create");
	}
	if (pthread_create(&my_thread2, NULL, thread_func2,NULL) != 0) {
		perror("pthread_create");
	}
	pthread_join(my_thread,NULL);
	endwtime = time (NULL);
	clocktime= (endwtime - startwtime);
	pthread_join(my_thread2,NULL);
	printf("result: %f\n",(wastetime1+wastetime2));
	printf ("wall clock time = %ld\n", clocktime);
	return 0;
}



