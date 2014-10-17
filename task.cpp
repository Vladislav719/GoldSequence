#include "iostream"
#include "bitset"
#include "cmath"
using namespace std;
int gen(int a, int b, int size, int arr_taps[]);
int retrieveRightNBit(int v, int m);

void printAsBinary(int num) ;

void setBit(int& value, int n) ;

/*
* получаем N-ый бит, начиная с 0 справа
*/
int getBit(int& value, int n) ;

void toggleBit(int& value, int n) ;

int main() {
    int init_state;
    cout << "Введите начальное состояние"<< endl;
    cin >> init_state; //ининциализировали регистр единицами.
    int taps1, taps2;
    cout << "Введите количество отводов для 1 последовательности" << endl;
    cin >> taps1;
    cout << "Введите номера для отводов в количестве " << taps1 << endl;
    int arr1[taps1];
    for (int i = 0; i < taps1; i++)
        cin>>arr1[i];
    cout << "Введите количество отводов для 2 последовательности" << endl;
    cin >> taps2;
    int arr2[taps2];
    cout << "Введите номера для отводов в количестве " << taps2 << endl;
    for (int i = 0; i < taps2; i++)
        cin>>arr2[i];
    int a = gen(pow(2, init_state) - 1, taps1, init_state,arr1);
    int b = gen(pow(2, init_state) - 1, taps2, init_state,arr2);
    cout << "M1 = ";
    printAsBinary(a);
    cout << "M2 = ";
    printAsBinary(b);
    cout << "Код = ";
    printAsBinary(a^b);


    return 0;
}



void printAsBinary(int num) {
    cout << bitset<31>(num)<<endl;
}

/**
* init первоначальный регистр например  1 1 1 1 1 = то есть 31
*/
int gen(int init, int taps, int size_shift, int  a[]) {

    int res = 0;
    int period = init;
    do {
        //ксорим указанные биты
        int bit = getBit(init, a[0]);
        for (int i = 1; i < taps - 1; i++) {
            bit ^= getBit(init, a[i]);
        }

        //записываем в результат
        if (res == 0) {
            setBit(res, 0);
        } else {
            res <<= 1;
            if (getBit(init, 0) != getBit(res, 0)) {
                toggleBit(res, 0);
            }
        }

        init >>= 1;//сдвигаю реестр вправо
        if (bit != getBit(init, size_shift-1)) {
            toggleBit(init, size_shift);
        }

        --period;
    } while (period != 0);
    return res;
}

/*
* получаем N-ый бит, начиная с 0 справа
*/
int getBit(int& value, int n) {
    return !!(value & (1 << n));
}

void setBit(int& value, int n) {
    value |= (1 << n);
}

int retrieveRightNBit(int value, int how_many) {
    return (value & ((1<< how_many) - 1));
}

void toggleBit(int& value, int n) {
    value ^= 1 << n;
}


