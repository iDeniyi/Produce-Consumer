// the queue mainteined by the parent process
// youtube video that helped with implementing the queue: https://www.youtube.com/watch?v=oyX30WVuEos
// linear vs circular queue: https://www.geeksforgeeks.org/difference-between-linear-queue-and-circular-queue/

#include "buffer.hpp"

void init_buffer(buffer* buf, int max_size)
{
    buf->size = max_size;
    buf->values = new int[max_size];
    buf->head = -1;
    buf->tail = -1;
}

void destroy_buffer(buffer* buf)
{
    delete [] buf->values;
}

bool is_empty_buffer(buffer* buf)
{
    if (buf->tail  == -1 && buf->head == -1)
        return true;
    else
        return false;
}

bool is_full_buffer(buffer* buf)
{
    if ((buf->tail + 1) % buf->size == buf->head)
        return true;
    else
        return false;
}

bool enqueue(buffer *buf, int value)
{
    if (is_full_buffer(buf))
    {
        return false;
    }
    else if (is_empty_buffer(buf)) {
        buf->tail = 0;
        buf->head = 0;
        buf->values[buf->tail] = value;
    } 
    else 
    {
        buf->tail = (buf->tail + 1) % buf->size;
        buf->values[buf->tail] = value;
    }
    return true;
}


int dequeue(buffer* buf)
{
    int result;
    if (is_empty_buffer(buf))
    {
        return 0;
    }
    else if (buf->tail == buf->head) 
    {
        result = buf->values[buf->tail];
        buf->values[buf->head] = 0;
        buf->tail = -1;
        buf->head = -1;
        return result;
    }
    else
    {
        result = buf->values[buf->head];
        buf->values[buf->head] = 0;
        buf->head = (buf->head + 1) % buf->size;
        return result;
    }
}

void display(buffer *buf) {
    cout << "All values in the Queue are - \n";
    for (int i = 0; i < buf->size; i++) {
      cout << buf->values[i] << "  ";
    }
    cout << endl;
}







