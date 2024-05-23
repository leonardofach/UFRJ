/*****************************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 12/10/2023
 * Arquivo: grafo.h
 * Descrição: Arquivo contendo a definição da classe Grafo.
 *****************************************************************/

#ifndef GRAFO_H
#define GRAFO_H

#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <queue>
#include <list>
#include "aresta.h"

using namespace std;

#define NUMERO_MINIMO_ARESTAS 4   // definido no trabalho
#define NUMERO_MAXIMO_ARESTAS 40  // minha escolha de projeto
#define NUMERO_MINIMO_VERTICES 4  // definido no trabalho
#define NUMERO_MAXIMO_VERTICES 20 // minha escolha de projeto
#define MAX_CARACT 30
#define INFINITO 1000000

enum status
{
    SUCESSO,                 // 0
    ERRO_LEITURA_ARQUIVO,    // 1
    ERRO_FORMATACAO_ARQUIVO, // 2
    ERRO_MINIMO_ARESTAS,     // 3
    ERRO_MAXIMO_ARESTAS,     // 4
    ERRO_MINIMO_VERTICES,    // 5
    ERRO_MAXIMO_VERTICES,    // 6
    ERRO_ENTRADA_USUARIO     // 7
};

/* A classe Grafo fornece uma série de funcionalidades a serem utilizadas sobre um GRAFO SIMÉTRICO NÃO-ORIENTADO*/

class Grafo
{
    public:
        void inserirArestas(string file, short int &status);
        /* Recebe um arquivo (file) txt contendo os vértices, arestas e pesos
        * e cria um grafo simétrico não-orientado. O arquivo txt terá o seguinte padrão de formatação:
        *
        *      verticeOrigem verticeDestino peso
        *
        * A separação entre os valores é feita por um ÚNICO caractere de espaço.
        * Exemplo de arquivo txt válido:
        *      A B 2,2
        *      B C 1,0
        *      C D 3,1
        *      A C 1,2
        * 
        * Além disso, o método inserirArestas retorna na variável (passada por referência) status se a construção foi
        * bem realizada com sucesso (retorna SUCESSO=0) ou não. Caso não seja, será retornado um código de erro
        * que pode ser interpretado a partir da variável enum status.
        */

        void imprimirVertices(void);
        // Imprimi na tela todos os vérices do grafo

        int getNumeroVertices(void);
        // Retorna o número de vértices do grafo

        void imprimirEnlaces(void);
        // Imprimir na tela a lista de enlaces existentes no grafo

        void imprimirMatrizAdjacencias(void);
        // Imprimi na tela a matriz de adjacências do grafo

        void menorCaminho(short int origem, short int destino);
        // Imprimi na tela a distância do menor caminho entre o vértice de origem ao de destino

        void densidadeGrafo(void);
        // Imprimi na tela a densidade do grafo

        void maiorCentralidade(void);
        // Imprimi na tela o vértice com a maior centralidade e seu respectivo valor

    private:
        // Atributos privados da classe Grafo
        vector<string> idVertices; // guarda o código de identificação (id) referentes aos vértices
        size_t numeroVertices;     // número de vértices do grafo
        short int numeroArestas;   // número de arestas do grafo
        float *matrizAdjacencia;   // um ponteiro para a matriz de adjacências
        
        // Métodos privados da classe Grafo
        void algoritmoDijkstra(short int verticeOrigem, short int verticeDestino, float *distancia);
        // Realiza o cálculo da distância do menor caminho do grafo entre o verticeOrigem e verticeDestino

        void gravarDados(string fileName, short int &status);
        // grava os dados informados no arquivo txt nas variáveis referêntes ao atributos privados da classe

        void validarDados(string fileName, vector<string> &listaIdVertices, vector<float> &listaPesos,
                        vector<string> &listaEnlacesOrigem, vector<string> &listaEnlacesDestino, short int &status);
        // Realiza a identificacao e validação dos vertices, arestas e pesos do grafo a ser construido.

        void lerArquivo(string fileName, vector<string> &dados, short int &status);
        // Realiza a leitura do arquivo txt file informado e retorna o conteúdo lido para o vetor de string dados
};

#endif