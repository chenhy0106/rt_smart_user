#ifndef IPC_SERVICE_H_
#define IPC_SERVICE_H_

#include <channel.h>
#include <rtthread.h>
#include <ueth.h>

rt_err_t ipc_service_init();
void ueth_int_recv(void);
void *ueth_v2p(void * addr);
void *ueth_remap(void * paddr, int type, size_t size);
void ueth_gpioinit(void *gpio, size_t size);
void ueth_init_clock();
void ueth_hw_interrupt_install(int vector, void * param);

#endif