#include <stdio.h>

int main(int argc, char **argv)
{
    asm volatile(
        "movl $5,%eax "  // 操作 源,目标  // 操作与操作数用空格隔开，源和目标用逗号隔开
    );

    printf("A mov was executed \n");
    return 0;
}