#ifndef RELOGIO_H
#define RELOGIO_H

class Relogio{
    int hora, minuto, segundo;

    public:
    void setHorario(int, int, int);
    int getHora(), getMinuto(), getSegundo();
    void avancarHorario();
};


#endif // RELOGIO_H
