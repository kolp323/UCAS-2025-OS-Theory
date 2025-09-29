#include <stdio.h>


int main(int argc, char** argv) {
    asm("nop");
    printf("A nop was executed");

    return 0;
}