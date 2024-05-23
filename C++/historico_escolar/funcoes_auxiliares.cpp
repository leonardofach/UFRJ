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
 * Arquivo: funcoes_auxiliares.cpp
 * Descrição: Implementação das funções auxiliares.
 *********************************************************/

#include <iostream>
#include "funcoes_auxiliares.h"


int StringToInt (string input) 
{
    // Converte uma string para um inteiro -> a função retorna -1 se a conversão não for bem sucedida

    int num;

    for (char caractere : input)
        if (caractere < '0' || caractere > '9') // a string informada possui um caractere inválido
            return -1;
    try
    {
        num = stoi (input);
        return num;
    }
    catch (...)
    {
        return -1;
    }
}

double StringToDouble (string input) 
{
    // Converte uma string para um inteiro -> a função retorna -1 se a conversão não for bem sucedida

    int count = 0;
    double num;

    for (char caractere : input)
    {
        if (caractere < '0' || caractere > '9') // a string informada possui um caractere inválido
        {
            if (caractere == '.' && count == 0)   // o ponto é permitido apenas uma vez
            {
                count++;   // apenas um ponto é permitido
                continue;
            }
            else
                return -1;
        }
    }   
    try
    {
        num = stod (input);
        return num;
    }
    catch (...)
    {
        return -1;
    }
}