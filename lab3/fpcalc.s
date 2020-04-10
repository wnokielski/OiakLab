SYSEXIT = 1
EXIT_SUCCESS = 0

.code32

.data
controlWord: .word 0
l1: .float 1.234567
l2: .float 697.250498
l3: .float -19.042392
trash: .double 0

finit                       #przywrocenie FPU "do stanu fabrycznego"
call setPrecisionSingle
call setRoundNearest

.global _start
_start:

#dodawanie
fld l1                      #zaladowanie pierwszej liczby
fld l2                      #zaladowanie drugiej liczby
fadd %st(1), %st(0) 
fstp trash                  #zdjecie liczb ze stosu i odlozenie
fstp trash                  #ich do "smietnika"

#odejmowanie
fld l1
fld l2
fsub %st(1), %st(0)
fstp trash
fstp trash

#mnozenie
fld l1
fld l2
fmul %st(1), %st(0)
fstp trash
fstp trash


#dzielenie
fld l1
fld l2
fdiv %st(1), %st(0)
fstp trash
fstp trash

#wyjatki

#-0
fld l3
fldz
fdiv %st(1)
fstp trash
fstp trash

#+0
fld l1
fldz
fdiv %st(1)
fstp trash
fstp trash

#NaN
fldz
fldz
fdiv %st(1)
fstp trash
fstp trash
	
#+INF
fldz
fld l1
fdiv %st(1)
fstp trash
fstp trash

#-INF
fldz
fld l3
fdiv %st(1)
fstp trash
fstp trash

jmp quit

setPrecisionSingle:
fstcw controlWord          #zapisanie slowa kontrolnego do pamieci pod adres controlWord
mov controlWord, %edx       #zapisanie w rejestrze EDX slowa kontrolnego
and $0b1111110011111111,%edx    #ustawiamy bit 8 i 9 (liczac od 0) aby ustawic precyzje
mov %edx, controlWord     #zapisanie nowego slowa kontrolnego do pamieci
fldcw controlWord          #zaladowanie nowego slowa kontolnego do FPU
ret

setPrecisionDouble:
fstcw controlWord          
mov controlWord, %edx       
and $0b1111111011111111,%edx   
mov %edx, controlWord    
fldcw controlWord          
ret

setRoundCut:
fstcw controlWord
mov controlWord, %edx
and $0b1111111111111111, %edx
mov %edx, controlWord
fldcw controlWord
ret

setRoundUp:
fstcw controlWord
mov controlWord, %edx
and $0b1111101111111111, %edx
mov %edx, controlWord
fldcw controlWord
ret

setRoundDown:
fstcw controlWord
mov controlWord, %edx
and $0b1111011111111111, %edx
mov %edx, controlWord
fldcw controlWord
ret

setRoundNearest:
fstcw controlWord
mov controlWord, %edx
and $0b1111001111111111, %edx
mov %edx, controlWord
fldcw controlWord
ret

quit:
mov $SYSEXIT, %eax
mov $EXIT_SUCCESS, %ebx
int $0x80
