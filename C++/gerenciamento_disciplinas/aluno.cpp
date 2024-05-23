/***********************************************************************************
 * UNIVERSIDADE FEDERAL O RIO DE JANEIRO
 *
 * Aluno: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônica e de computação
 *
 * Disciplina: Linguagens de programação - 23/2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 13/09/2023
 * Arquivo: aluno.cpp
 * Descrição: Arquivo contendo a implementação dos métodos da classe Aluno.
 * *********************************************************************************
 */

#include <iostream>
#include <iomanip>
#include "aluno.h"

using namespace std;

Aluno::Aluno(string nomeAluno, vector<vector<float>> &notasAluno) // construtor
{
    setNome(nomeAluno);
    setNotas(notasAluno);
}

void Aluno::setNome(string nomeAluno)
{
    nome = nomeAluno;
}

void Aluno::setNotas(vector<vector<float>> &notasAluno)
{
    notas = notasAluno;
}

string Aluno::getNome(void)
{
    return nome;
}

void Aluno::getNotas(vector<vector<float>> &notasAluno)
{
    notasAluno = notas;
}

void Aluno::getMedia(vector<float> &mediaFinal)
{
    calcularMedia(mediaFinal);
}

void Aluno::getMediaMovel(vector<float> &mediaFinal)
{
    calcularMediaMovel(mediaFinal);
}

void Aluno::printDados(void)
{
    cout << "Aluno: " << nome << endl;

    for (size_t periodo=0; periodo < notas.size(); periodo++)
    {
        cout << setw(5);
        for (size_t disciplina=0; disciplina < notas[periodo].size(); disciplina++)
        {
            cout << notas[periodo][disciplina] << setw(5);
        }
        cout << endl;
    }
    cout << endl;
}

void Aluno::calcularMedia(vector<float> &mediaFinal)
{
    for (size_t periodo=0; periodo < notas.size(); periodo++)
    {
        float soma = 0;

        for (size_t disciplina=0; disciplina < notas[periodo].size(); disciplina++)
            soma += notas[periodo][disciplina];
    
        mediaFinal.push_back(soma / notas[periodo].size());
    }
}

void Aluno::calcularMediaMovel(vector<float> &mediaFinal)
{
    float somaNotas;
    vector<float> mediaAritmetica;
    
    getMedia(mediaAritmetica);

    somaNotas = 0; 
    for (size_t periodo=0; periodo < notas.size(); periodo++)
    {
        // Caso em que não há dados históricos suficiente
        if (periodo < N_MEDIA_MOVEL - 1)
            mediaFinal.push_back (-1);

        else
        {
            /* Período   Intervalo
             *  atual      soma
             *   0           -
             *   1           -
             *   2         0 1 2
             *   3         1 2 3
             *   4         2 3 4
             *   5         3 4 5
             *   6         4 5 6
             *   7         5 6 7 */

            for (size_t i=periodo - 2; i <= periodo; i++)
                somaNotas+=mediaAritmetica[i];

            mediaFinal.push_back(somaNotas/N_MEDIA_MOVEL);
            somaNotas = 0;
        }
    } 
}