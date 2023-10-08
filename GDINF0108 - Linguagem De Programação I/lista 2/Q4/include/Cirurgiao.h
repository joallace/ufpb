#ifndef CIRURGIAO_H
#define CIRURGIAO_H

#include <Medico.h>


class Cirurgiao : public Medico{
    public:
        Cirurgiao(std::string nome, std::string altura, std::string peso);
        std::string atendimento();
};

#endif // CIRURGIAO_H
