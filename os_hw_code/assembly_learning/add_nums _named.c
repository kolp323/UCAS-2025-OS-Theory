#include <stdio.h>

int add_numbers(int a, int b) {
    int sum;
    asm volatile(
        "movl %[val_a], %[total];"
        "addl %[val_b], %[total];"
        : [total]"=r"(sum)
        : [val_a]"r"(a), [val_b]"r"(b)
        : "cc" // 告诉编译器，这段汇编代码会修改 EFLAGS Register 状态寄存器
    );
    return sum;
}

int main(int argc, char** argv) {
    int result = add_numbers(50, 75);
    printf("The result from the function is: %d\n", result); // 应该输出 125
    return 0;
}