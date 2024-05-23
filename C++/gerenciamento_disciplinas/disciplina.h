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
 * Arquivo: disciplina.h
 * Descrição: Arquivo de cabeçalho contendo o protótipo da classe Disciplina.
 * *********************************************************************************
 */

#ifndef DISCIPLINA_H
#define DISCIPLINA_H

#include "aluno.h"

#define NUM_ALUNOS 10
#define NUM_PERIODOS 8
#define NUM_DISCIPLINAS 5
#define N_MEDIA_MOVEL 3

using namespace std;

class Disciplina
{
    public:
        /* Construtor da classe. */
        Disciplina(string nomeDisciplina, int idDisciplina, vector<Aluno> &listaAlunos);

        /* Salva o nome da disciplina. */
        void setNome(string nomeDisciplina);

        /* Salva o id da disciplina. */
        void setId (int idDisciplina);

        /* Matricula os alunos informados no vector listaAlunos na disciplina. */
        void matricularAlunos(vector<Aluno> &listaAlunos);

        /* Retorna o nome da disciplina. */
        string getNome(void);

        /* Retorna um vector com a lista de alunos que estão cursando a disciplina. */
        void getAluno (vector<Aluno> &listaAlunos);

        /* Retorna (por referência) a média final da turma na disciplina em cada período. 
        Cada posição do vector mediaFinal informado como parâmetro conterá a
        média final da turma no respectivo período, ou seja, a posição do vector mediaFinal
        representa o periodo letivo em questão.*/
        void getMedia(vector<float> &mediaFinal);

        /* Retorna (por referência) a média móvel final da turma ao longo dos períodos
        considerando uma iteração de N_MEDIA_MOVEL. Cada posição do vector mediaMovel informado
        como parâmetro conterá a média móvel no respectivo período, ou seja,
        a posição do vector mediaMovel representa o periodo letivo em questão. */
        void getMediaMovel(vector<float> &mediaMovel);

    private:
        string nome;                      // nome da disciplina
        int id;                           // id de idenficação da disciplina
        vector<Aluno> alunosMatriculados; // lista de alunos matriculados

        /* Calcula a média final da turma em cada período. */
        void calcularMedia(vector<float> &mediaFinal);

        /* Calcula a média móvel final da turma ao longo dos períodos considerando um espaço de
        médias iguais ao valor definido na macro N_MEDIA_MOVEL. */
        void calcularMediaMovel(vector<float> &mediaMovel);
};

#endif