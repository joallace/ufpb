#ifndef DATA_H
#define DATA_H

class Data{
    private:
        int dia;
        int mes;
        int ano;

    public:
        Data(int dia, int mes, int ano);
        void avancarDia();

        int getDia();
        int getMes();
        int getAno();
        void setDia(int dia);
        void setMes(int mes);
        void setAno(int ano);
};

#endif // Data
