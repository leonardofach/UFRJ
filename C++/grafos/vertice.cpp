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
 * Arquivo: vertice.cpp
 * Descrição: Arquivo contendo a implementação dos métodos da classe Vertice.
 ******************************************************************************/

#include "vertice.h"

Vertice::Vertice(string nomeVertice)
{
    setNome(nomeVertice);
}

void Vertice::setNome(string nomeVertice)
{
    nome = nomeVertice;
}

string Vertice::getNome(void)
{
    return nome;
}