SYSEXIT = 1
EXIT_SUCCESS = 0
SYSWRITE = 4
SYSREAD = 3
STDOUT = 1
STDIN = 0

.data
buf: .ascii "     "
buf_len = . - buf

str: .ascii "testo"
str_len = . - str


.text
msg: .ascii "Wpisz tekst (5): \n"
msg_len = . - msg

same: .ascii "Tekst sie zgadza!\n "
same_len = . - same

diff: .ascii "Tekst rozni sie!\n"
diff_len = . - diff


.global _start
_start:

mov $SYSWRITE, %eax		#wyswietlenie msg
mov $STDOUT, %ebx
mov $msg, %ecx
mov $msg_len, %edx
int $0x80

mov $SYSREAD, %eax		#wczytanie tekstu
mov $STDIN, %ebx
mov $buf, %ecx
mov $buf_len, %edx
int $0x80

mov $0, %edx			#porownywanie w petli
loop:
cmp $str_len, %edx
je thesame
mov buf(,%edx,1), %ah
mov str(,%edx,1), %al
cmp %ah, %al
jne different
inc %edx
jmp loop

thesame:
mov $SYSWRITE, %eax		#teksty takie same
mov $STDOUT, %ebx
mov $same, %ecx
mov $same_len, %edx
int $0x80
jmp end

different:
mov $SYSWRITE, %eax		#teksty rozne
mov $STDOUT, %ebx
mov $diff, %ecx
mov $diff_len, %edx
int $0x80
jmp end


end:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
