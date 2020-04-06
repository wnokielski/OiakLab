SYSEXIT = 1
EXIT_SUCCESS = 0

.global _start
_start:

mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
