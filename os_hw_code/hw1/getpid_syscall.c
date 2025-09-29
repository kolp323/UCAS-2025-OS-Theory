#include <stdio.h>
#include <unistd.h> // 不加的话，syscall会报warning
#include <sys/syscall.h>
#include <time.h>

int main()
{
    struct timespec start, end;
    long diff;

    for (int i = 0; i < 100000; i++)
    {
        clock_gettime(CLOCK_MONOTONIC, &start);
        pid_t pid = syscall(SYS_getpid); // 通过 syscall 调用
        clock_gettime(CLOCK_MONOTONIC, &end);
        diff += (end.tv_sec - start.tv_sec) * 1000000000L + (end.tv_nsec - start.tv_nsec); // 转换为ns
    }
    
    diff /= 100000; // 取平均值
    printf("syscall  getpid() average time: %ld ns\n", diff);
    return 0;
}
