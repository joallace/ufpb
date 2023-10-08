#ifndef TESTAVALIDANUMERO_H
#define TESTAVALIDANUMERO_H

#include "ValorAbaixoException.h"
#include "ValorAcimaException.h"
#include "ValorMuitoAcimaException.h"

class TestaValidaNumero : public std::exception{
    public:
        void validaNumero(int num);
};

#endif // TESTAVALIDANUMERO_H
