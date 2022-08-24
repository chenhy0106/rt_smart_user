#include <rtdef.h>
#include <stdio.h>

#include <gtimer.h>

// #include <rtthread.h>

uint64_t current_id = -1;

uint64_t before_recv;
uint64_t after_recv;
uint64_t ipc_send; 
uint64_t ipc_recv;
uint64_t memcpy_before;
uint64_t memcpy_after;

uint64_t user_recv;
uint64_t user_reply;

void set_current_id(int id)
{
    current_id = id;
}

int get_current_id()
{
    return current_id;
}

uint64_t get_hdr_counter()
{
    return gtimer_get_current_physical_value();
    // return rt_tick_get();
}

void qua_printvar()
{
    printf("\n\n===================\n");
    printf("iperf @before u_recv: %lld\n", before_recv);
    
    printf("usocket @ipc_send: %lld\n", ipc_send);

    printf("usocket @user_recv: %lld\n", user_recv);
    printf("usocket @user_reply: %lld\n", user_reply);

    printf("usocket @memcpy_before: %lld\n", memcpy_before);
    printf("usocket @memcpy_after: %lld\n", memcpy_after);

    printf("iperf @after u_recv: %lld\n", after_recv);
}