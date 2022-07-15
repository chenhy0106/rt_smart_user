.syntax unified
.text

/*
int syscall(int nr, ...)
*/
.global syscall
.type syscall, %function
syscall:
	push {r4-r7, lr}
	mov r7, r0
	mov r0, r1
	mov r1, r2
	mov r2, r3
	add r6, sp,#20
	ldmia r6,{r3-r5}
	svc 0
	pop {r4-r7, lr}
    bx lr

