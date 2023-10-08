#ifndef OTORRINO_H
#define OTORRINO_H

#include <Medico.h>


class Otorrino : public Medico
{
    public:
        Otorrino(std::string nome, std::string altura, std::string peso);
        std::string atendimento();
};

#endif // OTORRINO_H
