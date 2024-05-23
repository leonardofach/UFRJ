/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 06/12/2023
 * Arquivo: empresa.h
 * Descrição: Implementação da classe Empresa.
 *********************************************************/

#ifndef EMPRESA_H
#define EMPRESA_H

#include <string>

using namespace std;

// Struct para armazenar os dados de uma empresa
struct Empresa
{
    double margemLucro;
    double margemOperacional;
    double margemEBITDA;
    double margemBruta;
    double crescimentoReceita;
    double retornoSobreAtivos;
    double receitaPorAcao;
};

#endif