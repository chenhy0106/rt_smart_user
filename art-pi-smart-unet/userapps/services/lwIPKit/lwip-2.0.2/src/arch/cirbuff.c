#include "arch/cirbuff.h"
#include <rtthread.h>

struct cirbuff * buffer_new(int len)
{
    struct cirbuff * new_cb = (struct cirbuff *)rt_malloc(sizeof(struct cirbuff));
    new_cb->input_ptr = 0;
    new_cb->output_ptr = 0;
    new_cb->buff = (rt_ubase_t *)rt_malloc(sizeof(rt_ubase_t) * len);
    rt_memset(new_cb->buff, 0, sizeof(rt_ubase_t) * len);
    new_cb->len = len;
    
    return new_cb;
}

void buffer_del(struct cirbuff *cb)
{
    rt_free(cb->buff);
    rt_free(cb);
}

int buffer_full(struct cirbuff *cb)
{
    return cb->output_ptr == ((cb->input_ptr + 1) % cb->len);
}

int buffer_empty(struct cirbuff *cb)
{
    return cb->input_ptr == cb->output_ptr;
}

int buffer_enqueue(struct cirbuff *cb, rt_ubase_t data)
{
    if (buffer_full(cb))
    {
        return -1;
    }

    cb->buff[cb->input_ptr] = data;
    cb->input_ptr = (cb->input_ptr + 1) % cb->len;

    return 0;
}

int buffer_dequeue(struct cirbuff *cb, rt_ubase_t *data)
{
    if (buffer_empty(cb))
    {
        return -1;
    }

    *data = cb->buff[cb->output_ptr];
    cb->output_ptr = (cb->output_ptr + 1) % cb->len;

    return 0;
}
