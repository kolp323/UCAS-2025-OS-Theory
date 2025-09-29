#include <stdio.h>

// * 通用寄存器约束 r: 可以使用任何一个通用的CPU寄存器（比如 %eax, %ebx, %ecx 等）来存放这个变量
int main(int argc, char** argv) {
    int a = 10;
    int b = 20;
    int sum;

    asm volatile(
        "movl %1, %0; addl %2, %0"
        : "=r"(sum)      // 输出部分：为 sum 找一个【任意】通用寄存器，=表示这是一个写操作
        : "r"(a), "r"(b) // 输入部分：把 a 和 b 变量的值传入汇编代码
    );

    printf("The sum of %d and %d is: %d\n", a, b, sum);
    return 0;
}