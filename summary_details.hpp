#ifndef SUMMARY_H
#define SUMMARY_H 

#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>




using namespace std;

typedef struct 
{
    int num_threads, trans_jobs, num_ask, num_recvs, num_complete, sleep_jobs, Q;
    int *threads_work_done;
    chrono::time_point<std::chrono::steady_clock> start_time, end_time; 
    double total_time;
} summary_dets;


void time_calc(summary_dets* summ);
void print_end(summary_dets* summ);
void print_sleep(summary_dets* summ, int sleep_time);
void print_work(summary_dets* summ, int trans_time);
void print_consumer_asks(summary_dets* summ, int id);
void print_consumer_rcvs(summary_dets* summ, int id, int trans_time);
void print_consumer_completes(summary_dets* summ, int id, int trans_time);
void init_summary_dets(summary_dets* summ, int num_of_threads);
void destroy_summ(summary_dets* summ);
void print_summary(summary_dets* summ);

#endif