gcc ./getpid_assembly.c -o getpid_assembly
gcc ./getpid_glibc.c -o getpid_glibc
gcc ./getpid_syscall.c -o getpid_syscall
# ./getpid_glibc && ./getpid_syscall && ./getpid_assembly