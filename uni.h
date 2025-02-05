#ifndef UNI_H
#define UNI_H

typedef struct Aluno
{
        char nome[30];
    int matricula;
    int idade;
    int nroDisciplinas;
    struct Aluno *prox;
} Aluno;

typedef struct Universidade
{
    char nome[30];
    int qtdAlunos;
    struct Universidade *prox;
    struct Aluno *inicioAluno;
} Universidade;

void insereUniversidade(Universidade **inicio, char *nomeUni);
void insereAluno(Universidade **inicio, char *nomeUni, char *nomeAluno, int matricula, int idade, int nroDisciplinas);
void buscaUniversidade(Universidade **inicio, char *nome);
void buscaAluno(Universidade **inicio, int matricula);
void imprimeUni(Universidade **inicio);
void removeUniversidade(Universidade **inicio, char *nomeUniversidade);
void removeAluno(Universidade **inicio, char *nomeUniversidade, int matricula);
Universidade *recuperaDados(Universidade **inicio);
void salvaDados(Universidade *inicio);


#endif