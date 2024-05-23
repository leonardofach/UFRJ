/***************************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 12/10/2023
 * Arquivo: main.cpp
 * Descrição: Arquivo contendo o programa principal main.
 ***************************************************************/

#include "grafo.h"

int main(void)
{
    short int status, verticeOrigem, verticeDestino, numeroVertices, imprimirMenu;
    string opcaoMenu, entradaDados;
    Grafo cidades;     

    // construindo o grafo a partir dos dado do arquivo txt
    cidades.inserirArestas("dados.txt", status);

    if (status != SUCESSO)
    {
        cout << "ERRO ao construir o grafo! -- Código de ERRO: " << status << endl;
        return status;
    }

    // Menu do programa
    imprimirMenu = 0;        // imprimirMenu=0 -> imprimir menu |  imprimirMenu=1 -> não imprimir menu
    do
    {
        if (imprimirMenu == 0)
        {
            cout << "******************************************** MENU ******************************************" << endl;
            cout << "[0] - Sair" << endl;
            cout << "[1] - Imprimir lista de enlaces do grafo" << endl;
            cout << "[2] - Imprimir matriz de adjacências" << endl;
            cout << "[3] - Exibir o custo do menor caminho entre dois vértices escolhidos" << endl;
            cout << "[4] - Imprimir densidade do grafo" << endl;
            cout << "[5] - Imprimir o vértice com a maior centralidade de proximidade" << endl;
            cout << "*********************************************************************************************" << endl;
        }

        cout << "Escolha uma opcao do MENU: ";
        getline(cin, opcaoMenu);

        if (opcaoMenu == "0")
        {
            cout << "\nPrograma encerrado com sucesso!" << endl;
            break;
        }

        else if (opcaoMenu == "1")
        {
            cidades.imprimirEnlaces();
            imprimirMenu = 0;
        }

        else if (opcaoMenu == "2")
        {
            cidades.imprimirMatrizAdjacencias();
            imprimirMenu = 0;
        }

        else if (opcaoMenu == "3")
        {
            cidades.imprimirVertices();
            numeroVertices = cidades.getNumeroVertices();

            cout << endl << "id vértice origem: ";
            getline (cin, entradaDados);

            verticeOrigem = 0;
            for (char caractere : entradaDados)
            {
                if (caractere >= '0' && caractere <= '9') 
                    verticeOrigem += verticeOrigem * 10 + (caractere - '0');            
                else 
                {
                    cout << "ERRO! Entrada inválida!" << endl;
                    return ERRO_ENTRADA_USUARIO;
                }
            }

            cout << "id vértice destino: ";
            getline (cin, entradaDados);

            verticeDestino = 0;
            for (char caractere : entradaDados)
            {
                if (caractere >= '0' && caractere <= '9') 
                    verticeDestino += verticeDestino * 10 + (caractere - '0');            
                else 
                {
                    cout << "ERRO! Entrada inválida!" << endl;
                    return ERRO_ENTRADA_USUARIO;
                }
            }

            if (verticeOrigem > numeroVertices || verticeDestino > numeroVertices)
            {
                cout << "ERRO! Entrada inválida! Os vértices informados não são válidos!" << endl;
                return ERRO_ENTRADA_USUARIO;
            }
            else
            {
                cout << endl;
                cidades.menorCaminho(verticeOrigem, verticeDestino);
                imprimirMenu = 0;
            }
        }

        else if (opcaoMenu == "4")
        {
            cidades.densidadeGrafo();
            imprimirMenu = 0;
        }

        else if (opcaoMenu == "5")
        {
            cidades.imprimirVertices();
            cidades.maiorCentralidade();
            imprimirMenu = 0;
        }

        else
        {
            // MELHORAR
            cout << "Opcao invalida! Por favor, informe uma opcao valida do MENU!" << endl;
            imprimirMenu = 1;
            continue;
        }

    } while (opcaoMenu != "0");

    return SUCESSO;   // 0
}