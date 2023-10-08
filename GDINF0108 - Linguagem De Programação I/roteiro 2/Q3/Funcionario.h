#ifndef FUNCIONARIO_DEF
#define FUNCIONARIO_DEF
#include <string>

class Funcionario{
    protected:
        std::string nome;
        std::string matricula;
        double salario;

    public:
        Funcionario(std::string nome, std::string matricula, double salario);

        std::string getNome();
        std::string getMatricula();
        virtual double getSalario();

        void setNome(std::string nome);
        void setMatricula(std::string matricula);
        void setSalario(double salario);
};

#endif // FUNCIONARIO_DEF
