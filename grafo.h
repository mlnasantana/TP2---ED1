#include <stdbool.h>
#ifndef GRAFO_H
#define GRAFO_H


/* Struct */
typedef struct grafo Grafo;

typedef struct caminho Caminho;

typedef struct item Item;

typedef struct cel Celula;

typedef struct lista Lista;



/* Aloca a struct */
Grafo* alocarGrafo();
Caminho* alocarSolucao();
int* alocaVetor(int n);
int** alocaMatriz(int n);

void preencheSolucao(Caminho*, int);
void preencheSolucaoAux(Caminho*, int);
void preencheGrafo(Grafo*, int);

/* Desaloca a struct */
void desalocarGrafo(Grafo* grafo);
void desalocaMatriz(int** mat, int n);
void desalocaSolucao(Caminho* soluc);
void desalocaVetor(int* vet);

/* Le os dados */
void leGrafo(Grafo* grafo);

/* Percorre as cidades */
void encontraCaminho(Grafo *grafo, Caminho *result, Caminho *aux, int x);
void trocaResultado(Caminho* dest, Caminho* source, int x);
bool caminhoValido(Grafo* grafo, Caminho *soluc, int x, int orig, int dest);

/* Imprime o caminho */
void imprimeCaminho(Caminho* soluc, int n);
void imprimeGrafo(Grafo* grafo, int n);

/* Funções da lista */
Lista* alocaLista(); //lista inicia
int ListaEhVazia (Lista*);
void desalocaLista(Lista*);
void ListaLibera(Celula*);
int ListaInsereFinal(Lista*, Grafo*, int, int);
void preencheLista(Lista*, Grafo*, int);
void ordenaLista (Lista*);
void imprimeOrdenado (Lista*, int);

#endif