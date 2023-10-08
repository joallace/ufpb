#include "Ginecologista.h"

Ginecologista::Ginecologista(std::string nome, std::string altura, std::string peso):
Medico(nome, altura, peso){
    setEspecialidade("Ginecologista");
}

std::string Ginecologista::atendimento(){
    return "Realizando atendimento ginecologico";
}
