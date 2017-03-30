#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <sys/sysinfo.h>
void a(long long n);
static long int count;
static pthread_mutex_t mutex;

int main( int arge , char *argv[] )
{
	//long int toss = atoi( argv[1] );
	long long toss;
	//sscanf(argv[1],"%lld", &toss);
	toss = 9999999999;
	long long  core = get_nprocs();
	long long mod = toss % core;
	pthread_t T_P[core];
	int i;
	for( i = 0 ; i < core ; i++ ){
		if( i == 0 )
			pthread_create( &T_P[i], NULL , (void*)a ,  (long long*)(toss/core + mod) );
		else
			pthread_create( &T_P[i], NULL , (void*)a ,  (long long*)(toss/core) );
	}
	for( i = 0 ; i < core ; i++ ){
		pthread_join( T_P[i] , NULL);
	}
	printf("%3.12f\n",4.0 * count / toss);
	return 0;

}
void a(long long n)
{
	//printf("%d\n",n);
	double x, y;
	long long i;
	unsigned int a;
	a = time(NULL);
	long long c = 0;
	for( i = 0; i < n ; i++ ){
		x = rand_r(&a)/((double)RAND_MAX+1);
		y = rand_r(&a)/((double)RAND_MAX+1);
		if( x*x + y*y < 1 ){
			c++;
		}
	}
	pthread_mutex_lock(&mutex);
	count += c;
	pthread_mutex_unlock(&mutex);
}

