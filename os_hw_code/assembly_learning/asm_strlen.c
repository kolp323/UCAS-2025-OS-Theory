#include <stdio.h>

int asm_strlen(const char* str){
    int len;
    char *p;
    // ! 一旦我们使用了输入输出列表，就应该完全交给编译器去管理寄存器。
    // !我们必须用占位符 %0 来代替所有用到 len 的地方（而不是 %%eax）
    asm volatile(
        "xorl %0, %0\n\t" // 1. 使用异或高效清零
        // "movl $0, %0;" 
        // "movl %1, %2;"    // %1 input:str, %2 存放字符指针
        "jmp .Lcheck\n\t" // 2. 跳到检查点
        ".Lloop_start:\n\t"
        "   incl %0\n\t"
        "   incl %1\n\t"
        ".Lcheck:\n\t" 
        "   cmpb $0, (%1)\n\t" // 3. 检查当前指针指向字符是否为'\0'
        "   jne .Lloop_start;" // 4. 不是'\0'则计入有效字符
        : "=a"(len)
        : "d"(str) // 明确使用 "d" 约束，以防止编译器将指针放入eax（实际几乎不可能）
        : "cc"
    );
    return len;
}

int main(int argc, char** argv) {
    const char *str = "114514";
    int str_len = asm_strlen(str);
    printf("length of %s is: %d", str, str_len);
    return 0;
}