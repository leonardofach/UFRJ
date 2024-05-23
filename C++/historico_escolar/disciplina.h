/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 27/10/2023
 * Arquivo: disciplina.h
 * Descrição: Implementação da struct Disciplina.
 *********************************************************/

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

struct Disciplina
{
    string nome, periodo;
    short int creditos;
    double notaFinal;
};

// Permite realizarmos cout << struct Disciplina
ostream &operator<< (ostream &output, const Disciplina &infoDisciplina); 

// Permite realizarmos cin >> struct Disciplina
istream &operator>> (istream &input, Disciplina &novaDisciplina);    

// Limpa os dados da struct Disciplina
void limparDisciplina (Disciplina &disciplina);

#endif
