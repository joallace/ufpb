#include "Oftalmologista.h"

Oftalmologista::Oftalmologista(std::string nome, std::string altura, std::string peso):
Medico(nome, altura, peso){
    setEspecialidade("Oftalmologista");
}

std::string Oftalmologista::atendimento(){
    return "Realizando atendimento oftalmologico";
}
