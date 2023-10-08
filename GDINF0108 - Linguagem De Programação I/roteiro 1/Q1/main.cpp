#include <iostream>
#include <conio.h>
#include "Data.cpp"

using namespace std;

int main(){
    int dia, mes, ano;

    cout<<"Insira o dia: ";
    cin >> dia;
    cout<<"Insira o mes: ";
    cin >> mes;
    cout<<"Insira o ano: ";
    cin >> ano;

    Data data = Data(dia, mes, ano);

    cout << "Para sair, digite 0"<<endl;

    while(true){
        cout << data.getDia() << "/" << data.getMes() << "/" << data.getAno() << endl;
        if(getch() == '0')
            break;
        data.avancarDia();
    }
    return 0;
}

