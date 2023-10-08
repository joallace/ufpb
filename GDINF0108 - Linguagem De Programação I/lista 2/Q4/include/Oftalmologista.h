#ifndef OFTALMOLOGISTA_H
#define OFTALMOLOGISTA_H

#include <Medico.h>


class Oftalmologista : public Medico
{
    public:
        Oftalmologista(std::string nome, std::string altura, std::string peso);
        std::string atendimento();
};

#endif // OFTALMOLOGISTA_H
