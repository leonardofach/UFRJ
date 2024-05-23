/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 27/10/2023
 * Arquivo: historio.h
 * Descrição: Implementação da classe Histórico.
 *********************************************************/

#ifndef HISTORICO_H
#define HISTORICO

#include <vector>
#include <fstream>
#include "disciplina.h"


class Historico
{
    friend ostream &operator<< (ostream &output, const Historico &infoHistorico); 
    /* Permite realizarmos cout << objeto da classe Historico
     * Imprimi todas as informações do histórico na tela */

    friend short int carregarDados (string fileName, Historico &infoHistorico);
    /* Carrega a base de dados do histórico salva em execuções anteriores do programa*
     * Retorna 0 caso o carregamento seja realizado com sucesso ou-1 caso contrário */

    friend short int gravarDados (string fileName, const Historico &infoHistorico);
    /* Grava todas as alterações realizadas no histórico na sua base de dados
     * Retorna 0 caso a gravação seja realizada com sucesso ou-1 caso contrário */

    public:
        Disciplina getDisciplina (short int idDisciplina);
        /* Retorna uma disciplina do histórico na posição idDisciplina do vector de disciplinas*/  

        short int getNumeroDisciplinas (void);  
        /* Retorna o número de disciplinas cadastradas no histórico*/

        short int getMaximoDisciplinas (void); 
        /* Retorna o número máximo de discplinas permitidas a serem cadastradas no histórico*/

        short int operator+= (Disciplina &novaDisciplina);
        /* Permite realizarmos historico += disciplina
         * Adiciona UMA nova disciplina no histórico de forma ordenada e retorna a posição em que
           foi adicionada no vector de disciplinas. Caso a disciplina informada já esteja cadastrada,
           será retornado -1.*/

        vector<short int> operator+= (vector<Disciplina> &novasDisciplinas);
        /* Permite realizarmos historico += disciplina
         * Adiciona VÁRIAS novas disciplinas no histórico de forma ordenada e retorna a posição em que
           foi adicionada no vector de disciplinas. Caso a disciplina informada já esteja cadastrada,
           será retornado -1.*/

        short int operator-= (Disciplina &disciplina);
        /* Permite realizarmos historico -= disciplina
         * Remove uma disciplina do histórico e retorna a posição em que a disciplina removida estava
           armazenada no vector de disciplinas. Caso a disciplina informada não esteja cadastrada, será
           retornado o valor -1.*/

        short int operator() (string nomeDisciplina);   
        /* Permite realizarmos histórico (nomeDisciplina)
         * Retorna a posição em que a disciplina informada está cadastrada no histórico. Caso a
           disciplina informada não esteja cadastrada, será retornado o valor -1.*/

        short int operator() (string nomeDisciplina, double novaNota);
        /* Permite realizarmos historico (nomeDisciplina, novaNota)
         * Edita a nota da disciplina informada e retorna a posição em que a disciplina editada
           está armazenada no vector disciplinas. Caso a disciplina informada não esteja cadastrada, será
           retornado o valor -1.*/

        double calcularCRA (void);
        /* Calcula o valor do CRA com base nas disciplinas cadastradas no histórico.*/

    private:
        vector<Disciplina> disciplinas;
        const short int maximoDisciplinas = 50;

        friend bool operator== (const Disciplina &disciplina1, const Disciplina &disciplina2);
        /* Permite realizarmos disciplina1 == disciplina2
         * Compara os nomes das disciplinas*/

        friend bool operator< (const Disciplina &disciplina1, const Disciplina &disciplina2);
        /* Permite realizarmos disciplina1 < disciplina2
         * Compara seus períodos */
};

#endif