ATIVIDADE AVALIATIVA 1 DA DISCIPLINA DE LINGUAGENS DE PROGRAMAÇÃO - 2023/2

Desenvolvido por Leonardo Fachetti Jovêncio


PROJETO: 
Implementação de um programa de gerenciamento de disciplinas.


DESCRIÇÃO DO PROJETO: 
O programa fornece ao usuário diversas ferramentas úteis para realizar o 
dgerenciamento de disciplinas. Para tal, ele oferece a possibilidade de cadastrar
várias disciplinas e gerenciá-las individualmete, realizando à matrícula dos
alunos em cada periodo letivo, bem como diversas métricas para avaliar o desempenho
dos alunos.

Para implementação do programa, duas classes foram desenvolvidas oferecendo os seguintes métodos publicos:

    CLASSE ALUNO:
    1 - setNome
    2 - setNotas
    2 - getNome
    3 - getNotas
    4 - printDados
    5 - getMedia
    6 - getMediaMovel

    CLASSE DISCIPLINA:
    1 - setNome
    2 - setId
    2 - matricularAlunos
    3 - getNome
    4 - getAluno
    5 - getMedia
    6 - getMediaMovel

As classes implementadas possuem os seguintes atributos privados:

    CLASSE ALUNO:
    string nome;                    // nome do aluno
    vector<vector<float>> notas;    // notas do aluno

    o vector notas possui a seguinte estrutura para armazenamento das notas do aluno:

    notas = [[disciplina1, disciplina2, ... , disciplinaN],   referente ao período 1
             [disciplina1, disciplina2, ... , disciplinaN],   referente ao período 2
                                    ...                                  ...
             [disciplina1, disciplina2, ... , disciplinaN]]   referente ao período N
    
    CLASSE DISCIPLINA:
    string nome;                      // nome da disciplina
    int id;                           // id de idenficação da disciplina
    vector<Aluno> alunosMatriculados; // lista de alunos matriculados a disciplina

FUNCIONALIDADES DO PROJETO: 
A classe Aluno é composta pelos seguintes métodos públicos:

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

A classe Disciplina é composta pelos seguintes métodos públicos:

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

ARQUIVO MAKEFILE:
Foi disponibilizado um arquivo Makefile contendo os seguintes rótulos:

    . make ou make all   -> gera o executável do programa
    . make run   		 -> roda o programa
    . make clean 		 -> apaga todos os arquivos