#include <iostream>

template <typename T>struct Humano{
    int idade;
    char nome[100];
    T altura;
};

Humano<double> adriel{22, "Adriel", 1.677777777773392183821093805409285};

int main(){
    float a = 1.677777777773392183821093805409285;
    double b = 1.677777777773392183821093805409285;

    printf("%f\n", a);
    printf("%lf\n", b);

    return 0;
}