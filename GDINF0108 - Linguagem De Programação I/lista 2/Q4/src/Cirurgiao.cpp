#include "Cirurgiao.h"

Cirurgiao::Cirurgiao(std::string nome, std::string altura, std::string peso):
Medico(nome, altura, peso)
{
    setEspecialidade("Cirurgiao");
}

std::string Cirurgiao::atendimento(){
    return "Realizando cirurgia";
}

