#include <stdio.h>
#include <fcntl.h>   // 包含 O_CREAT 和其他标志
#include <sys/stat.h> // 包含 S_IRWXU 等权限模式
#include <unistd.h>
#include <errno.h>    // 用于处理错误
#include <time.h>
#include <asm/unistd_64.h> // 包含系统调用号 #define __NR_open 2

// int open(const char *pathname, int flags, mode_t mode); // open函数原型
int main(){
    const char *file_path = "comp1.txt";
    int flags = O_CREAT ;     // 如果不存在则创建
    mode_t mode = S_IRUSR | S_IWUSR;    // 用户读写执行权限
    long ret_val; // 存储系统调用的返回值
    struct timespec start, end;
    long diff;

    for (int i = 0; i < 100000; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        asm volatile(
            "syscall"
            : "=a"(ret_val)               // 输出: 将 rax 寄存器的值赋给 ret_val
            : "a"(__NR_open),             // 系统调用号 __NR_open 赋给 rax 寄存器
            "D"(file_path),             // 第一个参数pathname 放入 rdi
            "S"(flags),                 // 第二个参数flags 放入 rsi
            "d"(mode)                   // 第三个参数mode 放入 rdx
            : "rcx", "r11" 
        );
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff += (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec); // 转换为ns
    }
    
    diff /= 100000; // 取平均值
    printf("assembly open()   average time: %ld ns\n", diff);
    return 0;
}