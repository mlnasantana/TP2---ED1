#include <stdio.h>
#include "grafo.h"

int main () {
    int n, x = 1;
    scanf("%d", &n);
    Caminho* resultado = alocarSolucao();
    Caminho* aux = alocarSolucao();
    Grafo* grafo = alocarGrafo();
    
    preencheSolucao(resultado, n);
    preencheSolucaoAux(aux, n);
    preencheGrafo(grafo, n);
    leGrafo(grafo);

    encontraCaminho(grafo, resultado, aux, x);

    for (int i = 0; i < n; i++) {
        Lista* lista = alocaLista();
        preencheLista(lista, grafo, i);
        ordenaLista(lista);
        imprimeOrdenado(lista, i);
        desalocaLista(lista);
    }

    imprimeCaminho(resultado, n);

    desalocarGrafo(grafo);
    desalocaSolucao(resultado);
    desalocaSolucao(aux);
    

    return 0;
}