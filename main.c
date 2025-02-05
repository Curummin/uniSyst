#include <stdio.h>
#include "uni.h"

int menu();

int menu()
{
    int opcao;

    printf("\n===========================MENU===========================\n");
    printf("1) Insere Universidade\n");
    printf("2) Insere Aluno\n");
    printf("3) Busca Universidade\n");
    printf("4) Busca Aluno\n");
    printf("5) Remove Universidade\n");
    printf("6) Remove Aluno\n");
    printf("0) Fechar\n");
    printf("==========================================================\n");

    printf("Selecione uma das opcoes acima: ");
    scanf("%d", &opcao);

    return opcao;
}

int main()
{

    Universidade *inicio = NULL;
    recuperaDados(&inicio);

    int opcao = 90;
    char nomeUni[30];
    char nomeAluno[30];
    int matricula, idade, nmrDisciplinas;

    while (opcao != 0)
    {
        opcao = menu();

        switch (opcao)
        {
        case 1:

            printf("Digite o nome da universidade a ser inserida: ");
            fflush(stdin);
            scanf("%s", nomeUni);

            insereUniversidade(&inicio, nomeUni);
            break;

        case 2:

            printf("Entre com a idade, numero de matricula e numero de disciplinas: ");
            scanf("%d %d %d", &idade, &matricula, &nmrDisciplinas);

            printf("Entre com o nome do aluno e da universidade: ");
            fflush(stdin);
            scanf("%s %s", nomeAluno, nomeUni);

            insereAluno(&inicio, nomeUni, nomeAluno, matricula, idade, nmrDisciplinas);

            break;

        case 3:

            printf("Entre com o nome da universidade: ");
            fflush(stdin);
            scanf("%s", nomeUni);

            buscaUniversidade(&inicio, nomeUni);
            break;

        case 4:

            printf("Entre com o numero de matricula: ");
            scanf("%d", &matricula);
            break;

        case 5:

            printf("Entre com o nome da universidade: ");
            fflush(stdin);
            scanf("%s", nomeUni);
            removeUniversidade(&inicio, nomeUni);
            break;

        case 6:

            printf("Entre com o nome da universidade e do aluno");
            fflush(stdin);
            scanf("%s %s", nomeUni, nomeAluno);
            removeAluno(&inicio, nomeUni, matricula);
            break;

        default:
            break;
        }
    }

    imprimeUni(&inicio);
    salvaDados(inicio);

    return 0;
}