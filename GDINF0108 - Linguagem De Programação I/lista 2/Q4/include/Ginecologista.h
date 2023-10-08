#ifndef GINECOLOGISTA_H
#define GINECOLOGISTA_H

#include <Medico.h>


class Ginecologista : public Medico
{
    public:
        Ginecologista(std::string nome, std::string altura, std::string peso);
        std::string atendimento();
};

#endif // GINECOLOGISTA_H
