#include <stdlib.h>

extern void __rt_lib_init(void);
extern int main(int, char**);

void __start(int *args)
{
    int argc;
    char **argv;

    argc = args[0];
    argv = (char**)args[1];
   __rt_lib_init();
    exit(main(argc, argv));
}
