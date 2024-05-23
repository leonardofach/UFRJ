/****************************************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 12/10/2023
 * Arquivo: aresta.cpp
 * Descrição: Arquivo contendo a implementação dos métodos da classe Aresta.
 *******************************************************************************/

#include "aresta.h"

Aresta::Aresta(Vertice verticeOrigem, Vertice verticeDestino, float pesoAresta) // construtor
{
    setOrigem(verticeOrigem);
    setDestino(verticeDestino);
    setPeso(pesoAresta);
}

void Aresta::setOrigem(Vertice verticeOrigem)
{
    origem = verticeOrigem;
}

void Aresta::setDestino(Vertice verticeDestino)
{
    destino = verticeDestino;
}

void Aresta::setPeso(float pesoAresta)
{
    peso = pesoAresta;
}

Vertice Aresta::getOrigem(void)
{
    return origem;
}

Vertice Aresta::getDestino(void)
{
    return destino;
}

float Aresta::getPeso(void)
{
    return peso;
}