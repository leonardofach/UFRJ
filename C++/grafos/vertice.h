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
 * Arquivo: vertice.h
 * Descrição: Arquivo contendo a definição da classe Vertice.
 *****************************************************************/

#ifndef VERTICE_H
#define VERTICE_H

#include <string>

using namespace std;

class Vertice
{
    public:
        Vertice(string nomeVertice = "default"); // construtor
        void setNome(string nomeVertice);
        string getNome(void);

    private:
        string nome;
};

#endif