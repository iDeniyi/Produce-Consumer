
// USING MUTEX LOCKS AND CONDITIONAL VARIABLES FOR SYNCHRONIZATION
#include "main.hpp"
void* consumer(void * arg)
{
    int* id = (int*) arg;
    while (true)
    {
        // CONSUMER ASKS
        pthread_mutex_lock(&file_mutex);
            print_consumer_asks(&log_details, *id);
        pthread_mutex_unlock(&file_mutex);
            

        pthread_mutex_lock(&buffer_mutex);

            while (is_empty_buffer(&prodcon_buf))
            {
                if (eof_reached)
                {
                    pthread_mutex_unlock(&buffer_mutex);
                    return NULL;
                }
                pthread_cond_wait( &emp, &buffer_mutex );            
            }

            int trans_time = dequeue(&prodcon_buf);
            pthread_mutex_lock(&file_mutex);
                print_consumer_rcvs(&log_details, *id, trans_time);
            pthread_mutex_unlock(&file_mutex);

            // SIGNAL THERE IS EMPTY SLOT IN BUFFER
            pthread_cond_signal( &full );

        pthread_mutex_unlock(&buffer_mutex);

        Trans(trans_time);

        // CONSUMER COMPLETES
        pthread_mutex_lock(&file_mutex);
            print_consumer_completes(&log_details, *id, trans_time);
        pthread_mutex_unlock(&file_mutex);
    }
    return NULL;
}

void producer()
{
    while (getline(cin, line))
    {
        // SLEEP PRODUCER
        if (line[0] == 'S')
        {
            line.erase(0, 1);
            int arg_i = stoi(line);

            pthread_mutex_lock(&file_mutex);
            print_sleep(&log_details, arg_i);
            Sleep(arg_i);
            pthread_mutex_unlock(&file_mutex);
            


            

    
        }
        // ENQUEUE BUFFER WITH WORK
        else if (line[0] == 'T')
        {
            line.erase(0, 1);
            int arg_i = stoi(line);
            
            // BLOCK IF BUFFER IS FULL
            pthread_mutex_lock( &buffer_mutex );
                while( is_full_buffer(&prodcon_buf))
                {
                    pthread_cond_wait( &full, &buffer_mutex );
                }

                enqueue(&prodcon_buf, arg_i);
                pthread_mutex_lock(&file_mutex);
                    print_work(&log_details, arg_i);
                pthread_mutex_unlock(&file_mutex);

                // SIGNAL BUFFER NOT EMPTY
                pthread_cond_signal( &emp );
            pthread_mutex_unlock( &buffer_mutex );
        }
    }
    pthread_mutex_lock(&buffer_mutex);
        eof_reached = true;
        pthread_cond_broadcast(&emp);
        pthread_mutex_lock(&file_mutex);
            print_end(&log_details);
        pthread_mutex_unlock(&file_mutex);
    pthread_mutex_unlock(&buffer_mutex);

} 
