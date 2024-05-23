/***********************************************************************************
 * UNIVERSIDADE FEDERAL O RIO DE JANEIRO
 *
 * Aluno: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônica e de computação
 *
 * Disciplina: Linguagens de programação - 23/2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 13/09/2023
 * Arquivo: aluno.h
 * Descrição: Arquivo de cabeçalho contendo o protótipo da classe Aluno.
 * *********************************************************************************
 */

#ifndef ALUNO_H
#define ALUNO_H

#include <string>
#include <vector>

#define N_MEDIA_MOVEL 3

using namespace std;

class Aluno
{
    public:
        /* Construtor da classe. */
        Aluno(string nomeAluno, vector<vector<float>> &notasAluno); 

        /* Salva o nome do aluno. */
        void setNome(string nomeAluno);

        /* Salva as notas do aluno em todas as disciplinas cursadas
        ao longo dos períodos. */
        void setNotas(vector<vector<float>> &notasAluno);

        /* Retorna o nome do aluno. */
        string getNome(void);

        /* Retorna as notas do aluno em todas as disciplinas cursadas
        ao longo dos períodos. */
        void getNotas(vector<vector<float>> &notasAluno);

        /* Imprimi na tela todas as informações salvas a respeito do aluno. */
        void printDados(void);

        /* Retorna (por referência) a media final do aluno em todas as
        disciplinas cursadas no período, isto é, para cada período cursado, é
        computada a média do aluno considerando todas as disciplinas que ele
        cursou no período. */
        void getMedia(vector<float> &mediaFinal);

        /* Retorna (por referência) a media móvel final do aluno em todas as
        disciplinas cursadas ao longo dos períodos considerando um espaço de
        medias definida na macro N_MEDIA_MOVEL médias. */
        void getMediaMovel(vector<float> &mediaFinal);

    private:
        string nome; // nome do aluno
        vector<vector<float>> notas; // notas do aluno

        /* Realiza o cálculo da média do aluno para cada período considerando
        todas as disciplinas cursadas no período. */
        void calcularMedia(vector<float> &mediaFinal);

        /* Realiza o cálculo da média móvel do aluno ao longo dos períodos considerando
        um espaço de médias definido na macro N_MEDIA_MOVEL. */
        void calcularMediaMovel(vector<float> &mediaFinal);
        
        /* Estrutura do vector notas:

            notas = [[disciplina1, disciplina2, ... , disciplinaN],   período 1
                     [disciplina1, disciplina2, ... , disciplinaN],   período 2
                                    ...                                  ...
                     [disciplina1, disciplina2, ... , disciplinaN]]   período N
        */
};

#endif