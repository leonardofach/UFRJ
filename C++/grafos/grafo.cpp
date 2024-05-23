/****************************************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 12/10/2023
 * Arquivo: grafo.cpp
 * Descrição: Arquivo contendo a implementação dos métodos da classe Grafo.
 ******************************************************************************/

#include "grafo.h"

// Métodos públicos da classe Grafo
void Grafo::inserirArestas(string fileName, short int &status)
{
    short int statusGravarDados;

    gravarDados(fileName, statusGravarDados);

    if (statusGravarDados == SUCESSO)
        status = SUCESSO;
    else
        status = statusGravarDados;
}

void Grafo::imprimirVertices(void)
{
    size_t contador;
    cout << endl;
    for (contador = 0; contador < numeroVertices; contador++)
        cout << "id[" << contador << "] = " << idVertices[contador] << endl;
}

int Grafo::getNumeroVertices (void)
{
    return static_cast <int> (numeroVertices);
}

void Grafo::imprimirEnlaces(void) // opção 1 do menu
{
    size_t linha, coluna;
    vector<string> enlaces;

    cout << endl
         << "Numero de enlaces: " << numeroArestas << endl;

    for (linha = 0; linha < numeroVertices; linha++)
    {
        for (coluna = linha + 1; coluna < numeroVertices; coluna++) // apenas a diagonal superior
            if (matrizAdjacencia[linha * numeroVertices + coluna] != 0)
                cout << "* " << idVertices[linha] << " -- " << idVertices[coluna] << endl;
    }
    cout << endl;
}

void Grafo::imprimirMatrizAdjacencias(void) // opção 2 do menu
{
    size_t linha, coluna;

    cout << endl << "Dimensao (numero de vértices): " << numeroVertices << endl << endl;

    for (linha = 0; linha < numeroVertices; linha++)
    {
        for (coluna = 0; coluna < numeroVertices; coluna++)
            cout << setw(8) << matrizAdjacencia[linha * numeroVertices + coluna] << setw(8);
        cout << endl;
    }
    cout << endl;
}

void Grafo::menorCaminho(short int verticeOrigem, short int verticeDestino) // opção 3 do menu
{
    float distancia[numeroVertices];

    algoritmoDijkstra(verticeOrigem, verticeDestino, distancia);
    cout << "Menor distância: " << distancia[verticeDestino] << endl; 
}

void Grafo::densidadeGrafo(void) // opção 4 do menu
{
    // caso grafo não orientado
    cout << endl
         << "Densidade = " << static_cast<float>(static_cast<float>(2 * numeroArestas) / (numeroVertices * (numeroVertices - 1))) << endl
         << endl;
}

void Grafo::maiorCentralidade(void) // opção 5 do menu
{
    float soma, somaDistancias, distancia[numeroVertices];
    double centralidades[numeroVertices];
    short int verticeMaiorCentralidade;
    size_t verticeOrigem, verticeDestino;

    // calculando a centralidade para cada um os vértices
    for (verticeOrigem = 0; verticeOrigem < numeroVertices; verticeOrigem++)
    {
        for (verticeDestino = somaDistancias = 0; verticeDestino < numeroVertices; verticeDestino++)
        {
            algoritmoDijkstra(verticeOrigem, verticeDestino, distancia);
            
            soma = distancia[verticeDestino];
            if (soma < 0)
                soma = soma * (-1);
            somaDistancias += soma;
        }
        centralidades[verticeOrigem] = 1 / somaDistancias;
    }

    verticeMaiorCentralidade = 0;
    for (verticeOrigem = 1; verticeOrigem < numeroVertices; verticeOrigem++)
        if (centralidades[verticeOrigem] > centralidades[verticeMaiorCentralidade])
            verticeMaiorCentralidade = verticeOrigem;
    
    cout << endl
         << "Vertice de maior centralidade: id[" << verticeMaiorCentralidade << "] = " << centralidades[verticeMaiorCentralidade] << endl
         << endl;
}

// Métodos privados da classe Grafo
void Grafo::algoritmoDijkstra(short int verticeOrigem, short int verticeDestino, float *distancia)
{
    size_t linha, coluna;
    list<pair<int, float>> *adj;

    adj = new list<pair<int, float>>[numeroVertices];

    for (linha = 0; linha < numeroVertices; linha++) // varrendo a matriz de adjacencias
    {
        for (coluna = linha + 1; coluna < numeroVertices; coluna++) // apenas a diagonal superior
            if (matrizAdjacencia[linha * numeroVertices + coluna] != 0)
            {
                // como o grafo é não orietado, fazemos o enlace em ambos os sentidos serem iguais
                adj[linha].push_back(make_pair(coluna, matrizAdjacencia[linha * numeroVertices + coluna]));
                adj[coluna].push_back(make_pair(linha, matrizAdjacencia[coluna * numeroVertices + linha]));
            }
    }

    /*
        vetor de visitados serve para caso o vértice já tenha sido
        expandido (visitado), não expandir mais
    */
    int visitados[numeroVertices];

    // fila de prioridades de pair (distancia, vértice)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // inicia o vetor de distâncias e visitados
    for (size_t i = 0; i < numeroVertices; i++)
    {
        distancia[i] = INFINITO;
        visitados[i] = false;
    }

    // a distância de orig para orig é 0
    distancia[verticeOrigem] = 0;

    // insere na fila
    pq.push(make_pair(distancia[verticeOrigem], verticeOrigem));

    // loop do algoritmo
    while (!pq.empty())
    {
        pair<float, float> p = pq.top(); // extrai o pair do topo
        int u = p.second;                // obtém o vértice do pair
        pq.pop();                        // remove da fila

        // verifica se o vértice não foi expandido
        if (visitados[u] == false)
        {
            // marca como visitado
            visitados[u] = true;

            list<pair<int, float>>::iterator it;

            // percorre os vértices "v" adjacentes de "u"
            for (it = adj[u].begin(); it != adj[u].end(); it++)
            {
                // obtém o vértice adjacente e o custo da aresta
                int v = it->first;
                float custo_aresta = it->second;

                // relaxamento (u, v)
                if (distancia[v] > (distancia[u] + custo_aresta))
                {
                    // atualiza a distância de "v" e insere na fila
                    distancia[v] = distancia[u] + custo_aresta;
                    pq.push(make_pair(distancia[v], v));
                }
            }
        }
    }
}

void Grafo::gravarDados(string fileName, short int &status)
{
    vector<string> listaIdVertices, listaEnlacesOrigem, listaEnlacesDestino;
    vector<float> listaPesos;
    short int statusValidarDados, contadorEnlaces;
    size_t contador1, contador2, origem, destino;

    validarDados(fileName, listaIdVertices, listaPesos, listaEnlacesOrigem, listaEnlacesDestino, statusValidarDados);

    if (statusValidarDados == SUCESSO)
    {
        numeroVertices = listaIdVertices.size(); // atribuindo o atributo privado dimensao

        // Alocando memória para matrizAdjacencia e iniciando valores em 0
        matrizAdjacencia = (float *)malloc(numeroVertices * numeroVertices * sizeof(float));
        for (contador1 = 0; contador1 < numeroVertices; contador1++)
            for (contador2 = 0; contador2 < numeroVertices; contador2++)
                matrizAdjacencia[contador1 * numeroVertices + contador2] = 0;

        // construindo a matriz de adjacências
        for (contador1 = contadorEnlaces = 0; contador1 < listaPesos.size(); contador1++) // varrendo arestas
        {
            for (contador2 = 0; contador2 < listaIdVertices.size(); contador2++) // identificando o id do vértice
            {
                if (listaEnlacesOrigem[contador1] == listaIdVertices[contador2])
                    origem = contador2; // linha

                if (listaEnlacesDestino[contador1] == listaIdVertices[contador2])
                    destino = contador2; // coluna
            }
            contadorEnlaces++;
            matrizAdjacencia[origem * numeroVertices + destino] = listaPesos[contador1]; // [linha][coluna]
            matrizAdjacencia[destino * numeroVertices + origem] = listaPesos[contador1]; // [coluna][linha]
        }

        idVertices = listaIdVertices;    // atribuindo o atributo privado idVertices
        numeroArestas = contadorEnlaces; // atribuindo o atributo privado numeroEnlaces
        status = SUCESSO;
    }
    else
        status = statusValidarDados;
}

void Grafo::validarDados(string fileName, vector<string> &listaIdVertices, vector<float> &listaPesos,
                         vector<string> &listaEnlacesOrigem, vector<string> &listaEnlacesDestino, short int &status)
{
    size_t contador1, contador2;
    vector<string> dados, stringDividida, listaVerticesAux;
    string pedacoString;
    short int statusLeitura, controle;

    lerArquivo(fileName, dados, statusLeitura);

    if (statusLeitura == ERRO_LEITURA_ARQUIVO)
        status = ERRO_LEITURA_ARQUIVO;
    else
    {
        for (contador1 = 0; contador1 < dados.size(); contador1++) // varrendo cada linha de dados
        {
            stringDividida.clear();
            stringstream stringStream(dados[contador1]); // construindo uma stream a partir da string

            while (getline(stringStream, pedacoString, ' '))
                stringDividida.push_back(pedacoString);

            if (stringDividida.size() > 3) // arquivo estaria numa formatação inválida -> VerticeOrigem VerticeDestino peso
                status = ERRO_FORMATACAO_ARQUIVO;
            else
            {
                listaVerticesAux.push_back(stringDividida[0]);
                listaVerticesAux.push_back(stringDividida[1]);

                listaEnlacesOrigem.push_back(stringDividida[0]);
                listaEnlacesDestino.push_back(stringDividida[1]);
                listaPesos.push_back(stof(stringDividida[2])); // para simplificar, estou assumindo que a formatação do peso está correta no txt
            }
        }
    }

    // Obtendo os id dos vertíces -> eliminando vertíces repetidos adicionados em listaVerticesAux
    for (contador1 = 0; contador1 < listaVerticesAux.size(); contador1++)
    {
        if (contador1 == 0) // adicionando o primeiro termo
        {
            listaIdVertices.push_back(listaVerticesAux[0]);
            continue;
        }
        else // tem que avaliar se o vertíce já existe em listaVertice
        {
            for (contador2 = controle = 0; contador2 < listaIdVertices.size(); contador2++)
            {
                if (listaVerticesAux[contador1] == listaIdVertices[contador2])
                    controle = 1; // já tem
            }

            if (controle == 0)
                listaIdVertices.push_back(listaVerticesAux[contador1]);
            else
                continue;
        }
    }

    // Validando os dados
    if (listaPesos.size() < NUMERO_MINIMO_ARESTAS)
        status = ERRO_MINIMO_ARESTAS;

    else if (listaPesos.size() > NUMERO_MAXIMO_ARESTAS)
        status = ERRO_MAXIMO_ARESTAS;

    else if (listaIdVertices.size() < NUMERO_MINIMO_VERTICES)
        status = ERRO_MINIMO_VERTICES;

    else if (listaIdVertices.size() > NUMERO_MAXIMO_VERTICES)
        status = ERRO_MAXIMO_VERTICES;

    else
        status = SUCESSO;
}

void Grafo::lerArquivo(string fileName, vector<string> &dados, short int &status)
{
    string linha;
    fstream file;

    file.open(fileName.c_str(), fstream::in | fstream::out | fstream::app);

    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, linha);
            dados.push_back(linha);
        }
        file.close();
        status = SUCESSO;
    }
    else
        status = ERRO_LEITURA_ARQUIVO;
}