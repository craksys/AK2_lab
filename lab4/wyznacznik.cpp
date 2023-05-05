#include <iostream>

using namespace std;
typedef struct{
    float x0,x1,x2,x3;
}wektor;

float wyznacznik(wektor v1, wektor v2, wektor v3, wektor v4);

int main(){
    float wynik;
    float macierzWejsciowa[4][4];
    float macierzTestowa[4][4] = {
        {1,3,4,5},
        {3,0,0,2},
        {5,1,2,7},
        {2,0,0,3}
    };

    int wybor;
    cout << "Chcesz wpisac wlasna macierz czy testowa? (0 - wlasna, 1 - testowa): ";
    cin >> wybor;
    if(wybor != 1 && wybor != 0){return 1;}
    if(wybor == 0){
    cout << "Podaj macierz (jedna liczba -> enter)"<<endl;
    cout << "Wedlug kolejnosci: "<<endl;
    cout << "0,1,2,3"<<endl;
    cout << "4,5,6,7"<<endl;
    cout << "8,9,10,11"<<endl;
    cout << "12,13,14,15"<<endl;
    float pomoc;
    for(int i = 0; i<4;i++){
        for(int j = 0; j<4; j++ ){
            cin>>pomoc;
            cout<<endl;
            macierzWejsciowa[i][j] = pomoc;
        }
    }
    }

    wektor macierz[4];
    if(wybor == 0){
    for(int i=0;i<4;i++){
        macierz[i].x0 = macierzWejsciowa[i][0];
        macierz[i].x1 = macierzWejsciowa[i][1];
        macierz[i].x2 = macierzWejsciowa[i][2];
        macierz[i].x3 = macierzWejsciowa[i][3];
    }
    }else if (wybor == 1){
        for(int i=0;i<4;i++){
        macierz[i].x0 = macierzTestowa[i][0];
        macierz[i].x1 = macierzTestowa[i][1];
        macierz[i].x2 = macierzTestowa[i][2];
        macierz[i].x3 = macierzTestowa[i][3];
    }
    }
    for(int i =0;i<4;i++){
        cout <<"[";
        cout << macierz[i].x0<<",";
        cout << macierz[i].x1<<",";
        cout << macierz[i].x2<<",";
        cout << macierz[i].x3;
        cout <<"]"<<endl;
    }
    wynik = wyznacznik(macierz[0], macierz[1], macierz[2], macierz[3]);
    cout << "Wyznacznik: " << wynik<<endl;
}
/*
detM = (a0 * b1 - a1 * b0) * (c2 * d3 - c3 * d2) +
(a2 * b0 - a0 * b2) * (c1 * d3 - c3 * d1) +
(a0 * b3 - a3 * b0) * (c1 * d2 - c2 * d1) +
(a1 * b2 - a2 * b1) * (c0 * d3 - c3 * d0) +
(a2 * b3 - a3 * b2) * (c0 * d1 - c1 * d0) +
(a3 * b1 - a1 * b3) * (c0 * d2 - c2 * d0)
*/
float wyznacznik(wektor v1, wektor v2, wektor v3, wektor v4) {
    wektor output; //tworzymy wektor koñcowy
         // makro oblicza wyra¿enie wektorowe A'B' - A”B”
         //% 1 - wektor A
         //% 2 - wektor B
         //% 3 - sta³a dla rozkazu shufps która wygeneruje wektory A' i B”
         //% 4 - sta³a dla rozkazu shufps która wygeneruje wektory B' i A”
         //% 5, % 6 - rejestry robocze -- niszczone
         //% 7 - rejestr wynikowy
    asm(
        //+-------------+ 1
        //przenosimy do rejestrów wektory
        "movaps %1, %%xmm0 \n\t"
        "movaps %2, %%xmm1 \n\t"
        //rozwiniêcia Laplace'a
        "shufps $0x48, %%xmm0, %%xmm0 \n\t" //01 00 10 00
        "shufps $0xB1, %%xmm1, %%xmm1 \n\t" //10 11 00 01

        "mulps %%xmm1, %%xmm0 \n\t"

        "movaps %1, %%xmm1 \n\t"
        "movaps %2, %%xmm2 \n\t"
        "shufps $0xB1, %%xmm1, %%xmm1 \n\t" //10 11 00 01
        "shufps $0x48, %%xmm2, %%xmm2 \n\t" //01 00 10 00

        "mulps %%xmm2, %%xmm1 \n\t"
        "subps %%xmm0, %%xmm1 \n\t"
        //+-------------+ 2
        "movaps %3, %%xmm0 \n\t"
        "movaps %4, %%xmm2 \n\t"
        "shufps $0x16, %%xmm0, %%xmm0 \n\t" //00 01 01 10
        "shufps $0xEF, %%xmm2, %%xmm2 \n\t" //11 10 11 11

        "mulps %%xmm2, %%xmm0 \n\t"

        "movaps %3, %%xmm2 \n\t"
        "movaps %4, %%xmm3 \n\t"
        "shufps $0xEF, %%xmm2, %%xmm2 \n\t" //11 10 11 11
        "shufps $0x16, %%xmm3, %%xmm3 \n\t" //11 10 11 11

        "mulps %%xmm3, %%xmm2 \n\t"
        "subps %%xmm0, %%xmm2 \n\t"
        //
        "mulps %%xmm2, %%xmm1 \n\t"
        //
        //+-------------+ 3
        "movaps %1, %%xmm0 \n\t"
        "movaps %2, %%xmm2 \n\t"
        "shufps $0x0E, %%xmm0, %%xmm0 \n\t" //00 00 11 10
        "shufps $0x07, %%xmm2, %%xmm2 \n\t" //00 00 01 11

        "mulps %%xmm2, %%xmm0 \n\t"

        "movaps %1, %%xmm2 \n\t"
        "movaps %2, %%xmm3 \n\t"
        "shufps $0x07, %%xmm2, %%xmm2 \n\t" //00 00 01 11
        "shufps $0x0E, %%xmm3, %%xmm3 \n\t" //00 00 11 10

        "mulps %%xmm3, %%xmm2 \n\t"
        "subps %%xmm0, %%xmm2 \n\t"
        //+-------------+ 4
        "movaps %3, %%xmm0 \n\t"
        "movaps %4, %%xmm3 \n\t"
        "shufps $0x00, %%xmm0, %%xmm0 \n\t" //00 00 00 00
        "shufps $0x09, %%xmm3, %%xmm3 \n\t" //01 00 00 01

        "mulps %%xmm3, %%xmm0 \n\t"

        "movaps %3, %%xmm3 \n\t"
        "movaps %4, %%xmm4 \n\t"
        "shufps $0x09, %%xmm3, %%xmm3 \n\t" //01 00 00 01
        "shufps $0x00, %%xmm4, %%xmm4 \n\t" //00 00 00 00

        "mulps %%xmm4, %%xmm3 \n\t"

        "subps %%xmm0, %%xmm3 \n\t"

        "mulps %%xmm3, %%xmm2 \n\t"

        "addps %%xmm2, %%xmm1 \n\t"
        "movaps %%xmm1, %0 \n\t"

        :"=g" (output)
        : "g"(v1), "g"(v2), "g"(v3), "g"(v4)
    );

    return output.x0 + output.x1 + output.x2 + output.x3;
}

