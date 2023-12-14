#include "main.hpp"


summary_dets log_details;
buffer prodcon_buf;

string filename;
int nthreads;
int prodcon_buf_length;
ofstream out_file;
sem_t sem_empty;
sem_t sem_full;
int buf_size;
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t buffer_mutex = PTHREAD_MUTEX_INITIALIZER;
bool eof_reached = false;
string line;
void Trans( int n );
void Sleep( int n );
pthread_cond_t emp = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;


int main(int argc, char *argv[])
{
    // HANDLE COMMAND LINE ARGUMENTS
    if ( argc < 2 || argc > 3)
    {
        printf("No command line arguments or too many arguments!\n");
        exit(-1);
    }
    else
    {
        nthreads = atoi(argv[1]);
        if (argc == 2)
        {
            filename = "prodcon.log";
        }
        else if (argc == 3)
        {
            filename =  "prodcon." + to_string(atoi(argv[2])) + ".log";
        }
    }
    // CREATE FILE
    out_file.open(filename);
    if(!out_file.is_open())
    {
        perror("Unable to create file.\n");
        exit(-1);
    }

    // INITIALIZE SEMAPHORE, BUFFER, MUTEX...
    buf_size = 2 * nthreads;
    sem_init(&sem_empty, 0, buf_size);
    sem_init(&sem_full, 0, 0);

    pthread_t threads_id[nthreads];
    int custom_thread_id[nthreads];
    for (int i=0; i < nthreads; i++)
    {
        custom_thread_id[i] = i+1;
    }

    init_summary_dets(&log_details, nthreads);
    init_buffer(&prodcon_buf, buf_size);


    log_details.start_time = chrono::steady_clock::now();       // START TIME
    
    // CREATE CONSUMERS
    for (int i=0; i<nthreads; i++)
    {
        // https://www.unix.com/programming/81931-creating-array-hold-posix-thread-ids-only-dynamic-array-works.html
        if (pthread_create(&(threads_id[i]), NULL, consumer, (void*)&custom_thread_id[i]) != 0)
        {
            perror("pthread_create");
            exit(-1);
        }
    }
    // PRODUCER THREAD
    producer();
    for (int i=0; i<nthreads; i++)
    {
        if (pthread_join(threads_id[i], NULL) == -1)
        {
            perror("pthread_join");
            exit(-1);
        };
    }
    print_summary(&log_details);
    destroy_buffer(&prodcon_buf);
    destroy_summ(&log_details);
    out_file.close();
    return 0;
}
