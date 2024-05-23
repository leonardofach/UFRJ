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
 * Arquivo: carteira.h
 * Descrição: Implementação da classe Carteira.
 *********************************************************/

#ifndef CARTEIRA_H
#define CARTEIRA_H

#include "acao.h"
#include "empresa.h"
#include <unistd.h>
#define Define_CurrentDir getcwd

#define DADOS_USUARIO   "dados_usuario.txt" // informa o arquivo txt onde os dados do usuario estão salvos
#define DADOS_ACOES     "tickers.txt" // informa o arquivo txt com a lista de ações a serem disponibilizadas pelo sistema


enum ERROR
{
    SUCESSO,                            // 0
    ERRO_CARREGAR_LISTA_ACOES,          // 1
    ERRO_ATUALIZAR_COTACOES,            // 2
    ERRO_CARREGAR_DADOS_USUARIO,        // 3
    ERRO_COTACAO_IPCA,                  // 4
    ERRO_COTACAO_DOLAR,                 // 5
    ERRO_DADOS_EMPRESA                  // 6
};

class Carteira
{
    /* Sobrecarga do operador << para exibir as informações da carteira
    do usuario como saldo, valor investido, rentabilidade, dentre outros */
    friend ostream &operator<< (ostream &output, Carteira &minhaCarteira);

    friend ostream &operator<< (ostream &output, Carteira &minhaCarteira);

    public:
        /* Construtor da classe Carteira */
        Carteira (string nomeUsuario="defaut", float saldoInicial=0);

        /* Carrega dos dados do usuário salvos na execução anterior do sistema e
        a lista de ações a serem disponibilizadas pelo sistema definos nos arquivos de
        texto DADOS_USUARIO e DADOS_ACOES, respectivamente. O método 
        retorna o inteiro 0 caso o carregamento dos dados sejam realizados
        com sucesso ou -1 caso contrário. */
        int iniciarSistema (vector<string> &listaAcoes, vector<Acao> &dadosAcoes);

        /* Atualiza as cotações das ações disponibilizadas no sistema para seus
        valores mais atuais. O argumento listaAcoes informa a lista de ações
        disponibilizadas pelo sistema e suas informações serão salvas no
        argumento dadosAcoes passado por referência. O argumento modo informa se
        a atualização está sendo realizada pela primeira vez durante a excução do
        sistema ou não */
        int atualizarCotacoes (vector<string> &listaAcoes, vector<Acao> &dadosAcoes, int modo);

        double getSaldo (void);

        Acao getAcao (int idAcao); 

        /* Retorna um número inteiro com o total de ações da carteira */
        int totalAcoesCarteira (void);

        /* Realiza a compra de uma ação informada. O método retorna o inteiro 0 caso a
        compra seja realizada com sucesso, ou -1 caso contrário. */
        int operator+ (Acao &novaAcao);

        /* Realiza a venda da ação informada */
        void operator- (Acao &acao);

        /* Exibi o valor do IPCA atual e no período acumulado do ano vigente */
        void exibirIPCA (int dia, int mes, int ano);

        /* Exibi a cotação atual do dólar e no período acumulado do ano vigente */
        void exibirDolar (void);

        /* Exibi várias métricas importantes da empresa informada */
        int analiseFundamentalista (string empresa);

    private:
        string usuario;                      // nome do usuário
        double saldo;                        // saldo atual da conta
        double investimentos;                // valor atual investido
        float rentabilidade;                //  rentabilidade da carteira
        vector<Acao> acoesUsuario;          //  ações compradas pelo usuário

        /* Carrega os dados do usuário salvos em uma execução anterior do
        sistema. OS dados serão lidos do arquivo txt definido na macro DADOS_USUARIO */
        int CarregarDadosUsuario (vector<string> listaAcoes, vector<Acao> &dadosAcoes);

        /* Carrega a lista de ações a serem disponibilizadas pelo sistema. A lista com as
        ações estão salvas no arquivo txt definido pela macro DADOS_ACOES */
        int CarregarListaAcoes (vector<string> &listaAcoes);

        /* Computa o valor atual investido com base nas cotações atuais e
        atualiza os valores dos parâmetros privados da classe investimentos e rentabilidade. */
        void computarInvestimento ();

        /* Chama a função externa DadosCotacoes escrita na linguagem python passando o parâmetro
        ação e recebe o preço de abertura e a cotação atual da respectiva ação. O método retorna
        o inteiro 0 se o processo for realizado com sucesso ou -1 casao contrário. */
        int dbCotacoes (string acao, double &abertura, double &cotacao);

        /* Recebe o ticker de uma ação na bolsa e retorna diversas informações sobre ela além 
        de várias métricas financeiras a respetio da empresa */
        int dbEmpresa (string empresa, Empresa &dadosEmpresa);

        int dbDolar (double &atual);

        int dbIPCA (float &atual, float &acumulado, int dia, int mes, int ano);
};

#endif