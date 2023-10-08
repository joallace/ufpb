#include "TestaValidaNumero.h"

void TestaValidaNumero::validaNumero(int num){
    if(num <= 0)
            throw ValorAbaixoException();
    if(num >= 1000)
            throw ValorMuitoAcimaException();
    if(num >= 100)
            throw ValorAcimaException();
}
