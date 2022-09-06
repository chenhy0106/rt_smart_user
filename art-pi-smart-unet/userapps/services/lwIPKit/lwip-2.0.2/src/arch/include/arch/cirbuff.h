#ifndef CIRBUFF_H_
#define CIRBUFF_H_

#include <rtdef.h>

struct cirbuff
{
    rt_ubase_t *buff;

    int input_ptr;
    int output_ptr;
    int len;
};

struct cirbuff * buffer_new(int len);
void buffer_del(struct cirbuff *cb);
int buffer_full(struct cirbuff *cb);
int buffer_empty(struct cirbuff *cb);
int buffer_enqueue(struct cirbuff *cb, rt_ubase_t data);
int buffer_dequeue(struct cirbuff *cb, rt_ubase_t *data);

#endif