#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

typedef struct vector{
    long a,b,c,d;
} vector;

#define NUMBERS 2048

vector vec1[NUMBERS/4];    //vectors for SIMD instructions
vector vec2[NUMBERS/4];

long num1[NUMBERS];  //tabs with numbers for SISD instructions
long num2[NUMBERS];

double t; //auxiliary variable for time measure
double tSum = 0;

double averageTimeAdd;
double averageTimeSub;
double averageTimeMul;
double averageTimeDiv;

long randomNumber(){
    // return (rand() * 1235 + rand() * 764 + rand() * 943) % INT_MAX;
    return rand() % 1000000;
}

void fillVector(vector x[]){
    for(int i=0; i<NUMBERS/4; i++){
        x[i].a = randomNumber();
        x[i].b = randomNumber();
        x[i].c = randomNumber();
        x[i].d = randomNumber();
    }
}

void fillTab(long x[]){
    for(int i=0; i<NUMBERS; i++){
        x[i] = randomNumber();
    }
}

void SIMDAdd(vector *A, vector *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movups (%%ecx), %%xmm0\n"
        "movups (%%edx), %%xmm1\n"
        "addps %%xmm0, %%xmm1\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx"
    );
}

void SIMDMul(vector *A, vector *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movups (%%ecx), %%xmm0\n"
        "movups (%%edx), %%xmm1\n"
        "mulps %%xmm0, %%xmm1\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx"
    );
}

void SIMDSub(vector *A, vector *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movups (%%ecx), %%xmm0\n"
        "movups (%%edx), %%xmm1\n"
        "subps %%xmm0, %%xmm1\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx"
    );
}

void SIMDDiv(vector *A, vector *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movups (%%ecx), %%xmm0\n"
        "movups (%%edx), %%xmm1\n"
        "divps %%xmm0, %%xmm1\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx"
    );
}

void SISDAdd(long *A, long *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movl (%%ecx), %%eax\n"
        "movl (%%edx), %%ebx\n"
        "add %%eax, %%ebx\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx", "eax", "ebx"
    );
}

void SISDMul(long *A, long *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movl (%%ecx), %%eax\n"
        "movl (%%edx), %%ebx\n"
        "mul %%ebx\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx", "eax", "ebx"
    );
}

void SISDSub(long *A, long *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movl (%%ecx), %%eax\n"
        "movl (%%edx), %%ebx\n"
        "sub %%eax, %%ebx\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx", "eax", "ebx"
    );
}

void SISDDiv(long *A, long *B){
    __asm__("movl %0, %%ecx\n"
        "movl %1, %%edx\n"
        "movl (%%ecx), %%eax\n"
        "movl (%%edx), %%ebx\n"
        "idiv %%ebx\n"
        :
        :"r"(A), "r"(B)
        :"ecx", "edx", "eax", "ebx"
    );
}

int main(){

    FILE *f;

    f = fopen("out.txt", "w");

    srand(time(NULL));

    //fill vectors with random numbers

    fillVector(vec1);
    fillVector(vec2);
    
    //fill tabs with random numbers

    fillTab(num1);
    fillTab(num2);

    //SIMD +

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS/4; j++){
            SIMDAdd(&vec1[j], &vec2[j]);
        }
        
        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeAdd = ((double)tSum)/CLOCKS_PER_SEC/10;
    tSum = 0;

    //SIMD -

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS/4; j++){
            SIMDSub(&vec1[j], &vec2[j]);
        }

        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeSub = ((double)tSum)/CLOCKS_PER_SEC/10;
    tSum = 0;

    //SIMD *

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS/4; j++){
            SIMDMul(&vec1[j], &vec2[j]);
        }

        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeMul = ((double)tSum)/CLOCKS_PER_SEC/10;
    tSum = 0;

    //SIMD /

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS/4; j++){
            SIMDDiv(&vec1[j], &vec2[j]);
        }

        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeDiv = ((double)tSum)/CLOCKS_PER_SEC/10;       
    tSum = 0;  


    fprintf(f,"Typ obliczen: SIMD\nLiczba liczb: %d\nSredni czas [s]:\n+ %f\n- %f\n* %f\n/ %f\n\n", NUMBERS, averageTimeAdd, averageTimeSub, averageTimeMul, averageTimeDiv);

    //SISD +

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS; j++){
            SISDAdd(&num1[j], &num2[j]);
        }

        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeAdd = ((double)tSum)/CLOCKS_PER_SEC/10;
    tSum = 0;

    //SISD -

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS; j++){
            SISDSub(&num1[j], &num2[j]);
        }

        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeSub = ((double)tSum)/CLOCKS_PER_SEC/10;
    tSum = 0;

    //SISD *

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS; j++){
            SISDMul(&num1[j], &num2[j]);
        }

        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeMul = ((double)tSum)/CLOCKS_PER_SEC/10;   
    tSum = 0;

    //SISD /

    for(int i=0;i<10;i++){ //repeat measure 10 times

        t = clock();   //start time measure

        for(int j=0; j<NUMBERS; j++){
     //       SISDDiv(&num1[j], &num2[j]);
        }

        t = clock() - t;    //stop time measure
        tSum += t;

    }

    averageTimeDiv = ((double)tSum)/CLOCKS_PER_SEC/10;   

    fprintf(f,"Typ obliczen: SISD\nLiczba liczb: %d\nSredni czas [s]:\n+ %f\n- %f\n* %f\n/ %f\n\n", NUMBERS, averageTimeAdd, averageTimeSub, averageTimeMul, averageTimeDiv);

    printf("%s", "Done!\n");

    return 1;
}