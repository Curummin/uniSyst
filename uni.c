#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uni.h"

void insereUniversidade(Universidade **inicio, char *nomeUni)
{
    Universidade *aux = *inicio;

    while (aux != NULL)
    {
        if (strcmp(aux->nome, nomeUni) == 0)
        {
            printf("Universidade já cadastrada\n");
            return;
        }
        aux = aux->prox;
    }

    Universidade *nova_uni = (Universidade *)malloc(sizeof(Universidade));
    strcpy(nova_uni->nome, nomeUni);
    nova_uni->qtdAlunos = 0;
    nova_uni->inicioAluno = NULL;
    nova_uni->prox = NULL;

    aux = *inicio;
    Universidade *anterior = NULL;

    while (aux != NULL && strcmp(aux->nome, nova_uni->nome) < 0)
    {
        anterior = aux;
        aux = aux->prox;
    }
    if (anterior == NULL)
    {
        nova_uni->prox = *inicio;
        *inicio = nova_uni;
        printf("Universidade %s foi cadastrada com exito\n", nova_uni->nome);
        return;
    }
    if (aux == NULL)
    {
        anterior->prox = nova_uni;
        printf("Universidade %s foi cadastrada com exito\n", nova_uni->nome);
        return;
    }
    nova_uni->prox = anterior->prox;
    anterior->prox = nova_uni;

    printf("Universidade %s foi cadastrada com exito\n", nova_uni->nome);
    return;
}

void insereAluno(Universidade **inicio, char *nomeUni, char *nomeAluno, int matricula, int idade, int nroDisciplinas)
{
    Universidade *uni_atual = *inicio;

    while (uni_atual != NULL && strcmp(uni_atual->nome, nomeUni) != 0)
    {
        uni_atual = uni_atual->prox;
    }

    if (uni_atual == NULL)
    {
        int opcao;

        printf("Universidade nao cadastrada. Deseja cadastrar outra universidade? (1 para sim, 0 para nao): ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            insereUniversidade(inicio, nomeUni);
            uni_atual = *inicio;
        }
        else
        {
            printf("Cadastro cancelado");
            return;
        }
    }

    uni_atual->qtdAlunos++;

    Aluno *novo_aluno = (Aluno *)malloc(sizeof(Aluno));
    strcpy(novo_aluno->nome, nomeAluno);
    novo_aluno->matricula = matricula;
    novo_aluno->idade = idade;
    novo_aluno->nroDisciplinas = nroDisciplinas;
    novo_aluno->prox = NULL;

    Aluno *aluno_atual = uni_atual->inicioAluno;
    Aluno *anterior = NULL;

    while (aluno_atual != NULL && strcmp(aluno_atual->nome, nomeAluno) < 0)
    {
        anterior = aluno_atual;
        aluno_atual = aluno_atual->prox;
    }

    if (anterior == NULL)
    {
        novo_aluno->prox = uni_atual->inicioAluno;
        uni_atual->inicioAluno = novo_aluno;
        printf("Aluno %s cadastrado.\n", novo_aluno->nome);
        return;
    }
    if (aluno_atual == NULL)
    {
        anterior->prox = novo_aluno;
        printf("Aluno %s cadastrado.\n", novo_aluno->nome);
        return;
    }

    novo_aluno->prox = anterior->prox;
    anterior->prox = novo_aluno;
    printf("Aluno %s cadastrado.\n", novo_aluno->nome);

    return;
}

void buscaUniversidade(Universidade **inicio, char *nome)
{
    Universidade *aux = *inicio;

    while (aux != NULL && strcmp(aux->nome, nome) != 0)
        aux = aux->prox;

    if (aux == NULL)
        printf("Universidade %s nao cadastrada", nome);

    else
        printf("Universidade %s possui cadastro", nome);
}

void buscaAluno(Universidade **inicio, int matricula)
{
    Universidade *uni_atual = *inicio;
    int a = 0;

    while (uni_atual != NULL)
    {
        Aluno *aluno_atual = uni_atual->inicioAluno;

        while (aluno_atual != NULL)
        {
            if (aluno_atual->matricula == matricula)
            {
                a = 1;
                printf("Aluno com a matrícula %d encontrado na universidade %s\n", matricula, uni_atual->nome);
                return;
            }
            aluno_atual = aluno_atual->prox;
        }
        uni_atual = uni_atual->prox;
    }

    if (a == 0)
        printf("Aluno nao encontrado em nenhuma universidade\n");
}

void imprimeUni(Universidade **inicio)
{
    Universidade *aux = *inicio;

    printf("====================UNIVERSIDADES====================\n");

    while (aux != NULL)
    {
        printf("%s \n", aux->nome);
        printf("Numero de alunos: %d\n", aux->qtdAlunos);
        printf("=====================================================\n");
        aux = aux->prox;
    }
}

void removeUniversidade(Universidade **inicio, char *nomeUniversidade)
{
    Universidade *uni_atual = *inicio;
    Universidade *uni_anterior = NULL;

    while (uni_atual != NULL && strcmp(uni_atual->nome, nomeUniversidade) != 0)
    {
        uni_anterior = uni_atual;
        uni_atual = uni_atual->prox;
    }

    if (uni_atual == NULL)
    {
        printf("Universidade %s não encontrada na lista.\n", nomeUniversidade);
        return;
    }

    Aluno *aluno_atual = uni_atual->inicioAluno;
    while (aluno_atual != NULL)
    {
        Aluno *aluno_removido = aluno_atual;
        aluno_atual = aluno_atual->prox;
        free(aluno_removido);
    }

    if (uni_anterior == NULL)
        *inicio = uni_atual->prox;

    else
        uni_anterior->prox = uni_atual->prox;

    printf("Universidade %s não consta mais no sistema",uni_atual->nome);
    free(uni_atual);
}

void removeAluno(Universidade **inicio, char *nomeUniversidade, int matricula)
{
    Universidade *uni_atual = *inicio;

    while (uni_atual != NULL && strcmp(uni_atual->nome, nomeUniversidade) != 0)
    {
        uni_atual = uni_atual->prox;
    }

    if (uni_atual == NULL)
    {
        printf("Universidade %s não encontrada na lista.\n", nomeUniversidade);
        return;
    }

    Aluno *aluno_atual = uni_atual->inicioAluno;
    Aluno *aluno_anterior = NULL;

    while (aluno_atual != NULL && aluno_atual->matricula != matricula)
    {
        aluno_anterior = aluno_atual;
        aluno_atual = aluno_atual->prox;
    }

    if (aluno_atual == NULL)
    {
        printf("Aluno com matrícula %d nao encontrado na universidade %s.\n", matricula, nomeUniversidade);
        return;
    }

    if (aluno_anterior == NULL)
        uni_atual->inicioAluno = aluno_atual->prox;

    else
        aluno_anterior->prox = aluno_atual->prox;

    printf("Aluno %s ja não consta mais no sistema",aluno_atual->nome);
    free(aluno_atual);
}


Universidade *recuperaDados(Universidade **inicio)
{
    FILE *file = fopen("lista_uni.txt", "r");
    if (file == NULL)
    {
        printf("Arquivo inexistente, sera criado.\n");
        return NULL;
    }

    Universidade *auxUniv = NULL;
    Aluno *auxAluno = NULL;
    char line[30];

    while (fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';

        if (strlen(line) == 0)
        {
            auxUniv->prox = NULL;
            auxUniv = NULL;
            auxAluno = NULL;
        }
        else if (auxUniv == NULL)
        {
            // Create a new university entry
            Universidade *nova_uni = malloc(sizeof(Universidade));
            strcpy(nova_uni->nome, line);

            fgets(line, sizeof(line), file);
            nova_uni->qtdAlunos = atoi(line);

            nova_uni->prox = NULL;
            nova_uni->inicioAluno = NULL;

            if (*inicio == NULL)
            {
                *inicio = nova_uni;
            }
            else
            {
                auxUniv = *inicio;
                while (auxUniv->prox != NULL)
                {
                    auxUniv = auxUniv->prox;
                }
                auxUniv->prox = nova_uni;
            }
            auxUniv = nova_uni;
        }
        else
        {
            // Create a new student entry
            Aluno *novo_aluno = malloc(sizeof(Aluno));
            strcpy(novo_aluno->nome, line);

            fgets(line, sizeof(line), file);
            novo_aluno->matricula = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->idade = atoi(line);

            fgets(line, sizeof(line), file);
            novo_aluno->nroDisciplinas = atoi(line);

            novo_aluno->prox = NULL;

            if (auxAluno == NULL)
            {
                auxUniv->inicioAluno = novo_aluno;
            }
            else
            {
                auxAluno->prox = novo_aluno;
            }
            auxAluno = novo_aluno;
        }
    }

    fclose(file);
    return *inicio;
}

void salvaDados(Universidade *inicio)
{
    FILE *file = fopen("lista_uni.txt", "w");
    if (file == NULL)
    {
        printf("Criando arquivo.\n");
        return;
    }

    Universidade *auxUniv = inicio;
    while (auxUniv != NULL)
    {
        fprintf(file, "%s\n", auxUniv->nome);
        fprintf(file, "%d\n", auxUniv->qtdAlunos);

        Aluno *auxAluno = auxUniv->inicioAluno;
        while (auxAluno != NULL)
        {
            fprintf(file, "%s\n", auxAluno->nome);
            fprintf(file, "%d\n", auxAluno->matricula);
            fprintf(file, "%d\n", auxAluno->idade);
            fprintf(file, "%d\n", auxAluno->nroDisciplinas);
            auxAluno = auxAluno->prox;
        }

        fprintf(file, "\n");
        auxUniv = auxUniv->prox;
    }

    fclose(file);
}
