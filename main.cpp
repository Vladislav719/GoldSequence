//#include <bitset>
//#include <iostream>;
//using namespace std;
//int generate(uint16_t a);
//int main() {
//    unsigned start_state = (((31^(31>>3)&1)>>1) ^ (((31^(31>>3)&1)>>1)>>1) & 1)>>1;
//    int original_value = 31;
//    int N = 1;
//    start_state = (start_state ^ (start_state>>1)&1);
//    int n = start_state & ((1 << 1) - 1);
//    cout << n;
////    cout<<(bitset<5>(start_state));
////    cout<< bitset<31>(generate(start_state));
////    cout<<'\n'<<bitset<16>(0xB4);
//
////    int a = 31;
////    int i = 0;
////    do {
////        a = a ^ a >> 3;
////        ++i;
////    }while(i!=a);
//    return 0;
//}
//
///**
//*
//*/
//int generate(uint16_t start_state) {
//
//    uint16_t res = start_state;
//    unsigned bit;
//    unsigned iter = 0;
//    do {
//        //X^5 + x^2 + 1, taps 5,2
//        bit = ((res>>0) ^ (res >> 3)) & 1;
//        res = (res>>1) | (bit << 4);
//        cout<<bitset<16>(res)<< ' ' << iter<<'\n';
//        ++iter;
//    } while (res != start_state);
//    return res;
//}
//
//
//
//
///**
//* функция возвращает последние N бит
//*/
//int retrieveRightNBit(int value, int how_many) {
//    return (value & ((1<< how_many) - 1));
//}

#include "iostream"
#include "bitset"
#include "cmath"
using namespace std;
int gen(int a, int b, int size);
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
    cout << "Введите количество отводов для 1 и 2 последовательности через пробел" << endl;
    cin >> taps1>>taps2;
    int a = gen(pow(2, init_state) - 1, taps1, init_state);
    int b = gen(pow(2, init_state) - 1, taps2, init_state);
    printAsBinary(a^b);


    return 0;
}



void printAsBinary(int num) {
    cout << bitset<63>(num)<<endl;
}

/**
* init первоначальный регистр например  1 1 1 1 1 = то есть 31
*/
int gen(int init, int taps, int size_shift) {
    int res = 0;
    int period = init;
    do {
        int bit = getBit(init, 0);
        for (int i = 1; i <= taps; i++) {
            bit ^= getBit(init, i);
        }
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


