#include <stdio.h>

int a = 2;
int b = 3;
int res = 0;
int main(int argc, char **argv)
{
    // ! 两个百分号 %% 表示一个寄存器。这是为了和变量占位符 %0, %1 等区分开
    asm volatile(
        "movl %1, %%eax;"  // 把 a 的值放到 eax
        "mull %2"
        : "=r"(res)
        : "r"(a), "r"(b)          // 输入部分：把 a 变量的值传入汇编代码

    );
    printf("Res is %d \n", res);
    return 0;
}