#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include<fstream>
#include <cstdlib>
#include <unistd.h>
using namespace std;
#define sizeOfTable 2048

clock_t startTime;
double timeSum,timeSub,timeMulti,timeDiv;

struct wektorr {
    float a;
    float b;
    float c;
    float d;
};

struct wektorr a[sizeOfTable];
struct wektorr b[sizeOfTable];
struct wektorr result[sizeOfTable];

void SumSIMD(struct wektorr a,struct wektorr b,struct wektorr* result){
asm(
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "addps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*result)
   : "m" (a),"m" (b)
    );
}

void SubSIMD(struct wektorr a,struct wektorr b,struct wektorr* result){
asm(
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "subps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*result)
   : "m" (a),"m" (b)
    );
}

void DivSIMD(struct wektorr a,struct wektorr b,struct wektorr* result){
asm(
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "divps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*result)
   : "m" (a),"m" (b)
    );
}

void MultiSIMD(struct wektorr a,struct wektorr b,struct wektorr* result){
asm(
    "movaps %1, %%xmm0\n\t"
    "movaps %2, %%xmm1\n\t"
    "mulps %%xmm1, %%xmm0\n\t"
    "movaps %%xmm0, %0\n\t"
   : "=m" (*result)
   : "m" (a),"m" (b)
    );
}


void SumSISD(struct wektorr a,struct wektorr b,struct wektorr *result){

asm(
    "fld %8\n\t"
    "fadd %4\n\t"
    "fstp %0\n\t"
    "fld %9\n\t"
    "fadd %5\n\t"
    "fstp %1\n\t"
    "fld %10\n\t"
    "fadd %6\n\t"
    "fstp %2\n\t"
    "fld %11\n\t"
    "fadd %7\n\t"
    "fstp %3\n\t"

   :    "=m" (result->a),
        "=m" (result->b),
        "=m" (result->c),
        "=m" (result->d)
   :    "m" (a.a),
        "m" (a.b),
        "m" (a.c),
        "m" (a.d),
        "m" (b.a),
        "m" (b.b),
        "m" (b.c),
        "m" (b.d)
    );

}

void SubSISD(struct wektorr a,struct wektorr b,struct wektorr* result){

asm(
    "fld %8\n\t"
    "fsub %4\n\t"
    "fstp %0\n\t"
    "fld %9\n\t"
    "fsub %5\n\t"
    "fstp %1\n\t"
    "fld %10\n\t"
    "fsub %6\n\t"
    "fstp %2\n\t"
    "fld %11\n\t"
    "fsub %7\n\t"
    "fstp %3\n\t"

   :    "=m" (result->a),
        "=m" (result->b),
        "=m" (result->c),
        "=m" (result->d)
   :    "m" (a.a),
        "m" (a.b),
        "m" (a.c),
        "m" (a.d),
        "m" (b.a),
        "m" (b.b),
        "m" (b.c),
        "m" (b.d)
    );

}

void DivSISD(struct wektorr a,struct wektorr b,struct wektorr* result){

asm(
    "fld %8\n\t"
    "fdiv %4\n\t"
    "fstp %0\n\t"
    "fld %9\n\t"
    "fdiv %5\n\t"
    "fstp %1\n\t"
    "fld %10\n\t"
    "fdiv %6\n\t"
    "fstp %2\n\t"
    "fld %11\n\t"
    "fdiv %7\n\t"
    "fstp %3\n\t"

   :    "=m" (result->a),
        "=m" (result->b),
        "=m" (result->c),
        "=m" (result->d)
   :    "m" (a.a),
        "m" (a.b),
        "m" (a.c),
        "m" (a.d),
        "m" (b.a),
        "m" (b.b),
        "m" (b.c),
        "m" (b.d)
    );

}

void MultiSISD(struct wektorr a,struct wektorr b,struct wektorr* result){
asm(
    "fld %8\n\t"
    "fmul %4\n\t"
    "fstp %0\n\t"
    "fld %9\n\t"
    "fmul %5\n\t"
    "fstp %1\n\t"
    "fld %10\n\t"
    "fmul %6\n\t"
    "fstp %2\n\t"
    "fld %11\n\t"
    "fmul %7\n\t"
    "fstp %3\n\t"

   :    "=m" (result->a),
        "=m" (result->b),
        "=m" (result->c),
        "=m" (result->d)
   :    "m" (a.a),
        "m" (a.b),
        "m" (a.c),
        "m" (a.d),
        "m" (b.a),
        "m" (b.b),
        "m" (b.c),
        "m" (b.d)
    );

}



void fillWithRandomNum(){
    for(int i=0;i<sizeOfTable;i++){
        a[i].a = (float)(rand()%10000)/100.0f;
        a[i].b = (float)(rand()%10000)/100.0f;
        a[i].c = (float)(rand()%10000)/100.0f;
        a[i].d = (float)(rand()%10000)/100.0f;
    }
    for(int i=0;i<sizeOfTable;i++){
        b[i].a = (float)(rand()%10000)/100.0f;
        b[i].b = (float)(rand()%10000)/100.0f;
        b[i].c = (float)(rand()%10000)/100.0f;
        b[i].d = (float)(rand()%10000)/100.0f;
    }
}

void wektory(){

    for(int k=0;k<10;k++){
            //usleep(100000); // jednak nie moznabo psuje wyniki

        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            SumSIMD(a[i],b[i],&result[i]);
            timeSum += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            DivSIMD(a[i],b[i],&result[i]);
            timeDiv += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            SubSIMD(a[i],b[i],&result[i]);
            timeSub += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            MultiSIMD(a[i],b[i],&result[i]);
            timeMulti += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }

    }
    timeSum = timeSum/(float)(10*sizeOfTable);//*sizeOfTable);
    timeDiv = timeDiv/(float)(10*sizeOfTable);//*sizeOfTable);
    timeMulti = timeMulti/(float)(10*sizeOfTable);//*sizeOfTable);
    timeSub = timeSub/(float)(10*sizeOfTable);//*sizeOfTable);
}

void noWektor(){

    for(int k=0;k<10;k++){
             //usleep(100000); // jednak nie moznabo psuje wyniki
        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            SumSISD(a[i],b[i],&result[i]);
            timeSum += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            DivSISD(a[i],b[i],&result[i]);
            timeDiv += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            MultiSISD(a[i],b[i],&result[i]);
            timeMulti += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
        for(int i=0;i<sizeOfTable;i++){
            startTime = clock();
            SubSISD(a[i],b[i],&result[i]);
            timeSub += ((double)clock() - startTime)/CLOCKS_PER_SEC*1000.0;
        }
    }
    timeSum = timeSum/(float)(10*sizeOfTable);
    timeDiv = timeDiv/(float)(10*sizeOfTable);
    timeMulti = timeMulti/(float)(10*sizeOfTable);
    timeSub = timeSub/(float)(10*sizeOfTable);
}


int main(){
        int noVector = 0;
        srand(time(NULL));
        fillWithRandomNum();
        cout << "Wybierz typ operacji: Na Wektorach (0), Bez wektorow(1)"<<endl;
        cin>>noVector;

        if(noVector ==0){
        wektory();
        cout << "Dzialania na wektorach: "<<endl;
        }else if(noVector == 1){
        noWektor();
        cout << "Dzialania bez wektorow: "<<endl;
        }

        cout << "Liczba liczb w Tablicy: "<< sizeOfTable*4<<endl;
        cout << "Wyniki [ms]: "<<endl<< "Dodawanie: " << timeSum <<endl;
        cout << "Odejmowanie: " << timeSub<<endl;
        cout << "Mnozenie: " << timeMulti <<endl;
        cout << "Dzielenie: " << timeDiv <<endl;
        ofstream zapis("dane.txt");
        zapis << "Rozmiar Tablicy: " << sizeOfTable*4<<endl;
        zapis << "Wyniki [ms]: "<<endl<< "Dodawanie: " << timeSum <<endl;
        zapis << "Odejmowanie: " << timeSub<<endl;
        zapis << "Mnozenie: " << timeMulti <<endl;
        zapis << "Dzielenie: " << timeDiv <<endl;
        zapis.close();
    return 0;
}


