#include "Otorrino.h"

Otorrino::Otorrino(std::string nome, std::string altura, std::string peso):
Medico(nome, altura, peso){
    setEspecialidade("Otorrino");
}

std::string Otorrino::atendimento(){
    return "Realizando atendimento otorrinolaringologico";
}
