SYSEXIT = 1
EXIT_SUCCESS = 0

.code32

.data
liczba1:
        .long 0x10304008, 0x701100FF, 0x45100020, 0x08570030
len_l1= ((. - liczba1)/4)-1

liczba2:
        .long 0xF040500C, 0x00220026, 0x321000CB, 0x04520031
len_l2= ((. - liczba2)/4)-1

#liczba2:
#        .long 0xA040500C, 0x00220026, 0x321000CB, 0x04520031   
#len_l2= ((. - liczba2)/4)-1

.global _start
_start:

        xor %eax, %eax              #wyzerowanie rejestrow (dla bezpieczenstwa)
        xor %ebx, %ebx
        xor %ecx, %ecx
        xor %edx, %edx
        xor %esi, %esi
        xor %edi, %edi

        clc                         #wyzerowanie flagi przeniesienia

        movl $len_l1, %esi          #zapisanie ilosci longow w liczbie 
        movl $len_l2, %edi          #do rejestrow esi i edi

        adding:
        movl liczba1(,%esi,4), %eax
        movl liczba2(,%edi,4), %edx
        adcl %eax, %edx
        push %edx
        cmp $0, %esi
        je endOfEqualLengthPart
        cmp $0, %edi
        je endOfEqualLengthPart
        dec %esi
        dec %edi
        jmp adding

        endOfEqualLengthPart:        #przechodzimy tutaj, gdy dodalismy juz cyfry
                                        #na liczbie pozycji rownej ilosci cyfr
                                       #w krotszej liczbie
        cmp %esi, %edi               
	je end                       
	jg secondNumberGreater
	jmp firstNumberGreater         

        firstNumberGreater:
        xor %edx, %edx
        dec %esi
        movl liczba1(,%esi,4), %eax
        adcl %eax, %edx
        push %edx
        cmp $0, %esi
        je quit
        jmp firstNumberGreater
        
        secondNumberGreater:
        dec %edi
        xor %edx, %edx
        movl liczba2(,%edi,4), %eax
        adcl %eax, %edx
        push %edx
        cmp $0, %edi   
        je quit
        jmp secondNumberGreater
    
        end:
        movl liczba1(,%esi,4), %eax
        movl liczba2(,%edi,4), %edx
        adcl %eax, %edx
        jc carry
        movl $0, %eax                   #jezeli nie ma przeniesienia
        push %eax                       #to wpisujemy zero "na poczatku liczby"
        jmp quit

        carry:
        movl $1, %eax                   #jezeli jest przeniesienie
        push %eax                       #to wpisujemy 1 "na poczatku liczby"

quit:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
