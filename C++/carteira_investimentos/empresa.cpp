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
 * Arquivo: empresa.cpp
 * Descrição: Implementação dos métodos da classe Empresa.
 *********************************************************/

#include "empresa.h"

Empresa::Empresa (dadosEmpresa &dbEmpresa)
{
    dados = dbEmpresa;
}

void Empresa::getDados (dadosEmpresa &dbEmpresa)
{
    dbEmpresa = dados;
}