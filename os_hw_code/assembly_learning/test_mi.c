#include <stdio.h>


int main(int argc, char** argv) {
// TODO: 内存约束 m: 告诉编译器不要把这个变量加载到寄存器里，汇编代码会直接通过内存地址来操作它
    // ex: 在内存中给一个变量加一
    int counter = 10;
    asm volatile(
        "incl %0"  // 自增指令
        : "+m"(counter) // 输出部分：告诉编译器 counter 变量会被读写
        //! + 表示这个操作数既是输入也是输出（我们先读取它的旧值，再写入新值）
    );
    printf("counter: %d\n", counter);

    // TODO: 立即数约束 i: 将一个常量直接作为汇编指令的一部分，而不是先把它加载到寄存器里
    int x = 10;
    asm volatile(
        "addl %1, %0" // ! 操作数是从输出开始，从 0 计数的, 所以 %0 是 x, %1 是 5
        : "+r" (x) // x 可在任意一个寄存器中，可读可写
        : "i" (5) // 5 是一个立即数常量
    );
    printf("x: %d\n", x);
    return 0;
}