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
 * Arquivo: funcoes_auxiliares.cpp
 * Descrição: Implementação de funções auxiliares para o 
 * programa principal definido no arquivo main.cpp.
 *********************************************************/

#include "funcoes_aux.h"

int StringToInt (string num)
{
    int n;

    // Verificando se a string informada possui caractere inválido
    for (char caractere : num)
    {
        if (caractere < '0' || caractere > '9')
            return -1;
    }

    try
    {
        n = stoi (num);
        return n;
    }

    catch (...)
    {
        return -1;
    }
}

double StringToDouble (string num)
{
    double n;
    int count = 0;

    // Verificando se a string informada possui caractere inválido
    for (char caractere : num)
    {
        if (caractere < '0' || caractere > '9')
        {
            // o ponto é permitido apenas uma vez (float / double)
            if (caractere == '.' && count == 0)
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
        n = stod (num);
        return n;
    }

    catch (...)
    {
        return -1;
    }
}