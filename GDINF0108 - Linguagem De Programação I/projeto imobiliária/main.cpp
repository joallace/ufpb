#include "Menu.h"

int main(){
    SistemaImobiliaria imobiliaria = SistemaImobiliaria();
    Menu menu = Menu(&imobiliaria);
    menu.principal();

    return 0;
}
