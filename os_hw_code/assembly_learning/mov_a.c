#include <stdio.h>

// TODO: 特定寄存器约束
// * "a": 强制使用 %eax 寄存器
// * "b": 强制使用 %ebx 寄存器
// * "c": 强制使用 %ecx 寄存器
// * "d": 强制使用 %edx 寄存器

// TODO: 意义
// 有些指令天生就只能在特定的寄存器上工作。一个经典的例子是 mul（无符号乘法）指令。
// 它会把 %eax 里的值和你指定的另一个操作数相乘，然后把结果的一个部分存回 %eax，另一部分存到 %edx。
// 如果我们想用 mul 指令，就没法用灵活的 "r" 约束了，我们必须把其中一个输入变量“锁”在 %eax 上，并且准备从 %eax 和 %edx 中读取结果。
// 所以，特定寄存器约束给了我们精准的控制权，但代价是牺牲了编译器的优化空间。


int result;
int main(int argc, char **argv)
{
    asm volatile(
        "movl $5,%0 "  
        : "=a" (result) // 输出部分： 把 eax 寄存器的值输出到 result 变量
    );
// * 当你在 asm() 中使用了输入/输出部分（就是冒号后面的部分）后，
// * 编译器就不再允许你在汇编指令里直接写寄存器的名字（比如 %eax）了。

    printf("A mov was executed\n");
    printf("The value from %%eax is: %d\n", result);
    return 0;
}

// 一般情况下，C 编译器会自己决定哪个变量在什么时候应该放在哪个寄存器或内存里，以便最大化程序的运行效率。
// "=a" 则约束编译器必须把 result 变量放到 %eax 寄存器里