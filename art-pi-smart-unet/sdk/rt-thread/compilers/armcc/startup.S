; Stack Configuration
;  Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

; Heap Configuration
;  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>

Heap_Size       EQU     0x00000400

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, CODE, READONLY

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __start
                IMPORT |Image$$data$$Base|

                ;get and set stack.
                LDR     R3, stack_Mem_offset
                LDR     R2, data_offset
                SUB     R3, R3, R2
				SUB     R3, #8
                ADD     R3, R3, R9
				BIC     R3, R3, #7
                MOV     SP, R3

                ; jump to __start
                LDR     R1, Entry_offset ; this is PI,
                ADR     R2, Entry_offset ; this is PI,
                ADD     R1, R1, R2
                BX      R1

                ALIGN

Entry_offset    DCD     __start - . ; this is PI
                ENDP

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory

                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                ;R0 heap base   R1 stack base (top-address)
                ;R2 heap limit  R3 stack limit (low-address)

                ; get real data offset to R1.
                LDR     R0, load_offset
                ADR     R1, load_offset
                ADD     R1, R0, R1
                SUB     R1, R1, #0x01       ; thumb-2 function is odd address.
                SUB     R1, R9, R1

                ; get heap base to R0
                LDR     R0, Heap_Mem_offset
                ADR     R2, Heap_Mem_offset
                ADD     R0, R0, R2
                ADD     R0, R0, R1

                ; get stack limit (low-address) to R3
                LDR     R3, stack_Mem_offset
                ADR     R2, stack_Mem_offset
                ADD     R3, R3, R2
                ADD     R3, R3, R1

                ADD     R1, R3, #Stack_Size
                ADD     R2, R0, #Heap_Size

                BX      LR

                ALIGN

load_offset         DCD     Reset_Handler - . ; this is PI
Heap_Mem_offset     DCD     Heap_Mem - . ; this is PI
stack_Mem_offset     DCD     Stack_Mem - .; this is PI
data_offset      DCD    |Image$$data$$Base| - .

                ALIGN

                ENDIF


                END
