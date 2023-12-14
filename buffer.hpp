#ifndef BUFFER_H
#define BUFFER_H 

#include <iostream>

using namespace std;

typedef struct 
{
    int *values;
    int head, tail, size;
} buffer;

void init_buffer(buffer* buf, int max_size);
void destroy_buffer(buffer* buf);
bool is_empty_buffer(buffer* buf);
bool is_full_buffer(buffer* buf);
bool enqueue(buffer *buf, int value);
int dequeue(buffer* buf);
void display(buffer *buf);


#endif