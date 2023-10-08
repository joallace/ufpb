#ifndef INVOICE_DEF
#define INVOICE_DEF
#include <string>

class Invoice{
    private:
        int num;
        int qntd;
        std::string descricao;
        double preco;

    public:
        Invoice(int, int, std::string, double);
        double getInvoiceAmount();

        int getNum();
        int getQntd();
        std::string getDescricao();
        double getPreco();

        void setNum(int);
        void setQntd(int);
        void setDescricao(std::string);
        void setPreco(double);

};

#endif // INVOICE_DEF
