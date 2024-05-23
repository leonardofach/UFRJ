**ATIVIDADE AVALIATIVA 3 DA DISCIPLINA DE LINGUAGENS DE PROGRAMAÇÃO - 2023/2**

Desenvolvido por Leonardo Fachetti Jovêncio


**PROJETO**: 
Implementação de uma classe denominada Historico para o gerenciamento de disciplinas.

**ARQUIVO MAKEFILE:**
Foi disponibilizado um arquivo Makefile contendo os seguintes rótulos:

    . make ou make all   -> gera o executável do programa
    . make run   		 -> roda o programa
    . make clean 		 -> apaga todos os arquivos objetos e executáveis 

**DESCRIÇÃO DO PROJETO:** 
O programa principal definido no arquivo main.cpp realiza a leitura do arquivo de texto dados_historico.txt contendo
a base de dados do historico e oferece 8 opções de menu para o usuário, sendo elas:

    [1] - Imprimir TODAS as disciplinas do histórico
    [2] - Imprimir UMA disciplina do histórico
    [3] - Inserir UMA nova disciplina no histórico
    [4] - Inserir VÁRIAS novas disciplinas no histórico
    [5] - Remover uma disciplina do histórico
    [6] - Buscar disciplina do histórico
    [7] - Editar nota de uma disciplina do histórico
    [8] - Calcular CRA


Para realizar as funcionalidades do programa, foi implementado uma classe chamada Historico cujo protótipo está definido
no arquivo historico.h. A classe Historico possui os seguintes métodos públicos:

    1 - getDisciplina
    2 - getNumeroDisciplinas
    2 - getMaximoDisciplinas
    3 - operator+=
    4 - operator-=
    5 - operator()
    6 - calcularCRA

A classe implementada Historico possui os seguintes atributos privados:

    . vector<Disciplina> disciplinas;           // guarda todas as disciplinas cadastradas no historico
    . const short int maximoDisciplinas = 50;   // número máximo de disciplinas permitidas a serem cadastradas


**DESCRIÇÃO DOS MÉTODOS DA CLASSE HISTÓRICO:** 
A classe Hstorico é composta pelos seguintes métodos públicos:

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


**FUNÇÕES AUXILIARES:**
O programa implementado faz o uso de funções auxiliares cujos protótipos estão definidos no arquivo
funcoes_auxiliares.h. Essas funções são:

        int StringToInt (string input);
        /* Converte uma string para um inteiro positivo.
         * A função retorna -1 se a conversão não for bem sucedida */

        double StringToDouble (string input);
        /* Converte uma string para um double positivo.
         * A função retorna -1 se a conversão não for bem sucedida */