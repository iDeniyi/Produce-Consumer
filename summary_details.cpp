#include "summary_details.hpp"
#include "main.hpp"
#include <unistd.h>

void init_summary_dets(summary_dets* summ, int num_of_threads)
{
    summ->Q = 0;
    summ->num_threads = num_of_threads;
    summ->trans_jobs = 0;
    summ->num_ask = 0;
    summ->num_recvs = 0;
    summ->num_complete = 0;
    summ->sleep_jobs = 0;
    summ->threads_work_done = new int[num_of_threads];
    summ->total_time = 0;
    for (int i = 0; i < num_of_threads; ++i) 
    {
        summ->threads_work_done[i] = 0;
    }
}

void destroy_summ(summary_dets* summ)
{
    delete [] summ->threads_work_done;
}

void time_calc(summary_dets* summ)
{
    summ->end_time = chrono::steady_clock::now();
    summ->total_time = chrono::duration<double>(summ->end_time - summ->start_time).count();
}

void print_consumer_asks(summary_dets* summ, int id)
{
    summ->num_ask++;
    time_calc(summ);
    out_file << fixed << setprecision(3) << summ->total_time << "\tID=\t" << id << "\t\t\tAsk" << endl;
}

void print_consumer_rcvs(summary_dets* summ, int id, int trans_time)
{
    summ->Q--;
    summ->num_recvs++;
    time_calc(summ);
    out_file << fixed << setprecision(3) << summ->total_time << "\tID=\t" << id << "\tQ=\t" << summ->Q << "\tReceive\t\t" << trans_time << endl;
}

void print_consumer_completes(summary_dets* summ, int id, int trans_time)
{   
    summ->threads_work_done[id-1]++;
    summ->num_complete++;
    time_calc(summ);
    out_file << fixed << setprecision(3) << summ->total_time << "\tID=\t" << id << "\t\t\tComplete\t" << trans_time << endl;
}

void print_sleep(summary_dets* summ, int sleep_time)
{
    summ->sleep_jobs++;
    time_calc(summ);
    out_file << fixed << setprecision(3) << summ->total_time << "\tID=\t0\t\t\tSleep\t\t" << sleep_time << endl;
}

void print_work(summary_dets* summ, int trans_time)
{
    summ->trans_jobs++;
    summ->Q++;
    time_calc(summ);
    out_file << fixed << setprecision(3) << summ->total_time << "\tID=\t0\tQ=\t" << summ->Q << "\tWork\t\t" << trans_time << endl;
}

void print_end(summary_dets* summ)
{
    time_calc(summ);
    out_file << fixed << setprecision(3) << summ->total_time <<  "\tID=\t0\t\t\tEnd" << endl;

}

void print_summary(summary_dets* summ)
{
    out_file << "Summary:" << endl;
    out_file << "\tWork\t\t" << summ->trans_jobs << endl;
    out_file << "\tAsk\t\t\t" << summ->num_ask << endl;
    out_file << "\tReceive\t\t" << summ->num_recvs << endl;
    out_file << "\tComplete\t" << summ->num_complete << endl;
    out_file << "\tSleep\t\t" << summ->sleep_jobs << endl;
    for(int i=0; i < summ->num_threads; i++)
    {
        out_file << "\tThread\t" << i+1 << "\t" << summ->threads_work_done[i] << endl;
    }
    out_file << "Transactions per second:\t"  << summ->trans_jobs/summ->total_time << endl;
}

