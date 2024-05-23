/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 08/12/2023
 * Arquivo: funcoes_aux.h
 * Descrição: Implementação de funções auxiliares para o 
 * programa principal definido no arquivo main.cpp.
 *********************************************************/

#ifndef FUNCOES_AUX_H
#define FUNCOES_AUX_H

#include <string>

using namespace std;

/* Converte uma string para um inteiro positivo.
A função retorna -1 se a conversão não for bem sucedida */
int StringToInt (string num);

/* Converte uma string para um double.
A função retorna -1 se a conversão não for bem sucedida */
double StringToDouble (string num);

#endif