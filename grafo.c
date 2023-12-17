#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_TAM 10000
#include "grafo.h"

struct grafo{
    int cidades;  /*armazena a quantidade de cidades*/
    int **matriz; /*armazena distancia entre as cidades, 0 caminho nulo, indice é  o numero da cidade*/
};

struct caminho{
    int *menorCa;
    int custo;
};

struct item{
    int cidAt; //cidade atual
    int distAt; //distância da cidade atual analisada
};

struct cel {
    Item item ;
    struct cel * pProx ;
};

struct lista {
    Celula* pPrimeiro;
    Celula* pUltimo;
};


/* Aloca solução*/
Caminho* alocarSolucao(){
    return malloc(sizeof(Caminho));
}

void preencheSolucao(Caminho* soluc, int n) {
    soluc->custo = MAX_TAM;
    soluc->menorCa = alocaVetor(n);
    soluc->menorCa[0] = 0;
}

void preencheSolucaoAux(Caminho* soluc, int n) {
    preencheSolucao(soluc, n);
    soluc->custo = 0;
}

void preencheGrafo(Grafo* grafo, int n) {
    grafo->matriz = alocaMatriz(n);
    grafo->cidades = n;
}

int** alocaMatriz(int n) {
    int** mat = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
       mat[i] = malloc(n * sizeof(int));
    }
    return mat;
}

int* alocaVetor (int n) {
    int* vet = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        vet[i] = -1;
    }
    return vet;
}

/* Aloca a struct */ 
Grafo* alocarGrafo(){ 
    return malloc(sizeof(Grafo));; /*retorna a estrutura alocada*/
}

/* Desaloca a struct */
void desalocarGrafo(Grafo *grafo){
    desalocaMatriz(grafo->matriz, grafo->cidades);
    free(grafo);
}


void desalocaSolucao(Caminho *soluc){
    desalocaVetor(soluc->menorCa);
    free(soluc);
}

void desalocaMatriz(int** mat, int n) {
    for (int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}


void desalocaVetor(int *vet){
    free(vet);
}

/* Le os dados */
void leGrafo(Grafo *grafo){
    int origem, destino, distancia, med;
    med = grafo->cidades * grafo->cidades;
    for (int i = 0; i < med; i++){ /*percorre as cidade de origem*/
        scanf("%d %d %d", &origem, &destino, &distancia);
        grafo->matriz[origem][destino] = distancia;
    }
}

    /* Percorre as cidades */
    void encontraCaminho(Grafo *grafo, Caminho *result, Caminho *aux, int x)
{
    if (x == grafo->cidades && grafo->matriz[aux->menorCa[x - 1]][0] != 0){
        aux->custo += grafo->matriz[aux->menorCa[x - 1]][0];
        trocaResultado(aux, result, grafo->cidades);
        aux->custo -= grafo->matriz[aux->menorCa[x - 1]][0];
        return;
    }
    for (int i = 0; i < grafo->cidades; i++) {
        if (caminhoValido(grafo, aux, x, aux->menorCa[x - 1], i)) {
            aux->menorCa[x] = i;
            aux->custo += grafo->matriz[aux->menorCa[x - 1]][i];
            encontraCaminho(grafo, result, aux, x + 1);
            aux->custo -= grafo->matriz[aux->menorCa[x - 1]][i];
        }
    }
}

bool caminhoValido(Grafo* grafo, Caminho *soluc, int x, int orig, int dest) {
    for (int i = 0; i < x; i++)
        if ((soluc->menorCa[i] == dest) || (grafo->matriz[orig][dest] == 0))
            return false;    
    return true;
}


void trocaResultado(Caminho *aux, Caminho *result, int x){
    if (aux->custo < result->custo) {
        for (int i = 0; i < x; i++)
            result->menorCa[i] = aux->menorCa[i];
        result->custo = aux->custo;
    }
}


/* Imprime o caminho */
void imprimeCaminho(Caminho* soluc, int n){
    printf("Melhor caminho: ");
    for (int i = 0; i < n ; i++) {
        printf("%d ", soluc->menorCa[i]);
    }
    printf("0\n");
    printf("Melhor distancia: %d\n", soluc->custo);
}


void imprimeGrafo(Grafo* grafo, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

/* Funções da Lista */

Lista* alocaLista() {
    Lista* lista = malloc(sizeof(Lista));
    lista->pPrimeiro = malloc(sizeof(Celula)); // Célula cabeça
    lista->pUltimo = lista->pPrimeiro;
    lista->pPrimeiro->pProx = NULL;
    return lista;
}

int ListaEhVazia(Lista* pLista) {
    return (pLista->pPrimeiro == pLista->pUltimo);
}

void ListaLibera(Celula* celula) {
    while (celula != NULL) {
        Celula* prox = celula->pProx;
        free(celula);
        celula = prox;
    }
}

void desalocaLista(Lista* lista) {
    ListaLibera(lista->pPrimeiro);
    free(lista);
}

int ListaInsereFinal(Lista* lista, Grafo* grafo, int cAtu, int CProx) {
    if (lista == NULL) {
        printf("Lista não inicializada.\n");
        return 0;
    }

    Celula* novaCelula = malloc(sizeof(Celula));
    if (novaCelula == NULL) {
        printf("Erro ao alocar memória.\n");
        return 0;
    }

    novaCelula->item.cidAt = CProx;
    novaCelula->item.distAt = grafo->matriz[CProx][cAtu];
    novaCelula->pProx = NULL;

    if (ListaEhVazia(lista)) {
        lista->pPrimeiro->pProx = novaCelula;
        lista->pUltimo = novaCelula;
    } else {
        lista->pUltimo->pProx = novaCelula;
        lista->pUltimo = novaCelula;
    }
    return 1;
}

void preencheLista(Lista* lista, Grafo* grafo, int cidAt) {
    for (int i = 0; i < grafo->cidades; i++) {
        ListaInsereFinal(lista, grafo, cidAt, i);
    }
}

void ordenaLista(Lista* lista) {
    Celula* atual = lista->pPrimeiro->pProx;
    Celula* anterior = lista->pPrimeiro;
    
    while (atual != NULL) {
        Celula* atualOrdenada = lista->pPrimeiro->pProx;
        Celula* anteriorOrdenada = lista->pPrimeiro;
        
        while (atualOrdenada != atual && atual->item.distAt >= atualOrdenada->item.distAt) {
            anteriorOrdenada = atualOrdenada;
            atualOrdenada = atualOrdenada->pProx;
        }
        
        if (atualOrdenada != atual) {
            anterior->pProx = atual->pProx;
            anteriorOrdenada->pProx = atual;
            atual->pProx = atualOrdenada;
            atual = anterior->pProx;
        } else {
            anterior = atual;
            atual = atual->pProx;
        }
    }
}

void imprimeOrdenado(Lista* lista, int n) {
    Celula* atual = lista->pPrimeiro->pProx;
    printf("Adjacencias do vertice %d: ", n);
    while (atual != NULL) {
        printf("(%d, %d) -> ", atual->item.cidAt, atual->item.distAt);
        atual = atual->pProx;
    }
    printf("NULL\n");
}
