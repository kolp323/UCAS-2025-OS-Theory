#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <asm/unistd_64.h> // 包含系统调用号 #define __NR_getpid 39

// 1.系统调用号: 将系统调用的 ID（即系统调用号）放入 rax 寄存器。
// 2.系统调用参数: 将系统调用的参数依次放入 rdi、rsi、rdx、r10、r8 和 r9 寄存器中。
// 3.触发系统调用: 使用 syscall 指令触发系统调用。
// 4.获取返回值: 系统调用完成后，内核将系统调用的返回值放入 rax 寄存器。

int main(){
    struct timespec start, end;
    long diff = 0;
    pid_t pid;

    for (int i = 0; i < 100000; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        asm volatile(
            "syscall"          // Instruction List
            : "=a"(pid)        // Output: 将rax寄存器的值赋给变量 pid
            : "a"(__NR_getpid) // Input: 将系统调用号 __NR_getpid 赋给 rax 寄存器
            : "rcx", "r11"     // Clobber/Modify: 告诉编译器 syscall 指令会修改 rcx 和 r11，以便它在生成代码时，不会依赖于这两个寄存器在 syscall 执行前的值。
        );
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff += (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec); // 转换为ns
    }
    
    diff /= 100000; // 取平均值
    printf("assembly getpid() average time: %ld ns\n", diff);
    
    return 0;
}
