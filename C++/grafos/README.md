ATIVIDADE AVALIATIVA 2 DA DISCIPLINA DE LINGUAGENS DE PROGRAMAÇÃO - 2023/2

Desenvolvido por Leonardo Fachetti Jovêncio


PROJETO: 
Implementação de uma classe denominada Grafo contendo uma série de métodos que permitem
trabalhar com um grafo simétrico não-orientado.


DESCRIÇÃO DO PROJETO: 
O programa realiza a leitura de um arquivo de texto .txt contendo as arestas e seus respectivos
pesos referente a um grafo simétrico não-orientado. A partir dessas informações, o programa cria
um grafo e disponibiliza os seguintes métodos públicos a serem  usados pelo usuário:

    1 - inserirArestas
    2 - imprimirVertices
    2 - getNumeroVertices
    3 - imprimirEnlaces
    4 - imprimirMatrizAdjacencias
    5 - menorCaminho
    6 - densidadeGrafo
    7 - maiorCentralidade

A classe implementada Grafo possui os seguintes atributos privados:

    . vector<string> idVertices;    // guarda o código de identificação (id) referentes aos vértices
    . size_t numeroVertices;        // número de vértices do grafo
    . short int numeroArestas;      // número de arestas do grafo
    . float *matrizAdjacencia;      // um ponteiro apontando para a matriz de adjacências do grafo


FUNCIONALIDADES DO PROJETO: 
A classe Grafo é composta pelos seguintes métodos públicos:

        void inserirArestas(string file, short int &status);
        /* Recebe um arquivo (file) txt contendo os vértices, arestas e pesos
        * e cria um grafo simétrico não-orientado. O arquivo txt terá o seguinte padrão de formatação:
        *
        *      verticeOrigem verticeDestino peso
        *
        * A separação entre os valores é feita por um ÚNICO caractere de espaço.
        * Exemplo de arquivo txt válido:
        *      A B 2,2
        *      B C 1,0
        *      C D 3,1
        *      A C 1,2
        * 
        * Além disso, o método inserirArestas retorna na variável (passada por referência) status se a construção foi
        * bem realizada com sucesso (retorna SUCESSO=0) ou não. Caso não seja, será retornado um código de erro
        * que pode ser interpretado a partir da variável enum status.
        */

        void imprimirVertices(void);
        // Imprimi na tela todos os vérices do grafo

        int getNumeroVertices(void);
        // Retorna o número de vértices do grafo

        void imprimirEnlaces(void);
        // Imprimir na tela a lista de enlaces existentes no grafo

        void imprimirMatrizAdjacencias(void);
        // Imprimi na tela a matriz de adjacências do grafo

        void menorCaminho(short int origem, short int destino);
        // Imprimi na tela a distância do menor caminho entre o vértice de origem ao de destino

        void densidadeGrafo(void);
        // Imprimi na tela a densidade do grafo

        void maiorCentralidade(void);
        // Imprimi na tela o vértice com a maior centralidade e seu respectivo valor


TESTE DO PROGRAMA: Para o teste do programa, existe uma base de dados armazenada no arquivo dados.txt contendo 30
arestas de um grafo cujas arestas são várias cidades do Brasil. Ao todo, são 12 cidades (vértices).

    Exemplos de arestas:
    . Linhares Vitoria 137
    . Vitoria Rio-de-Janeiro 517
    . Belo-Horizonte Linhares 601
    . Vitoria Belo-Horizonte 516
    . Linhares Salvador 1037

- Arquivo com todas as arestas do grado: dados.txt
- Arquivo contendo todas as cidades do grafo: cidades.txt


INICIALIZAÇÃO:
Foi disponibilizado um arquivo Makefile contendo os seguintes rótulos:

    . make ou make all   -> gera o executável do programa
    . make run   		 -> roda o programa
    . make clean 		 -> apaga todos os arquivos