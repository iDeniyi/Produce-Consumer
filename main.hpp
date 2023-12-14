#include <string.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <semaphore.h>
#include <pthread.h>


#include "summary_details.hpp"
#include "buffer.hpp"

using namespace std;


void* consumer(void * arg);
void producer();

extern string line;
extern string filename;
extern int nthreads;
extern int prodcon_buf_length;
extern ofstream out_file;
extern sem_t sem_empty;
extern sem_t sem_full;
extern int buf_size;
extern pthread_mutex_t file_mutex;
extern pthread_mutex_t buffer_mutex;
extern summary_dets log_details;
extern buffer prodcon_buf;
extern bool eof_reached;
extern void Trans( int n );
extern void Sleep( int n );
extern pthread_cond_t emp;
extern pthread_cond_t full;



