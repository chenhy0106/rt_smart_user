#include <rtdef.h>
#include <stdio.h>

rt_tick_t before_recv;
rt_tick_t after_recv;
rt_tick_t ipc_send; 
rt_tick_t ipc_recv;
rt_tick_t memcpy_before;
rt_tick_t memcpy_after;

void qua_printvar()
{
    printf("\n\n===================\n");
    printf("iperf @before u_recv: %d\n", before_recv);
    
    printf("usocket @ipc_send: %d\n", ipc_send);
    printf("usocket @ipc_recv: %d\n", ipc_recv);

    printf("usocket @memcpy_before: %d\n", memcpy_before);
    printf("usocket @memcpy_after: %d\n", memcpy_after);

    printf("iperf @after u_recv: %d\n", after_recv);
}