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
 * Arquivo: disciplina.cpp
 * Descrição: Arquivo contendo a implementação dos métodos da classe Disciplina.
 * *********************************************************************************
 */

#include <iostream>
#include "disciplina.h"

Disciplina::Disciplina(string nomeDisciplina, int idDisciplina, vector<Aluno> &listaAlunos) // construtor
{
    setNome(nomeDisciplina);
    setId(idDisciplina);
    matricularAlunos(listaAlunos);
}

void Disciplina::setNome(string nomeDisciplina)
{
    nome = nomeDisciplina;
}

void Disciplina::setId (int idDisciplina)
{
    id = idDisciplina;
}

void Disciplina::matricularAlunos(vector<Aluno> &listaAlunos)
{
    alunosMatriculados = listaAlunos;
}

string Disciplina::getNome(void)
{
    return nome;
}

void Disciplina::getAluno(vector<Aluno> &listaAlunos)
{
    listaAlunos = alunosMatriculados;
}

void Disciplina::getMedia(vector<float> &mediaFinal)
{
    calcularMedia(mediaFinal);
}

void Disciplina::getMediaMovel(vector<float> &mediaMovel)
{
    calcularMediaMovel(mediaMovel);
}

void Disciplina::calcularMedia(vector<float> &mediaFinal)
{
    float somaNotas;

    for (int periodo=0; periodo < NUM_PERIODOS; periodo++)
    {
        somaNotas = 0;
        for (int aluno=0; aluno < NUM_ALUNOS; aluno++)
        {
            vector<vector<float>> notasAluno;
            alunosMatriculados[aluno].getNotas (notasAluno);
            somaNotas+= notasAluno[periodo][id];
        }
        mediaFinal.push_back (somaNotas/NUM_ALUNOS);
    }
}

void Disciplina::calcularMediaMovel(vector<float> &mediaMovel)
{
    float somaNotas;
    vector<float> mediasFinais;

    getMedia(mediasFinais);

    somaNotas = 0; 
    for (int periodo=0; periodo < NUM_PERIODOS; periodo++)
    {
        // Caso em que não há dados históricos suficiente
        if (periodo < N_MEDIA_MOVEL - 1)
            mediaMovel.push_back (-1);

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

            for (int i=periodo - 2; i <= periodo; i++)
                somaNotas+=mediasFinais[i];

            mediaMovel.push_back(somaNotas/N_MEDIA_MOVEL);
            somaNotas = 0;
        }
    }    
}