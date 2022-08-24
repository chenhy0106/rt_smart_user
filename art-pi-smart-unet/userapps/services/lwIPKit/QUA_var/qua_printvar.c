#include <rtdef.h>
#include <stdio.h>
#include <rtthread.h>

#define __get_cp64(cp, op1, Rt, CRm) \
    __asm__ volatile("MRRC p" # cp ", " # op1 ", %Q0, %R0, c" # CRm  : "=r" (Rt) : : "memory" )

uint64_t ipc_recv = 0;
uint64_t internal_process_end = 0;

uint64_t get_hdr_counter()
{
    // return gtimer_get_current_physical_value();

    // return rt_tick_get();

    rt_uint64_t result;
    __get_cp64(15, 0, result, 14);
    return result;
}

void qua_printvar()
{
    printf("\n\n===================\n");

    printf("main @ipc_recv: %lld\n", ipc_recv);
    printf("main @internal_process_end: %lld\n", internal_process_end);
}