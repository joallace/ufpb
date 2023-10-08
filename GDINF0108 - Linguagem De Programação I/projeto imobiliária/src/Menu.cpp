#include "Menu.h"

Menu::Menu(SistemaImobiliaria *imobiliaria){
    this->imobiliaria = imobiliaria;
    imobiliaria->lerImoveis();
}

void Menu::confirmaSaida(){
	std::cout << "\n\nPressione uma tecla para voltar ao menu\n";
    if(getch() == 224)
        getch();
    system("cls");
    principal();
}

tNegocio Menu::getNegocio(){
    char escolha;
    bool interminado = true;

    std::cout << "1.Venda\n"<<
                 "2.Aluguel\n"<<
                 "\nEscolha o tipo de negocio:\n";



    while(interminado){
        escolha = getch();
        switch(escolha){
            case '1':
                interminado = false;
                return VENDA;
                break;

            case '2':
                interminado = false;
                return ALUGUEL;
                break;

            default:
                std::cout << "Insira uma opcao valida\n";
        }
    }
    return VENDA;
}

double Menu::getValor(tNegocio negocio){
    double valor;

    std::cout << "\nInsira o preco " << (negocio == VENDA? "de venda: " : "do aluguel: ");
    std::cin >> valor;

    return valor;
}

Endereco Menu::getEndereco(){
    std::string rua,
                bairro,
                cidade,
                cep,
                numero;

    std::cout<<"---===Digite o endereco:===---\n\n";

    std::cout<<"\nRua: ";
    std::cin.ignore();
    getline(std::cin, rua);

    std::cout<<"\nNumero: ";
    getline(std::cin, numero);

    std::cout<<"\nBairro: ";
    getline(std::cin, bairro);

    std::cout<<"\nCidade: ";
    getline(std::cin, cidade);

    std::cout<<"\nCEP: ";
    getline(std::cin,cep);

    return Endereco(rua, bairro, cidade, cep, numero);
}

void Menu::getCasa(int *numQuartos, int *numPavimentos, double *areaConstruida, double *area){
    std::cout<<"---===Caracteristicas da casa===---\n\n";

    std::cout << "\nDigite o numero de quartos: ";
    std::cin >> *numQuartos;


    std::cout << "\nDigite o numero de pavimentos: ";
    std::cin >> *numPavimentos;


    std::cout << "\nDigite a area da construida: ";
    std::cin >> *areaConstruida;


    std::cout << "\nDigite a area total da casa: ";
    std::cin >> *area;
}

void Menu::getApartamento(double *valorCondominio, int *numQuartos, int *vagasGaragem, std::string *posicao, double *area){
    std::cout << "\nDigite o valor do condominio: ";
    std::cin >> *valorCondominio;

    std::cout << "\nDigite o numero de quartos: ";
    std::cin >> *numQuartos;

    std::cout << "\nDigite a quantidade de vagas na garagem: ";
    std::cin >> *vagasGaragem;

    std::cout << "\nDigite a area total do apartamento: ";
    std::cin >> *area;

    std::cout << "\nDigite a posicao do apartamento: ";
    std::cin.ignore();
    getline(std::cin, *posicao);
}


void Menu::getTerreno(double *area){
    std::cout << "\nDigite a area do terreno: ";
    std::cin >> *area;
}


void Menu::consulta(){
    char i;
    bool interminado = true;

    system("cls");

    std::cout<<"---===Selecione o metodo de listagem===---\n"
         <<"1. Listar todos\n"
         <<"2. Listar por tipo de imovel\n"
         <<"3. Listar por tipo de negocio\n"
         <<"4. Voltar para o Menu\n";

    while(interminado){
        i = getch();
        switch(i){
            case '1':
                system("cls");
                std::cout << imobiliaria->getImoveis() << std::endl;
                interminado = false;
                break;

            case '2':
                system("cls");
                std::cout << "1. Casa\n"<<
                             "2. Apartamento\n"<<
                             "3. Terreno\n"<<
                             "\nEscolha o tipo de imovel:\n";
                while(interminado){
                    i = getch();
                    switch(i){
                        case '1':
                            std::cout << imobiliaria->getImoveis(CASA) << std::endl;
                            interminado = false;
                            break;

                        case '2':
                            std::cout << imobiliaria->getImoveis(APARTAMENTO) << std::endl;
                            interminado = false;
                            break;

                        case '3':
                            std::cout << imobiliaria->getImoveis(TERRENO) << std::endl;
                            interminado = false;
                            break;

                        default:
                            std::cout << "Insira uma opcao valida\n";
                    }
                }
                break;

            case '3':
                system("cls");
                std::cout << "1. Venda\n"<<
                             "2. Aluguel\n"<<
                             "\nEscolha o tipo de negocio:\n";
                while(interminado){
                    i = getch();
                    switch(i){
                        case '1':
                            std::cout << imobiliaria->getImoveis(VENDA) << std::endl;
                            interminado = false;
                            break;

                        case '2':
                            std::cout << imobiliaria->getImoveis(ALUGUEL) << std::endl;
                            interminado = false;
                            break;

                        default:
                            std::cout << "Insira uma opcao valida\n";
                    }
                }
                break;

            case '4':
                principal();
                interminado = false;
                break;

            default:
                std::cout << "Insira uma opcao valida\n";
        }
    }
    confirmaSaida();
}

void Menu::buscar(){
    char i;
    bool interminado;
    double valorEscolhido;
    std::string local;

    system ("cls");
    std::cout<<"---===Selecione o metodo de busca===---\n"
             <<"1.Por bairro\n"
             <<"2.Por cidade\n"
             <<"3.Por valor\n"
             <<"4.Voltar para o Menu\n";

    i = getch();

    switch(i){
        case '1':
            system("cls");

            std::cout<<"Digite o nome do bairro:\n";
            std::cin>>local;
            system("cls");

            std::cout<<imobiliaria->buscarImovel(local,0)<<std::endl;
            break;

        case '2':
            system("cls");

            std::cout<<"Digite o nome da cidade:\n";
            std::cin>>local;
            system("cls");

            std::cout<<imobiliaria->buscarImovel(local,1)<<std::endl;
            break;

        case '3':
            system("cls");

            std::cout<<"---===Escolher Imovel por===---\n"
                     <<"1.Valor maior que\n"
                     <<"2.Valor menor que\n\n";

            interminado = true;
            while(interminado){
                i = getch();
                system("cls");

                switch(i){
                    case '1':
                        interminado = false;
                        std::cout<<"Digite o valor desejado:\n"<<std::endl;
                        std::cin>>valorEscolhido;

                        system("cls");

                        std::cout<<imobiliaria->buscarImovel(valorEscolhido,1)<<std::endl;
                        break;

                    case '2':
                        interminado = false;
                        std::cout<<"Digite o valor desejado:\n"<<std::endl;
                        std::cin>>valorEscolhido;

                        system("cls");

                        std::cout<<imobiliaria->buscarImovel(valorEscolhido,0)<<std::endl;
                        break;

                    default:
                        std::cout<<"Insira um valor valido"<<std::endl;
                }
            }
            break;

        case '4':
            principal();
            break;

        default:
            std::cout<<"Insira uma opcao valida\n";
            buscar();
    }
}

void Menu::busca(){
    buscar();
    confirmaSaida();
}

void Menu::cadastro(){
    //Variaveis de navegacao
    char i;
    bool interminado;

    //Variaveis genericas
    int numQuartos;
    double valor,
           area;
    tNegocio negocio;

    //Imoveis
    Casa c;
        //Atributos de casa
        int numPavimentos;
        double areaConstruida;

    Apartamento a;
        //Atributos de apartamento
        std::string posicao;
        double valorCondominio;
        int vagasGaragem;

    Terreno t;


    system("cls");

    std::cout << "---------=========Cadastro=========---------\n\n";
    std::cout << "1. Casa\n"
                 "2. Apartamento\n"
                 "3. Terreno\n\n"
                 "Escolha o tipo de imovel, ou digite 0 para voltar: \n";

    interminado = true;
    while(interminado){
        i = getch();


        switch(i){
            case '0':
                principal();
                break;

            case '1':
                interminado = false;
                system("cls");
                std::cout << "---------=========Casa=========---------\n\n";
                break;

            case '2':
                interminado = false;
                system("cls");
                std::cout << "---------=========Apartamento=========---------\n\n";
                break;

            case '3':
                interminado = false;
                system("cls");
                std::cout << "---------=========Terreno=========---------\n\n";
                break;

            default:
                std::cout << "\nInsira uma opcao valida\n";
        }
    }

    negocio = getNegocio();

    valor = getValor(negocio);

    system("cls");


    switch(i){
        case '1':
            std::cout << "---------=========Casa=========---------\n\n";
            break;

        case '2':
            std::cout << "---------=========Apartamento=========---------\n\n";
            break;

        case '3':
            std::cout << "---------=========Terreno=========---------\n\n";
            break;
    }
    Endereco endereco = getEndereco();

    switch(i){
        case '1':
            system("cls");
            std::cout << "---------=========Casa=========---------\n\n";

            getCasa(&numQuartos, &numPavimentos, &areaConstruida, &area);

            system("cls");

            c = Casa(endereco, negocio, valor, area, areaConstruida, numQuartos, numPavimentos);
            imobiliaria->addImovel(&c);
            std::cout << "Casa cadastrada com sucesso!\n";
            break;


        case '2':
            system("cls");
            std::cout << "---------=========Apartamento=========---------\n\n";

            getApartamento(&valorCondominio, &numQuartos, &vagasGaragem, &posicao, &area);

            system("cls");

            a = Apartamento(endereco, negocio, valor, area, valorCondominio, numQuartos, vagasGaragem, posicao);
            imobiliaria->addImovel(&a);
            std::cout << "Apartamento cadastrado com sucesso!\n";
            break;


        case '3':
            system("cls");
            std::cout << "---------=========Terreno=========---------\n\n";

            getTerreno(&area);

            system("cls");

            t = Terreno(endereco, negocio, valor, area);
            imobiliaria->addImovel(&t);
            std::cout << "Terreno cadastrado com sucesso!\n";
            break;
    }
    confirmaSaida();
}


void Menu::remover(){
    int i;
    char escolha;
    bool interminado = true;

    buscar();

    std::cout<<"\nDigite o indice do imovel a ser removido: ";

    while(interminado){
        std::cin >> i;
        i--;

        if(imobiliaria->getQntdImoveis() > i)
            interminado = false;
        else
            std::cout << "Nao existe nenhum imovel nesse indice\n";
    }

    std::cout << "Tem certeza que deseja remover o imovel de indice " << i+1 << "? (s/n)\n";

    interminado = true;
    while(interminado){
        std::cin.ignore();
        escolha = getchar();
        escolha = toupper(escolha);
        switch(escolha){
            case 'S':
                imobiliaria->removeImovel(i);
                interminado = false;
                break;

            case 'N':
                confirmaSaida();
                interminado = false;
                break;

            default:
                std::cout<<"Insira uma opcao valida\n";
        }
    }
    confirmaSaida();
}

void Menu::editar(){
    //Variaveis de navegacao
    int i, escolha;
    bool interminado = true;

    //Variaveis genericas
    int numQuartos;
    double area;

    //Imoveis
    //Atributos de casa
    int numPavimentos;
    double areaConstruida;

    //Atributos de apartamento
    std::string posicao;
    double valorCondominio;
    int vagasGaragem;

    buscar();

    std::cout<<"\nDigite o indice do imovel a ser editado: ";

    while(interminado){
        std::cin >> i;
        i--;

        if(imobiliaria->getQntdImoveis() > i)
            interminado = false;
        else
            std::cout << "Nao existe nenhum imovel nesse indice\n";
    }

    interminado = true;

    system("cls");

    if(imobiliaria->getTipo(i) == CASA){
        std::cout <<"----====Editar Casa====----\n"
                  <<"1. Endereco\n"
                  <<"2. Tipo de negocio\n"
                  <<"3. Valor\n"
                  <<"4. Caracteristicas da casa\n"
                  <<"5. Retornar\n";

        while(interminado){
            escolha = getch();
            switch(escolha){
                case '1':
                    system("cls");
                    std::cout<<"----====Editar Casa====----\n";
                    imobiliaria->editarImovel(getEndereco(), i);
                    interminado = false;
                    break;


                case '2':
                    system("cls");
                    std::cout<<"----====Editar Casa====----\n";
                    imobiliaria->editarImovel(getNegocio(), i);
                    interminado = false;
                    break;


                case '3':
                    system("cls");
                    std::cout<<"----====Editar Casa====----\n";
                    imobiliaria->editarImovel(getValor(imobiliaria->getNegocio(i)), i);
                    interminado = false;
                    break;


                case '4':
                    system("cls");
                    std::cout<<"----====Editar Casa====----\n";
                    getCasa(&numQuartos, &numPavimentos, &areaConstruida, &area);
                    imobiliaria->editarCasa(numQuartos, numPavimentos, areaConstruida, area, i);
                    interminado = false;


                case '5':
                    principal();
                    interminado = false;
                    break;

                default:
                    std::cout << "Insira uma opcao valida\n";
                    break;

            }
        }
        system("cls");
        std::cout << "Casa editada com sucesso!\n";
    }
    else if(imobiliaria->getTipo(i) == APARTAMENTO){
        std::cout<<"----====Editar Apartamento====----\n"
                 <<"1. Endereco\n"
                 <<"2. Tipo de negocio\n"
                 <<"3. Valor\n"
                 <<"4. Caracteristicas do apartamento\n"
                 <<"5. Retornar\n";

        while(interminado){
            escolha = getch();
            switch(escolha){
                case '1':
                    system("cls");
                    std::cout<<"----====Editar Apartamento====----\n";
                    imobiliaria->editarImovel(getEndereco(), i);
                    interminado = false;
                    break;


                case '2':
                    system("cls");
                    std::cout<<"----====Editar Apartamento====----\n";
                    imobiliaria->editarImovel(getNegocio(), i);
                    interminado = false;
                    break;


                case '3':
                    system("cls");
                    std::cout<<"----====Editar Apartamento====----\n";
                    imobiliaria->editarImovel(getValor(imobiliaria->getNegocio(i)), i);
                    interminado = false;
                    break;

                case '4':
                    system("cls");
                    std::cout<<"----====Editar Apartamento====----\n";
                    getApartamento(&valorCondominio, &numQuartos, &vagasGaragem, &posicao, &area);
                    imobiliaria->editarApartamento(valorCondominio, numQuartos, vagasGaragem, posicao, area, i);
                    interminado = false;
                    break;

                case '5':
                    principal();
                    interminado = false;
                    break;

                default:
                    std::cout << "Insira uma opcao valida\n";
                    break;
            }
            system("cls");
            std::cout << "Apartamento editado com sucesso!\n";
        }
    }else if(imobiliaria->getTipo(i) == TERRENO){

        std::cout<<"----====Editar Terreno====----\n"
                 <<"1. Endereco\n"
                 <<"2. Tipo de negocio\n"
                 <<"3. Valor\n"
                 <<"4. Caracteristicas do terreno\n"
                 <<"5. Voltar\n";

        while(interminado){
            escolha = getch();
            switch(escolha){
                case '1':
                    system("cls");
                    std::cout<<"----====Editar Terreno====----\n";
                    imobiliaria->editarImovel(getEndereco(), i);
                    interminado = false;
                    break;


                case '2':
                    system("cls");
                    std::cout<<"----====Editar Terreno====----\n";
                    imobiliaria->editarImovel(getNegocio(), i);
                    interminado = false;
                    break;


                case '3':
                    system("cls");
                    std::cout<<"----====Editar Terreno====----\n";
                    imobiliaria->editarImovel(getValor(imobiliaria->getNegocio(i)), i);
                    interminado = false;
                    break;

                case '4':
                    system("cls");
                    std::cout<<"----====Editar Terreno====----\n";
                    getTerreno(&area);
                    imobiliaria->editarTerreno(area, i);
                    interminado = false;
                    break;

                case '5':
                    principal();
                    interminado = false;
                    break;

                default:
                    std::cout << "Insira uma opcao valida\n";
                    break;
            }
            system("cls");
            std::cout << "Terreno editado com sucesso!\n";
        }
    }
    confirmaSaida();
}

void Menu::principal(){
    char i;
   //tem que ler a lista automaticamente assim que começar

    system ("cls");

    std::cout << "---------=========Menu=========---------\n"<<
                 "1. Cadastrar imoveis\n"<<
                 "2. Consultar imoveis\n"<<
                 "3. Buscar imoveis\n"<<
                 "4. Remover imoveis\n"<<
                 "5. Editar imoveis\n"<<
                 "6. Sair\n";

    while(1){
        i = getch();

        switch(i){
            case '1':
                cadastro();
                break;

            case '2':
                consulta();
                break;

            case '3':
                busca();
                break;

            case '4':
                remover();
                break;

            case '5':
                editar();
                break;

            case '6':
                imobiliaria->salvarImoveis();
                exit(0);
                break;

            default:
               std::cout << "\nInsira uma opcao valida\n";
        }
    }
}
