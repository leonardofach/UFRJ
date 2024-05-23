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
 * Arquivo: acao.cpp
 * Descrição: Implementação dos métodos classe Acao.
 *********************************************************/

#include <iomanip>
#include "acao.h"

Acao::Acao (string descricao, double open, double atual, int qtd, double compra, float var)
{
    setTicker (descricao);
    setValorAbertura (open);
    setValorAtual (atual);
    setQuantidade (qtd);
    setValorCompra (compra);
    setVariacao (var);
}

ostream &operator<< (ostream &output, vector<Acao> &acoes)
{
    string divisor (ESPACAMENTO, '-');

    output << "TOTAL AÇÕES: - " << acoes.size () << " ações" << endl;
    output << divisor << endl;
    output << " ID" << setw(9);
    output << "ACAO" << setw(13); 
    output << "QTD" << setw(25);
    output << "COTAÇÃO (R$)" << setw(19);
    output << "TOTAL (R$)" << setw(20) << endl;;   
    output << divisor << endl;

    for (size_t i=0; i < acoes.size(); i++)
    {
        // Formatando a impressão
        if (i <= 9)
            output << "[0" << i << "]" << setw (10);
        else
            output << "[" << i << "]" << setw (10);
        
        output << acoes[i].getTicker() << setw(10);
        output << acoes[i].getQuantidade() << setw(20);
        output << setprecision(2) << fixed << acoes[i].getValorAtual() << setw(20);
        output << setprecision(2) << fixed << acoes[i].getQuantidade() * acoes[i].getValorAtual() << endl;
    }
    output << divisor << endl;

    return output;
}

void Acao::setTicker (string acao)
{
    ticker = acao;
}

void Acao::setValorAbertura (double abertura)
{
    valorAbertura = abertura;
}

void Acao::setValorAtual (double atual)
{
    valorAtual = atual;
}

void Acao::setQuantidade (int qtd)
{   
    quantidade = qtd;
}

void Acao::setValorCompra (double compra)
{
    valorCompra = compra;
}

void Acao::setVariacao (float var)
{
    variacao = var;
}

string Acao::getTicker (void)
{
    return ticker;
}

double Acao::getValorAbertura (void)
{
    return valorAbertura;
}

double Acao::getValorCompra (void)
{
    return valorCompra;
}

double Acao::getValorAtual (void)
{
    return valorAtual;
}

int Acao::getQuantidade (void)
{
    return quantidade;
}

float Acao::getVariacao (void)
{
    return variacao;
}