/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 03/10/2023
 * Arquivo: funcoes_auxiliares.h
 * Descrição: Implementação dos protótipos das funções auxiliares.
 *********************************************************/

#ifndef FUNCOES_AUXILIARES_H
#define FUNCOES_AUXILIARES_H

#include <string>

using namespace std;

int StringToInt (string input);
/* Converte uma string para um inteiro positivo.
* A função retorna -1 se a conversão não for bem sucedida */

double StringToDouble (string input);
/* Converte uma string para um double positivo.
* A função retorna -1 se a conversão não for bem sucedida */

#endif