/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 02/11/2023
 * Arquivo: disciplina.cpp
 * Descrição: Implementação das funções da struct Disciplina.
 *********************************************************/

#include "disciplina.h"

ostream &operator<< (ostream &output, const Disciplina &infoDisciplina)
{
    // Permite realizarmos cout << struct da struct Disciplina

    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << "PERÍODO" << "      " << "NOTA" << "     " << "CRÉDITOS" << "     " << "DISCIPLINA" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    output << infoDisciplina.periodo << setw (10) 
           << infoDisciplina.notaFinal << setw(10)
           << infoDisciplina.creditos << "         " 
           << infoDisciplina.nome << endl;

    cout << "-----------------------------------------------------------------------------" << endl << endl;     

    return output;
}

istream &operator>> (istream &input, Disciplina &novaDisciplina)
{
    // Permite realizarmos cin >> struct Disciplina

    cout << "Pressione a tecla ENTER para iniciar! ";
    input.ignore ();

    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << "Nome da disciplina: ";
    getline (input, novaDisciplina.nome);

    cout << "Créditos: ";
    input >> novaDisciplina.creditos;

    cout << "Período (ex: 2023.1): ";
    input >> novaDisciplina.periodo;

    cout << "Nota final: ";
    input >> novaDisciplina.notaFinal;
    cout << "-----------------------------------------------------------------------------" << endl;

    return input;
}

void limparDisciplina (Disciplina &disciplina)
{
    // Limpa os dados da struct Disciplina

    disciplina.creditos = 0;
    disciplina.nome = "Padrão";
    disciplina.notaFinal = 0;
    disciplina.periodo = "Padrão";
}