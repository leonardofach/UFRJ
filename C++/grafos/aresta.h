/****************************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 12/10/2023
 * Arquivo: aresta.h
 * Descrição: Arquivo contendo a definição da classe aresta.
 *****************************************************************/

#ifndef ARESTA_H
#define ARESTA_H

#include "vertice.h"

class Aresta
{
    public:
        Aresta(Vertice verticeOrigem, Vertice verticeDestino, float pesoAresta); // construtor

        void setOrigem (Vertice verticeOrigem);
        void setDestino (Vertice verticeDestino);
        void setPeso (float pesoAresta);

        Vertice getOrigem (void);
        Vertice getDestino (void);
        float getPeso (void);

    private:
        Vertice origem, destino;
        float peso;
};

#endif
