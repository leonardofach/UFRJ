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
 * Arquivo: acao.h
 * Descrição: Implementação da classe Acao.
 *********************************************************/

#ifndef ACAO_H
#define ACAO_H

#include <string>
#include <vector>

#define ESPACAMENTO     70

using namespace std;

class Acao
{
    friend ostream &operator<< (ostream &output, vector<Acao> &acoes);

    public:
        Acao (string descricao = "default", 
              double open = 0,
              double atual = 0, 
              int qtd = 0, 
              double compra = 0, 
              float var = 0);

        void setTicker (string acao);
        void setValorAbertura (double abertura);
        void setValorAtual (double atual);
        void setQuantidade (int qtd);
        void setValorCompra (double compra);
        void setVariacao (float var);
        string getTicker (void);
        double getValorAbertura (void);
        double getValorCompra (void);
        double getValorAtual (void);
        int getQuantidade (void);
        float getVariacao (void);

    private:
        string ticker;
        double valorAbertura;
        double valorAtual;
        int quantidade;
        double valorCompra;
        float variacao;
};

#endif
