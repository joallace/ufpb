#include <stdio.h>
#include <strings.h>
#include <stdlib.h>

#define QNT_IMOVEIS 10

typedef enum {VENDA, ALUGUEL} tTipo;

typedef struct{
    //Variáveis de localização
    char rua[101];
    char bairro[31];
    char cep[11];
    char cidade[51];
    int numero;

    //Variáveis de negociação
    double valor;
    tTipo tipo;
    char ativo; //Define se o anúncio está ativo ou inativo

    //Variáveis de descrição
    char titulo[201];
    int nPavimentos;
    int nQuartos;
    float areaTotal;
    float areaConstruida;

}tCasa;

typedef struct {
    //Variáveis de localização
    char rua[101];
    char bairro[31];
    char cep[11];
    char cidade[51];
    int numero;

    //Variáveis de negociação
    double valor;
    tTipo tipo;
    char ativo;


    //Variáveis de descrição
    char titulo[201];
    int nQuartos;
    float areaTotal;
    char posicao[31];
    int nAndares;
    float valorCondominio;
    int vagasGaragem;

}tApartamento;

typedef struct{
    //Variáveis de localização
    char rua[101];
    char bairro[31];
    char cep[11];
    char cidade[51];
    int numero;

    //Variáveis de negociação
    double valor;
    tTipo tipo;
    char ativo;

    //Variáveis de descrição
    char titulo[201];
    float areaTotal;
}tTerreno;

//Declara as listas de imóveis no escopo global
tCasa casas[QNT_IMOVEIS] = {};
tApartamento apartamentos[QNT_IMOVEIS] = {};
tTerreno terrenos[QNT_IMOVEIS] = {};

//Função de leitura de Strings, que remove o \n no final
void scans(char *str, int num){
    int i;

    fgets(str, num, stdin);

    for(i = 0; i <= num; i++){
        if(str[i] == '\n'){
            str[i] = '\0';
            break;
        }
    }
}

//Confirma a saida para o menu
void ConfirmaSaida(){
	printf("\n\nPressione uma tecla para voltar ao menu");
    if(getch() == 224)
        getch();
    system("cls");
    ExibirMenu();
}

void ImprimeCasa(int num){
    printf("\n\nTitulo: %s", casas[num].titulo);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Tipo: Casa\n");
    printf("Forma de negocio: %s\n", casas[num].tipo == VENDA? "VENDA" : "ALUGUEL");
    printf("Valor %s: %.2lf\n", casas[num].tipo == VENDA? "de venda" : "do aluguel", casas[num].valor);

    printf("\n-------Caracteristicas do Imovel-------\n");
    printf("Quantidade de quartos: %d\n", casas[num].nQuartos);
    printf("Quantidade de pavimentos: %d\n", casas[num].nPavimentos);
    printf("Area construida: %.2f\n", casas[num].areaConstruida);
    printf("Area total: %.2f\n", casas[num].areaTotal);

    printf("\n--------------Localizacao--------------\n");
    printf("CEP: %s\n", casas[num].cep);
    printf("Cidade: %s\n", casas[num].cidade);
    printf("Bairro: %s\n", casas[num].bairro);
    printf("Rua: %s\n", casas[num].rua);
    printf("Numero: %d\n\n", casas[num].numero);

}

void ImprimeApt(int num){
    printf("\n\nTitulo: %s", apartamentos[num].titulo);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Tipo: Apartamento\n");
    printf("Forma de negocio: %s\n", apartamentos[num].tipo == VENDA? "VENDA" : "ALUGUEL");
    printf("Valor %s: %.2lf\n", apartamentos[num].tipo == VENDA? "de venda" : "do aluguel", apartamentos[num].valor);

    printf("\n-------Caracteristicas do Imovel-------\n");
    printf("Quantidade de quartos: %d\n", apartamentos[num].nQuartos);
    printf("Quantidade de andares: %d\n", apartamentos[num].nAndares);
    printf("Posicao: %s\n", apartamentos[num].posicao);
    printf("Vagas na garagem: %d\n", apartamentos[num].vagasGaragem);
    printf("Valor do condominio: %.2f\n", apartamentos[num].valorCondominio);
    printf("Area total: %.2f\n", apartamentos[num].areaTotal);

    printf("\n--------------Localizacao--------------\n");
    printf("CEP: %s\n", apartamentos[num].cep);
    printf("Cidade: %s\n", apartamentos[num].cidade);
    printf("Bairro: %s\n", apartamentos[num].bairro);
    printf("Rua: %s\n", apartamentos[num].rua);
    printf("Numero: %d\n\n", apartamentos[num].numero);


}

void ImprimeTerreno(int num){
    printf("\n\nTitulo: %s", terrenos[num].titulo);
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("Tipo: Terreno\n");
    printf("Forma de negocio: %s\n", terrenos[num].tipo == VENDA? "VENDA" : "ALUGUEL");
    printf("Valor %s: %.2lf\n", terrenos[num].tipo == VENDA? "de venda" : "do aluguel", terrenos[num].valor);

    printf("\n-------Caracteristicas do Imovel-------\n");
    printf("Area total: %.2f\n", terrenos[num].areaTotal);

    printf("\n--------------Localizacao--------------\n");
    printf("CEP: %s\n", terrenos[num].cep);
    printf("Cidade: %s\n", terrenos[num].cidade);
    printf("Bairro: %s\n", terrenos[num].bairro);
    printf("Rua: %s\n", terrenos[num].rua);
    printf("Numero: %d\n\n", terrenos[num].numero);

}



void Consulta(){
    int i, j, k = 0;

    system("cls");
	printf("---------=========Consulta=========---------\n\n");
	printf("1. Casa\n"
	   	   "2. Apartamento\n"
	       "3. Terreno\n\n"
	       "Escolha o tipo de imovel, ou digite 0 para retornar: ");
	scanf("%d%*c", &i);

	if(!i)
        ExibirMenu();

	printf("\n\n1. Venda\n"
			"2. Aluguel\n\n"
			"Escolha o tipo de negocio: ");
	scanf("%d%*c", &j);
    system ("cls");
	//Checando cada situação
	if(i == 1 && j == 1){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(casas[i].ativo && casas[i].tipo == VENDA){
				ImprimeCasa(i);
				k++;
			}
		}
	}

	if(i == 1 && j == 2){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(casas[i].ativo && casas[i].tipo == ALUGUEL){
				ImprimeCasa(i);
				k++;
			}
		}
	}

	if(i == 2 && j == 1){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(apartamentos[i].ativo && apartamentos[i].tipo == VENDA){
				ImprimeApt(i);
				k++;
			}
		}
	}

	if(i == 2 && j == 2){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(apartamentos[i].ativo && apartamentos[i].tipo == ALUGUEL){
				ImprimeApt(i);
				k++;
			}
		}
	}

	if(i == 3 && j == 1){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(terrenos[i].ativo && terrenos[i].tipo == VENDA){
				ImprimeTerreno(i);
				k++;
			}
		}
	}

	if(i == 3 && j == 2){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(terrenos[i].ativo && terrenos[i].tipo == ALUGUEL){
				ImprimeTerreno(i);
				k++;
			}
		}
	}

	//Caso ele não tenha printado nada, ou seja, k == 0, é informado que não há nenhum imóvel disponível
	if(k == 0){
		printf("\n\nNao ha imoveis disponiveis nessa categoria\n\n");
	}


    ConfirmaSaida();
}

void ConsultaDisponiveis(){
    int i, soma;

    system("cls");
	printf("---------=========Consulta Imoveis Disponiveis=========---------\n\n");
	printf("1. Venda\n"
	   	   "2. Aluguel\n"
	       "3. Todos\n\n"
	       "Escolha o tipo de negocio, ou digite 0 para retornar: ");
	scanf("%d%*c", &i);

	if(!i)
        ExibirMenu();

    switch(i){
        case 1:
            printf("---------=========Casas=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(casas[i].ativo && casas[i].tipo == VENDA){
                    ImprimeCasa(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha casas disponiveis\n");


            printf("\n\n---------=========Apartamentos=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(apartamentos[i].ativo && apartamentos[i].tipo == VENDA){
                    ImprimeApt(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha apartamentos disponiveis\n");

             printf("\n\n---------=========Terrenos=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(terrenos[i].ativo && terrenos[i].tipo == VENDA){
                    ImprimeTerreno(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha terrenos disponiveis\n");
            break;

        case 2:
            printf("---------=========Casas=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(casas[i].ativo && casas[i].tipo == ALUGUEL){
                    ImprimeCasa(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha casas disponiveis\n");


            printf("\n\n---------=========Apartamentos=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(apartamentos[i].ativo && apartamentos[i].tipo == ALUGUEL){
                    ImprimeApt(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha apartamentos disponiveis\n");

             printf("\n\n---------=========Terrenos=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(terrenos[i].ativo && terrenos[i].tipo == ALUGUEL){
                    ImprimeTerreno(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha terrenos disponiveis\n");
            break;


        case 3:
            printf("---------=========Casas=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(casas[i].ativo){
                    ImprimeCasa(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha casas disponiveis\n");


            printf("\n\n---------=========Apartamentos=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(apartamentos[i].ativo){
                    ImprimeApt(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha apartamentos disponiveis\n");

             printf("\n\n---------=========Terrenos=========---------\n");
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(terrenos[i].ativo){
                    ImprimeTerreno(i);
                    soma++;
                }
            }
            if(!soma)
                printf("Nao ha terrenos disponiveis\n");
            break;
    }

    ConfirmaSaida();
}

void SalvaCasa(tCasa lista[]){
    FILE* arq = fopen("data.bin", "wb");
    if(arq>0){
        fwrite(lista,QNT_IMOVEIS,sizeof(tCasa),arq);
        fclose(arq);
        printf("Casas salvas com sucesso\n");
    }else{
        printf("Erro ao abrir o arquivo\n");
    }
}

void SalvaApartamento(tApartamento lista[]){
    FILE* arq = fopen("data2.bin", "wb");
    if(arq>0){
        fwrite(lista,QNT_IMOVEIS,sizeof(tApartamento),arq);
        fclose(arq);
        printf("Apartamentos salvos com sucesso\n");
    }else{
        printf("Erro ao abrir o arquivo\n");
    }
}

void SalvaTerreno(tTerreno lista[]){
    FILE* arq = fopen("data3.bin", "wb");
    if(arq>0){
        fwrite(lista,QNT_IMOVEIS,sizeof(tTerreno),arq);
        fclose(arq);
        printf("Terrenos salvos com sucesso\n");
    }else{
        printf("Erro ao abrir o arquivo\n");
    }
}


void LerCasa(tCasa lista[]){
    FILE* arq = fopen("data.bin","rb");
    if(arq>0){

        fread(lista,QNT_IMOVEIS,sizeof(tCasa),arq);
        fclose(arq);
        printf("Leitura de casas feita com sucesso\n");

    }else{
        printf("Erro ao abrir  o arquivo para leitura\n");
    }

}

void LerApartamento(tApartamento lista[]){
    FILE* arq = fopen("data2.bin","rb");
    if(arq>0){

        fread(lista,QNT_IMOVEIS,sizeof(tApartamento),arq);
        fclose(arq);
        printf("Leitura de apartamentos feita com sucesso\n");
    }else{

        printf("Erro ao abrir  o arquivo para leitura\n");
    }
}
void LerTerreno(tTerreno lista[]){
    FILE* arq = fopen("data3.bin","rb");
    if(arq>0){

        fread(lista,QNT_IMOVEIS,sizeof(tTerreno),arq);
        fclose(arq);
        printf("Leitura de terrenos feita com sucesso\n");
    }else{

        printf("Erro ao abrir  o arquivo para leitura\n");
    }
}

void Cadastro(){
    int i, tTipo; //Esta variável será utilizada tanto para o switch e para os fors

    system("cls");

    printf("---------=========Cadastro=========---------\n\n");
    printf("1. Casa\n"
           "2. Apartamento\n"
           "3. Terreno\n\n"
           "Escolha o tipo de imovel, ou digite 0 para voltar: ");

    scanf("%d%*c", &i);

	if(!i){
		system("cls");
		ExibirMenu();
	}

    switch(i){
        case 1:
            for(i = 0; i <= QNT_IMOVEIS; i++){
                if(!casas[i].ativo){
                    printf("\nInsira o titulo do anuncio: ");
                    scans(casas[i].titulo, 201);

                    printf("\nInsira o numero de pavimentos: ");
                    scanf("%d", &casas[i].nPavimentos);

                    printf("\nInsira o numero de quartos: ");
                    scanf("%d", &casas[i].nQuartos);

                    printf("\nInsira a area construida: ");
                    scanf("%f", &casas[i].areaConstruida);

                    printf("\nInsira a area total: ");
                    scanf("%f%*c", &casas[i].areaTotal);

                    printf("\nInsira o CEP: ");
                    scans(casas[i].cep, 11);

                    printf("\nInsira a cidade: ");
                    scans(casas[i].cidade, 51);

                    printf("\nInsira o bairro: ");
                    scans(casas[i].bairro, 31);

                    printf("\nInsira a rua: ");
                    scans(casas[i].rua, 101);

                    printf("\nInsira o numero da casa: ");
                    scanf("%d%*c", &casas[i].numero);

                    printf("\n1.Venda\n2.Aluguel\n\nEscolha o tipo de negocio: ");

                    do{
                        scanf("%d%*c", &tTipo);
                        if(tTipo == 1)
                            casas[i].tipo = VENDA;
                        else if(tTipo == 2)
                            casas[i].tipo = ALUGUEL;
                            else
                                printf("Insira uma opcao valida");
                    }while(tTipo < 1 || tTipo > 2);

                    printf("\nInsira o preco %s: ", casas[i].tipo == VENDA? "de venda" : "do aluguel");
                    scanf("%lf", &casas[i].valor);

                    casas[i].ativo = 1;
                    printf("Cadastro de numero %d realizado com sucesso!", i + 1);

                    break;
                }
            }
        break;

        case 2:
            for(i = 0; i <= QNT_IMOVEIS; i++){
                if(!apartamentos[i].ativo){
                    printf("\nInsira o titulo do anuncio: ");
                    scans(apartamentos[i].titulo, 201);

                    printf("\nInsira o numero de quartos: ");
                    scanf("%d", &apartamentos[i].nQuartos);

                    printf("\nInsira o numero de andares: ");
                    scanf("%d", &apartamentos[i].nAndares);

                    printf("\nInsira a area total: ");
                    scanf("%f", &apartamentos[i].areaTotal);

                    printf("\nInsira o numero de vagas na garagem: ");
                    scanf("%d%*c", &apartamentos[i].vagasGaragem);

                    printf("\nInsira a posicao do apartamento: ");
                    scans(apartamentos[i].posicao, 31);

                    printf("\nInsira o valor do condominio: ");
                    scanf("%f%*c", &apartamentos[i].valorCondominio);

                    printf("\nInsira o CEP: ");
                    scans(apartamentos[i].cep, 11);

                    printf("\nInsira a cidade: ");
                    scans(apartamentos[i].cidade, 51);

                    printf("\nInsira o bairro: ");
                    scans(apartamentos[i].bairro, 31);

                    printf("\nInsira a rua: ");
                    scans(apartamentos[i].rua, 101);

                    printf("\nInsira o numero do predio: ");
                    scanf("%d%*c", &apartamentos[i].numero);

                    printf("\n1.Venda\n2.Aluguel\n\nEscolha o tipo de negocio: ");
                    do{
                        scanf("%d%*c", &tTipo);
                        if(tTipo == 1)
                            apartamentos[i].tipo = VENDA;
                        else if(tTipo == 2)
                            apartamentos[i].tipo = ALUGUEL;
                            else
                                printf("Insira uma opcao valida");
                    }while(tTipo < 1 || tTipo > 2);

                    printf("\nInsira o preco %s: ", apartamentos[i].tipo == VENDA? "de venda" : "do aluguel");
                    scanf("%lf", &apartamentos[i].valor);

                    apartamentos[i].ativo = 1;
                    printf("Cadastro de numero %d realizado com sucesso!", i + 1);

                    break;
                }
            }
        break;

        case 3:
            for(i = 0; i <= QNT_IMOVEIS; i++){
                if(!terrenos[i].ativo){
                    printf("\nInsira o titulo do anuncio: ");
                    scans(terrenos[i].titulo, 201);

                    printf("\nInsira a area do terreno: ");
                    scanf("%f%*c", &terrenos[i].areaTotal);

                    printf("\nInsira o CEP: ");
                    scans(terrenos[i].cep, 11);

                    printf("\nInsira a cidade: ");
                    scans(terrenos[i].cidade, 51);

                    printf("\nInsira o bairro: ");
                    scans(terrenos[i].bairro, 31);

                    printf("\nInsira a rua: ");
                    scans(terrenos[i].rua, 101);

                    printf("\nInsira o numero: ");
                    scanf("%d", &terrenos[i].numero);

                    printf("\n1.Venda\n2.Aluguel\n\nEscolha o tipo de negocio: ");
                    do{
                        scanf("%d%*c", &tTipo);
                        if(tTipo == 1)
                            terrenos[i].tipo = VENDA;
                        else if(tTipo == 2)
                            terrenos[i].tipo = ALUGUEL;
                            else
                                printf("Insira uma opcao valida");
                    }while(tTipo < 1 || tTipo > 2);
                    printf("\nInsira o preco %s: ", terrenos[i].tipo == VENDA? "de venda" : "do aluguel");
                    scanf("%lf", &terrenos[i].valor);

                    terrenos[i].ativo = 1;
                    printf("Cadastro de numero %d realizado com sucesso!", i + 1);

                    break;
                }
            }
    }
    ConfirmaSaida();
}

void BuscaPreco(){
    int i, j, k, //Variáveis de seleção
    s = 0; //Contador de casos encontrados
    double valor;

    system("cls");

	printf("---------=========Busca por Preco=========---------\n\n");
	printf("1. Casa\n"
	   	   "2. Apartamento\n"
	       "3. Terreno\n\n"
	       "Escolha o tipo de imovel, ou digite 0 para voltar: ");

    do{
        scanf("%d%*c", &i);
        if(i < 0 || i > 3)
            printf("Insira uma opcao valida");
    }while(i < 0 || i > 3);

	if(!i)
        MenuBusca();

	printf("\n\n1. Venda\n"
			"2. Aluguel\n"
			"Escolha o tipo de negocio: ");

    do{
        scanf("%d%*c", &j);
        if(j < 1 || j > 2)
            printf("Insira uma opcao valida");
    }while(j < 1 || j > 2);

	printf("\n\nProcurar um valor: \n"
			"1. Maior\n"
			"2. Menor\n"
			"Escolha uma opcao de busca: ");

    do{
        scanf("%d%*c", &k);
        if(k < 1 || k > 2)
            printf("Insira uma opcao valida");
    }while(k < 1 || k > 2);

	printf("\n\nInsira o valor: ");
	scanf("%lf", &valor);

	//Checando cada situação
	if(i == 1 && j == 1){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(casas[i].ativo && casas[i].tipo == VENDA){
                if(k == 1 && casas[i].valor >= valor){
                    ImprimeCasa(i);
                    s++;
                } else if(k == 2 && casas[i].valor <= valor){
                    ImprimeCasa(i);
                    s++;
                }
			}
		}
	}

	if(i == 1 && j == 2){
		for(i = 0; i < QNT_IMOVEIS; i++){
			if(casas[i].ativo && casas[i].tipo == ALUGUEL){
                if(k == 1 && casas[i].valor >= valor){
                    ImprimeCasa(i);
                    s++;
                } else if(k == 2 && casas[i].valor <= valor){
                    ImprimeCasa(i);
                    s++;
                }
			}
		}
	}

	if(i == 2 && j == 1){
        for(i = 0; i < QNT_IMOVEIS; i++){
			if(apartamentos[i].ativo && apartamentos[i].tipo == VENDA){
                if(k == 1 && apartamentos[i].valor >= valor){
                    ImprimeApt(i);
                    s++;
                } else if(k == 2 && apartamentos[i].valor <= valor){
                    ImprimeApt(i);
                    s++;
                }
			}
		}
	}

	if(i == 2 && j == 2){
        for(i = 0; i < QNT_IMOVEIS; i++){
			if(apartamentos[i].ativo && apartamentos[i].tipo == ALUGUEL){
                if(k == 1 && apartamentos[i].valor >= valor){
                    ImprimeApt(i);
                    s++;
                } else if(k == 2 && apartamentos[i].valor <= valor){
                    ImprimeApt(i);
                    s++;
                }
			}
		}
	}
	if(i == 3 && j == 2){
        for(i = 0; i < QNT_IMOVEIS; i++){
			if(terrenos[i].ativo && terrenos[i].tipo == VENDA){
                if(k == 1 && terrenos[i].valor >= valor){
                    ImprimeTerreno(i);
                    s++;
                } else if(k == 2 && terrenos[i].valor <= valor){
                    ImprimeTerreno(i);
                    s++;
                }
			}
		}
	}

	if(i == 3 && j == 2){
        for(i = 0; i < QNT_IMOVEIS; i++){
			if(terrenos[i].ativo && terrenos[i].tipo == VENDA){
                if(k == 1 && terrenos[i].valor >= valor){
                    ImprimeTerreno(i);
                    s++;
                } else if(k == 2 && terrenos[i].valor <= valor){
                    ImprimeTerreno(i);
                    s++;
                }
			}
		}
	}

	//Caso ele não tenha printado nada, ou seja, s == 0, é informado que não há nenhum imóvel disponível
	if(s == 0){
		printf("\n\nNao ha imoveis disponiveis nesses criterios\n\n");
	}


    ConfirmaSaida();
}

void BuscaTitulo(){
    char titulo[201];
    int i, soma = 0;

    system("cls");
    printf("---------=========Busca por Titulo=========---------\n");
    printf("Digite o titulo a ser pesquisado:\n");
    scans(titulo, 201);

    for(i = 0; i < QNT_IMOVEIS; i++){
        if(casas[i].ativo && !strcmp(titulo, casas[i].titulo)){
            ImprimeCasa(i);
            soma++;
       }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if(apartamentos[i].ativo && !strcmp(titulo, apartamentos[i].titulo)){
            ImprimeApt(i);
            soma++;
        }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if(terrenos[i].ativo && !strcmp(titulo, apartamentos[i].titulo)){
            ImprimeTerreno(i);
            soma++;
        }
    }

    if(soma == 0){
        printf("\n\nNao ha imoveis disponiveis com esse titulo\n\n");
    }

    ConfirmaSaida();
}

void BuscaBairro(){
    char bairro[31];
    int i, soma = 0;

    system("cls");

    printf("---------=========Busca por Bairro=========---------\n");
    printf("Digite o bairro a ser pesquisado:\n");
    scans(bairro, 31);

    for(i = 0; i < QNT_IMOVEIS; i++){
        if(casas[i].ativo && !strcmp(bairro, casas[i].bairro)){
            ImprimeCasa(i);
            soma++;
       }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if(apartamentos[i].ativo && !strcmp(bairro, apartamentos[i].bairro)){
            ImprimeApt(i);
            soma++;
        }
    }

    for(i = 0; i < QNT_IMOVEIS; i++){
        if(terrenos[i].ativo && !strcmp(bairro, terrenos[i].bairro)){
            ImprimeTerreno(i);
            soma++;
        }
    }

    if(soma == 0){
        printf("\n\nNao ha imoveis disponiveis nesse bairro\n\n");
    }

    ConfirmaSaida();
}

void Remover(){
    int i, soma;

    system("cls");

    //seleção do tipo de imovel a ser removido
    printf("---------=========Remover Imovel=========---------\n\n");
    printf("1.Casas\n"
           "2.Apartamentos\n"
           "3.Terrenos\n"
	       "\nInsira o tipo de imovel, ou digite 0 para voltar: ");

    do{
        scanf("%d%*c", &i);
        if(i < 0 || i > 3)
            printf("Insira uma opcao valida");
    }while(i < 0 || i > 3);

	if(!i)
        MenuBusca();

    //impressão dos imoveis cadastrados na categoria desejada
    switch(i){

        case 1:
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(casas[i].ativo){

                    printf("---------=========Casa %d=========---------\n", i+1);
                    ImprimeCasa(i);
                    soma++;
               }
            }
            if(!soma){
                printf("Nao ha casas disponiveis\n");
                ConfirmaSaida();
                break;
            }

            printf("Insira o numero da casa a ser removida: ");
            scanf("%d%*c", &i);

            casas[--i].ativo = 0;

            ConfirmaSaida();

            break;

        case 2:
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(apartamentos[i].ativo){
                    printf("---------=========Apartamento %d=========---------\n", i+1);
                    ImprimeApt(i);
                    soma++;
                }
            }
            if(!soma){
                printf("Nao ha apartamentos disponiveis\n");
                ConfirmaSaida();
                break;
            }

            printf("Insira o numero do apartamento a ser removido: ");
            scanf("%d", &i);

            apartamentos[--i].ativo = 0;

            ConfirmaSaida();

            break;

        case 3:
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(terrenos[i].ativo){
                    printf("---------=========Terreno %d=========---------\n", i+1);
                    ImprimeTerreno(i);
                    soma++;
                }
            }
            if(!soma){
                printf("Nao ha terrenos disponiveis\n");
                ConfirmaSaida();
                break;
            }

            printf("Insira o numero do terreno a ser removido: ");
            scanf("%d", &i);

            terrenos[--i].ativo = 0;

            ConfirmaSaida();

            break;

    }
}

void Editar(){
    int i, j, soma, tTipo;

    system("cls");

    //seleção do tipo de imovel a ser editado
    printf("---------=========Editar Imovel=========---------\n\n");
    printf("1.Casas\n"
           "2.Apartamentos\n"
           "3.Terrenos\n"
	       "\nInsira o tipo de imovel, ou digite 0 para voltar: ");

    do{
        scanf("%d", &i);
        if(i < 0 || i > 3)
            printf("Insira uma opcao valida\n");
    }while(i < 0 || i > 3);

    system("cls");


	if(!i)
        MenuBusca();

    switch(i){

        case 1:
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(casas[i].ativo){

                    printf("---------=========Casa %d=========---------\n", i+1);
                    ImprimeCasa(i);
                    soma++;
               }
            }
            if(!soma){
                printf("Nao ha casas disponiveis\n");
                ConfirmaSaida();
                break;
            }

            printf("Insira o numero da casa a ser editada: ");
            scanf("%d%*c", &i);
            i--;

            while(1){
                system ("cls");
                printf("\n\n1. Titulo\n"
                       "2. Numero de Pavimentos\n"
                       "3. Numero de Quartos\n"
                       "4. Area construida\n"
                       "5. Area Total\n"
                       "6. CEP\n"
                       "7. Cidade\n"
                       "8. Bairro\n"
                       "9. Rua\n"
                       "10. Numero da casa\n"
                       "11. Tipo de negocio\n"
                       "12. Preco\n"
                       "\n\nDigite o campo a ser alterado, ou digite 0 para retornar: \n");

                do{
                    scanf("%d%*c", &j);
                    if(!j)
                        ExibirMenu();
                    if(j < 0 || j > 13)
                        printf("Insira uma opcao valida\n");
                }while(j < 0 || j > 13);

                system("cls");

                switch(j){
                    case 1:
                        printf("\nInsira o titulo do anuncio: ");
                        scans(casas[i].titulo, 201);
                        break;

                    case 2:
                        printf("\nInsira o numero de pavimentos: ");
                        scanf("%d", &casas[i].nPavimentos);
                        break;

                    case 3:
                        printf("\nInsira o numero de quartos: ");
                        scanf("%d", &casas[i].nQuartos);
                        break;

                    case 4:
                        printf("\nInsira a area construida: ");
                        scanf("%f", &casas[i].areaConstruida);
                        break;

                    case 5:
                        printf("\nInsira a area total: ");
                        scanf("%f%*c", &casas[i].areaTotal);
                        break;

                    case 6:
                        printf("\nInsira o CEP: ");
                        scans(casas[i].cep, 11);
                        break;

                    case 7:
                        printf("\nInsira a cidade: ");
                        scans(casas[i].cidade, 51);
                        break;

                    case 8:
                        printf("\nInsira o bairro: ");
                        scans(casas[i].bairro, 31);
                        break;

                    case 9:
                        printf("\nInsira a rua: ");
                        scans(casas[i].rua, 101);
                        break;

                    case 10:
                        printf("\nInsira o numero da casa: ");
                        scanf("%d%*c", &casas[i].numero);
                        break;

                    case 11:
                        printf("\n1.Venda\n2.Aluguel\n\nEscolha o tipo de negocio: ");
                        do{
                                scanf("%d%*c", &tTipo);
                                if(tTipo == 1)
                                    casas[i].tipo = VENDA;
                                else if(tTipo == 2)
                                    casas[i].tipo = ALUGUEL;
                                    else
                                    printf("Insira uma opcao valida");
                        }while(tTipo < 1 || tTipo > 2);
                        break;

                    case 12:
                        printf("\nInsira o preco %s: ", casas[i].tipo == VENDA? "de venda" : "do aluguel");
                        scanf("%lf", &casas[i].valor);
                        break;
                }
            }

            printf("Cadastro de numero %d alterado com sucesso!", i + 1);


            ConfirmaSaida();

            break;

        case 2:
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(apartamentos[i].ativo){
                    printf("---------=========Apartamento %d=========---------\n", i+1);
                    ImprimeApt(i);
                    soma++;
                }
            }
            if(!soma){
                printf("Nao ha apartamentos disponiveis\n");
                ConfirmaSaida();
                break;
            }

            printf("Insira o numero do apartamento a ser editado: ");
            scanf("%d%*c", &i);
            i--;

            while(1){
                system ("cls");
                printf("\n\n1. Titulo\n"
                       "2. Numero de Quartos\n"
                       "3. Numero de Andares\n"
                       "4. Area Total\n"
                       "5. Numero de vagas na garagem\n"
                       "6. Posicao do apartamento\n"
                       "7. Valor do condominio\n"
                       "8. CEP\n"
                       "9. Cidade\n"
                       "10. Bairro\n"
                       "11. Rua\n"
                       "12. Numero do predio\n"
                       "13. Tipo de negocio\n"
                       "14. Preco\n"
                       "\n\nDigite o campo a ser alterado, ou digite 0 para retornar: \n");

                do{
                    scanf("%d%*c", &j);
                    if(!j)
                        ExibirMenu();
                    if(j < 0 || j > 13)
                        printf("Insira uma opcao valida\n");
                }while(j < 0 || j > 13);

                system("cls");

                switch(j){
                    case 1:
                        printf("\nInsira o titulo do anuncio: ");
                        scans(apartamentos[i].titulo, 201);
                        break;

                    case 2:
                        printf("\nInsira o numero de quartos: ");
                        scanf("%d", &apartamentos[i].nQuartos);
                        break;

                    case 3:
                        printf("\nInsira o numero de andares: ");
                        scanf("%d", &apartamentos[i].nAndares);
                        break;
                    case 4:
                        printf("\nInsira a area total: ");
                        scanf("%f", &apartamentos[i].areaTotal);
                        break;

                    case 5:
                        printf("\nInsira o numero de vagas na garagem: ");
                        scanf("%d%*c", &apartamentos[i].vagasGaragem);
                        break;

                    case 6:
                        printf("\nInsira a posicao do apartamento: ");
                        scans(apartamentos[i].posicao, 31);
                        break;

                    case 7:
                        printf("\nInsira o valor do condominio: ");
                        scanf("%f%*c", &apartamentos[i].valorCondominio);
                        break;

                    case 8:
                        printf("\nInsira o CEP: ");
                        scans(apartamentos[i].cep, 11);
                        break;

                    case 9:
                        printf("\nInsira a cidade: ");
                        scans(apartamentos[i].cidade, 51);
                        break;

                    case 10:
                        printf("\nInsira o bairro: ");
                        scans(apartamentos[i].bairro, 31);
                        break;

                    case 11:
                        printf("\nInsira a rua: ");
                        scans(apartamentos[i].rua, 101);
                        break;

                    case 12:
                        printf("\nInsira o numero do predio: ");
                        scanf("%d%*c", &apartamentos[i].numero);
                        break;

                    case 13:
                        printf("\n1.Venda\n2.Aluguel\n\nEscolha o tipo de negocio: ");
                        do{
                                scanf("%d%*c", &tTipo);
                                if(tTipo == 1)
                                    apartamentos[i].tipo = VENDA;
                                else if(tTipo == 2)
                                    apartamentos[i].tipo = ALUGUEL;
                                    else
                                    printf("Insira uma opcao valida");
                        }while(tTipo < 1 || tTipo > 2);
                        break;

                    case 14:
                        printf("\nInsira o preco %s: ", apartamentos[i].tipo == VENDA? "de venda" : "do aluguel");
                        scanf("%lf", &apartamentos[i].valor);
                        break;
                }
            }

            printf("Cadastro de numero %d alterado com sucesso!", i + 1);


            ConfirmaSaida();

            break;

        case 3:
            for(i = 0, soma = 0; i < QNT_IMOVEIS; i++){
                if(terrenos[i].ativo){
                    printf("---------=========Terreno %d=========---------\n", i+1);
                    ImprimeTerreno(i);
                    soma++;
                }
            }
            if(!soma){
                printf("Nao ha terrenos disponiveis\n");
                ConfirmaSaida();
                break;
            }

            printf("Insira o numero do terreno a ser editado: ");
            scanf("%d%*c", &i);
            i--;

            while(1){
                system ("cls");
                printf("\n\n1. Titulo\n"
                        "2. Area do terreno\n"
                        "3. CEP\n"
                        "4. Cidade\n"
                        "5. Bairro\n"
                        "6. Rua\n"
                        "7. Numero do terreno\n"
                        "8. Tipo de negocio\n"
                        "9. Preco\n"
                        "\n\nDigite o campo a ser alterado, ou digite 0 para retornar: \n");

                do{
                    scanf("%d%*c", &j);
                    if(!j)
                        ExibirMenu();
                    if(j < 0 || j > 13)
                        printf("Insira uma opcao valida\n");
                }while(j < 0 || j > 13);

                system("cls");

                switch(j){
                    case 1:
                        printf("\nInsira o titulo do anuncio: ");
                        scans(terrenos[i].titulo, 201);
                        break;

                    case 2:
                        printf("\nInsira a area do terreno: ");
                        scanf("%f%*c", &terrenos[i].areaTotal);
                        break;

                    case 3:
                        printf("\nInsira o CEP: ");
                        scans(terrenos[i].cep, 11);
                        break;

                    case 4:
                        printf("\nInsira a cidade: ");
                        scans(terrenos[i].cidade, 51);
                        break;

                    case 5:
                        printf("\nInsira o bairro: ");
                        scans(terrenos[i].bairro, 31);
                        break;
                    case 6:
                        printf("\nInsira a rua: ");
                        scans(terrenos[i].rua, 101);
                        break;
                    case 7:
                        printf("\nInsira o numero: ");
                        scanf("%d", &terrenos[i].numero);
                        break;

                    case 8:
                        printf("\n1.Venda\n2.Aluguel\n\nEscolha o tipo de negocio: ");
                        do{
                                scanf("%d%*c", &tTipo);
                                if(tTipo == 1)
                                    terrenos[i].tipo = VENDA;
                                else if(tTipo == 2)
                                    terrenos[i].tipo = ALUGUEL;
                                    else
                                    printf("Insira uma opcao valida");
                        }while(tTipo < 1 || tTipo > 2);
                        break;

                    case 9:
                        printf("\nInsira o preco %s: ", terrenos[i].tipo == VENDA? "de venda" : "do aluguel");
                        scanf("%lf", &terrenos[i].valor);
                        break;
                }
            }

            printf("Cadastro de numero %d alterado com sucesso!", i + 1);


            ConfirmaSaida();

            break;

    }
}

void MenuBusca(){
    char i;

    system ("cls");

    printf("---------=========Buscar Imoveis=========---------\n");
    printf("1. Por titulo\n");
    printf("2. Por bairro\n");
    printf("3. Por preco\n");
    printf("4. Voltar\n");

    while(1){
        i = getch();

        switch(i){
            case '1':
               BuscaTitulo();
               break;

            case '2':
               BuscaBairro();
               break;

            case '3':
                BuscaPreco();
                break;

            case '4':
                ExibirMenu();
                break;

            default:
               printf("\nInsira uma opcao valida\n");
        }
    }
}


void ExibirMenu(){
    char i;

    system ("cls");

    printf("---------=========Menu=========---------\n");
    printf("1. Cadastrar imoveis\n");
    printf("2. Consultar imoveis\n");
    printf("3. Buscar imoveis\n"); //por titulo ou bairro ou valor
    printf("4. Imoveis disponiveis\n"); // para vender ou alugar
    printf("5. Remover imoveis\n");
    printf("6. Editar imoveis\n");
    printf("7. Salvar lista\n");
    printf("8. Ler lista\n");
    printf("9. Sair\n");

    while(1){
        i = getch();

        switch(i){
            case '1':
                Cadastro();
                break;

            case '2':
                Consulta();
                break;

            case '3':
                MenuBusca();
                break;

            case '4':
                ConsultaDisponiveis();
                break;

            case '5':
                Remover();
                break;

            case '6':
                Editar();
                break;

            case '7':
                system("cls");
                SalvaCasa(casas);
                SalvaApartamento(apartamentos);
                SalvaTerreno(terrenos);
                ConfirmaSaida();
                break;

            case '8':
                system("cls");
                LerCasa(casas);
                LerApartamento(apartamentos);
                LerTerreno(terrenos);
                ConfirmaSaida();
                break;

            case '9':
               exit(0);

            default:
               printf("\nInsira uma opcao valida\n");
        }
    }
}

int main(){
    ExibirMenu();
    return 0;
}
