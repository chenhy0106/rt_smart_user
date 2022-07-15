#include <stdlib.h>

extern int main(int, char **);

void __main(int *args)
{
    int argc;
    char **argv;

    argc = args[0];
    argv = (char **)args[1];

    exit(main(argc, argv));
}
