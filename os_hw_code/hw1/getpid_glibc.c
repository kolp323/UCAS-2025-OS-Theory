#include <stdio.h>
#include <unistd.h> // 包含POSIX标准定义的unix类系统定义符号常量和函数
#include <time.h>   // 包含计时函数

// strace timespec{
//  time_t tv_sec;
//  long tv_nsec;
// }
int main() {
    struct timespec start, end;
    long diff;
    // 重复调用10000次取平均值
    for (int i = 0; i < 100000; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        pid_t pid = getpid(); // 直接调用 glibc 库函数
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff += (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec); // 转换为ns
    }

    diff /= 100000; // 取平均值
    printf("glibc    getpid() average time: %ld ns\n", diff);
    return 0;
}
