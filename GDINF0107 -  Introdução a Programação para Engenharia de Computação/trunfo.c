#include <conio.h>
#include <stdlib.h>

#define TEMA 0
#define QNTD_CARTAS 4
#define QNTD_ATRIBUTOS 4

static int carta[QNTD_CARTAS][QNTD_ATRIBUTOS];

int Random(int n){
    srand(time(NULL));
    return rand()%n+1;
}

int Seta(){
    int a, b;

    b = getch();
    a = getch();

    if (b == 224){
        if(a == 75)
            return 0;
        if(a == 72)
            return 1;
        if(a == 80)
            return 2;
        if(a == 77)
            return 3;
    }else
        return b;
}

void VoltarMenu(int menu){
    printf("\n\nPressione uma tecla para voltar ao menu");
    if(getch() == 224)
        getch();
    if(menu == 2)
        SubMenuCartas();
}

void ListarCartas(){
    int i, j = 0;

    system("cls");
    for(i = 0; i < QNTD_CARTAS; i++){
        printf("-----=====Carta %d=====-----\n", i+1);
        printf("\tForca: %d\n", carta[i][j]);
        printf("\tAgilidade: %d\n", carta[i][j+1]);
        printf("\tInteligencia: %d\n", carta[i][j+2]);
        printf("\tCarisma: %d\n\n", carta[i][j+3]);
    }
    VoltarMenu(2);
}

void RegistrarCarta(){
    int i, j = 0, num;
    system("cls");

    printf("Digite o numero da carta a ser editada: ");
    scanf("%d", &num);

    printf("\n-----=====Carta %d=====-----\n", num);

    printf("\tForca: ");
    scanf("%d", &carta[num-1][0]);

    printf("\tAgilidade: ");
    scanf("%d", &carta[num-1][1]);

    printf("\tInteligencia: ");
    scanf("%d", &carta[num-1][2]);

    printf("\tCarisma: ");
    scanf("%d", &carta[num-1][3]);

    VoltarMenu(2);
}

void ApagarCarta(){
    int i, j;

    system("cls");

    while(1){
        printf("Digite o numero da carta a ser apagada: ");
        scanf("%d", &i);

        printf("\n\n-----=====Carta %d=====-----\n", i--);
        printf("\tForca: %d\n", carta[i][0]);
        printf("\tAgilidade: %d\n", carta[i][1]);
        printf("\tInteligencia: %d\n", carta[i][2]);
        printf("\tCarisma: %d\n\n", carta[i][3]);

        printf("\n\nEh esta a carta a ser apagada?(s/n)");
        if(getche() == 'n' || getche() == 'N')
            continue;

        for(j = 0; j < QNTD_ATRIBUTOS; j++){
            carta[i][j] = 0;
        }
        break;
    }

    VoltarMenu(2);
}

void ExibirSplash(int n){
    int i;

    printf("Loading");

    for(i = 2; i <= n; i++);
    printf(".");

    for(i = 2; i <= n; i++);
    printf(".");

    for(i = 2; i <= n; i++);
    printf(".\n\n");

    system("cls");
}

void Login(char *j1[10], char *j2[10]){
    printf("Insira o nome do jogador 1\n");
    scanf("%s", j1);

    printf("Insira o nome do jogador 2\n");
    scanf("%s", j2);
}

void SeletorMenu(int tipo, int n){
        switch(n){
            case 1:
                if(tipo == 2)
                    RegistrarCarta();
                break;
            case 2:
                if(tipo == 2)
                    RegistrarCarta();
                break;
            case 3:
                if(tipo == 2)
                    ApagarCarta();
                if(tipo == 0)
                    SubMenuTemas();
                break;
            case 4:
                if(tipo == 0)
                    SubMenuCartas();
                if(tipo == 2)
                    ListarCartas();
                break;
            case 5:
                if(tipo == 0)
                    exit(0);
                break;
            case 6:
                break;
            default:
                printf("\nInsira uma opcao valida\n");
        }
}

void ExibirMenu(){
    int num = 1, c;

    while(1){
        system("cls");
        printf("---------=========Menu=========---------\n");
        printf("%s1. Jogar\n", num==1?"\t":"");
        printf("%s2. Exibir ranking\n", num==2?"\t":"");
        printf("%s3. Gerenciar temas\n", num==3?"\t":"");
        printf("%s4. Gerenciar cartas de um tema\n", num==4?"\t":"");
        printf("%s5. Sair\n\n", num==5?"\t":"");
        printf("NUM = %d\n", num);
        printf("CHAR = %d", c);

        c = Seta();

        if(c == 1 && num != 1)
            num--;
        if(c == 2 && num != 5)
            num++;
        if(c == 13){
            SeletorMenu(0, num);
            break;
        }
    }
}

void SubMenuTemas(){
    system("cls");
    printf("--------========Menu Temas========--------\n"
           "1. Escolher Tema do Jogo\n"
           "2. Listar Temas\n"
           "3. Cadastrar Tema\n"
           "4. Editar Tema\n"
           "5. Apagar Tema\n"
           "6. Voltar ao Menu Principal\n\n");
}

void SubMenuCartas(){
    system("cls");
    printf("--------========Menu Cartas========--------\n"
           "1. Cadastrar uma carta\n"
           "2. Editar uma carta\n"
           "3. Apagar uma carta\n"
           "4. Listar todas as cartas cadastradas\n"
           "5. Listar uma ou mais cartas ordenadas de acordo um criterio de busca\n"
           "6. Voltar ao Menu Principal\n\n");
}

int main(){
    char j1[10], j2[10];

    //ExibirSplash(555555555);
    //Login(&j1, &j2);
    ExibirMenu();

    return 0;
}
