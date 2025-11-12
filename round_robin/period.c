#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        perror("Must give more than 1 argument");
        return -1;
    }
    unsigned i = 0;
    while(1) {
        if (!(i++ % 10000000))
            putc(argv[1][0], stderr);
    }
    return 0;
}