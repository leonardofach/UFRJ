/***********************************************************************************
 * UNIVERSIDADE FEDERAL O RIO DE JANEIRO
 *
 * Aluno: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônica e de computação
 *
 * Disciplina: Linguagens de programação - 23/2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 03/12/2023
 * Arquivo: main.cpp
 * Descrição: Arquivo contendo a implementação do programa principal main.
 * **********************************************************************************/

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "disciplina.h"

using namespace std;

int main(void)
{
    unsigned semente;
    float notaSorteada;
    vector<Aluno> listaAlunos;
    vector<Disciplina> listaDisciplinas;
    string opcaoMenu, infoEntrada;

    // Inicializando os dados
    vector<string> nomesAlunos = {"Leonardo",
                                  "Lucas",
                                  "Luís Henrique",
                                  "Eloiza",
                                  "Thiago",
                                  "Beatriz",
                                  "Fábio",
                                  "Ana",
                                  "Leandro",
                                  "Daniel"};

    vector<string> nomesDisciplinas = {"Controle I",
                                       "Comunicações I",
                                       "Modelos probabilísticos",
                                       "Linguagem de programação",
                                       "Sistemas Digitais"};

    // Criando os objetos da classe Aluno
    semente = time(0);
    for (int aluno=0; aluno < NUM_ALUNOS; aluno++)
    {
        vector<vector<float>> dbNotas;

        for (int periodo=0; periodo < NUM_PERIODOS; periodo++)
        {
            vector<float> notas;

            for (int disciplina=0; disciplina < NUM_DISCIPLINAS; disciplina++)
            {
                semente += 1; // para forçar a mudança da semente a cada sorteio
                srand(semente);
                notaSorteada = 1 + rand() % 10; // sorteando notas entre 1 a 10;
                if (notaSorteada < 3)
                    notaSorteada = 5;
                notas.push_back(notaSorteada);
            }
            dbNotas.push_back(notas);
        }
        
        Aluno dadosAluno(nomesAlunos[aluno], dbNotas); // criando a list de alunos
        listaAlunos.push_back(dadosAluno);
    }

    // Criando os objetos da classe Disciplina
    for (int i=0; i < NUM_DISCIPLINAS; i++)
    {
        Disciplina dadosDisciplina(nomesDisciplinas[i], i, listaAlunos);
        listaDisciplinas.push_back(dadosDisciplina);
    }

    // Menu do sistema
    do
    {
        cout << "----------------------------------- MENU ---------------------------------------------------" << endl;
        cout << "[0] - Sair" << endl;
        cout << "[1] - Exibir evolucao da media móvel final das disciplinas nos ultimos periodos" << endl;
        cout << "[2] - Exibir disciplinas que apresentaram melhoria e piora de desempenho" << endl;
        cout << "[3] - Exibir a evolucao individual de cada aluno" << endl;
        cout << "[4] - Exibir a disciplina com a maior media de nota final" << endl;
        cout << "[5] - Exibir a disciplina que teve a maior evolucao da media da nota final no ultimo periodo" << endl;
        cout << "[6] - Exibir o melhor aluno no periodo" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;

        cout << "Escolha uma opcao do MENU: ";
        getline(cin, opcaoMenu);

        if (opcaoMenu == "0")
        {
            cout << "\nPrograma encerrado com sucesso!" << endl;
            break;
        }

        else if (opcaoMenu == "1")
        {
            cout << endl << endl;
            cout << "--------------------------------------------------------------------------------------------" << endl;
            cout << setw(40) << "PERÍODOS" << setw(53) << "DISCIPLINAS" << endl;
            cout << "--------------------------------------------------------------------------------------------" << endl;
            for (int i=0; i < NUM_DISCIPLINAS; i++)
            {
                vector<float> mediaMovel;
                listaDisciplinas[i].getMediaMovel(mediaMovel);

                for (float media : mediaMovel)
                {
                    if (media == -1)
                        cout << "-" << setw(10);
                    else 
                        cout << setprecision(2) << fixed << media << setw(10);
                }
                cout << "  " << listaDisciplinas[i].getNome() << endl;
            }
            cout << endl << endl;
        }

        else if (opcaoMenu == "2")
        {
            cout << endl << endl;
            vector<float> desempenho;

            for(int i=0; i < NUM_DISCIPLINAS; i++)
            {
                vector<float> mediaMovel;
                listaDisciplinas[i].getMediaMovel(mediaMovel);

                // NUM_PERIODOS - 1 = período atual  |  NUM_PERIODOS - 2 = periodo anterior
                float aux = mediaMovel[NUM_PERIODOS - 1] / mediaMovel[NUM_PERIODOS - 2];
                desempenho.push_back (aux);
            }

            cout << "DISCIPLINAS QUE APRESENTARAM MELHORA" << endl;
            for (int i=0; i < NUM_DISCIPLINAS; i++)
            {
                if (desempenho[i] > 1.05)
                    cout << setw(2) << "* " << listaDisciplinas[i].getNome() << endl;
            }

            cout << endl << "DISCIPLINAS QUE APRESENTARAM PIORA" << endl;
            for (int i=0; i < NUM_DISCIPLINAS; i++)
            {
                if (desempenho[i] < 1)
                    cout << setw(2) << "* " << listaDisciplinas[i].getNome() << endl;
            }

            cout << endl << "DISCIPLINAS QUE NÃO SOFRERAM VARIAÇÃO" << endl;
            for (int i=0; i < NUM_DISCIPLINAS; i++)
            {
                if (desempenho[i] >= 1 && desempenho[i] <= 1.05)
                    cout << setw(2) << "* " << listaDisciplinas[i].getNome() << endl;
            }
            cout << endl << endl;
        }

        else if (opcaoMenu == "3")
        {
            vector<float> desempenhoAlunos;

            cout << endl << endl;
            for (int i=0; i < NUM_ALUNOS; i++)
            {
                vector<float> mediaMovelAluno;
                listaAlunos[i].getMediaMovel(mediaMovelAluno);

                // NUM_PERIODOS - 1 = período atual  |  NUM_PERIODOS - 2 = periodo anterior
                float aux = mediaMovelAluno[NUM_PERIODOS - 1] / mediaMovelAluno[NUM_PERIODOS - 2];
                desempenhoAlunos.push_back (aux);
            }

            cout << "ALUNOS QUE APRESENTARAM MELHORA" << endl;
            for (int i=0; i < NUM_ALUNOS; i++)
            {
                if (desempenhoAlunos[i] > 1.05)
                    cout << setw(2) << "* " << listaAlunos[i].getNome() << endl;
            }

            cout << endl << "ALUNOS QUE APRESENTARAM PIORA" << endl;
            for (int i=0; i < NUM_ALUNOS; i++)
            {
                if (desempenhoAlunos[i] < 1)
                    cout << setw(2) << "* " << listaAlunos[i].getNome() << endl;
            }

            cout << endl << "ALUNOS QUE NÃO SOFRERAM VARIAÇÃO" << endl;
            for (int i=0; i < NUM_ALUNOS; i++)
            {
                if (desempenhoAlunos[i] >= 1 && desempenhoAlunos[i] <= 1.05)
                    cout << setw(2) << "* " << listaAlunos[i].getNome() << endl;
            }
            cout << endl << endl;
        }

        else if (opcaoMenu == "4")
        {
            cout << endl << endl;

            vector<float> medias;

            for (int i=0; i < NUM_DISCIPLINAS; i++)
            {
                float soma = 0;
                
                vector<float> mediaDisciplina;
                listaDisciplinas[i].getMedia(mediaDisciplina);
                
                for (int p=0; p < NUM_PERIODOS; p++)
                    soma += mediaDisciplina[p]; 

                medias.push_back(soma / NUM_PERIODOS);
            }
            
            int maior = 0;  // posição da disciplina com a maior média

            for (int i=1; i < NUM_DISCIPLINAS; i++)
                if(medias[i] > medias[maior])
                    maior = i;

            cout << "* " << listaDisciplinas[maior].getNome() << setw(10);
            cout << "Media: " << setprecision(2) << fixed << medias[maior] << endl << endl << endl;
        }

        else if (opcaoMenu == "5")
        {
            cout << endl << endl;
            vector<float> desempenho;

            for(int i=0; i < NUM_DISCIPLINAS; i++)
            {
                vector<float> mediaMovel;
                listaDisciplinas[i].getMediaMovel(mediaMovel);

                // NUM_PERIODOS - 1 = período atual  |  NUM_PERIODOS - 2 = periodo anterior
                float aux = mediaMovel[NUM_PERIODOS - 1] / mediaMovel[NUM_PERIODOS - 2];
                desempenho.push_back (aux);
            }

            int maior=0;  // posição da disciplina com a melhor desempenho
            
            for (int i=0; i < NUM_DISCIPLINAS; i++)
                if (desempenho[i] > desempenho[maior])
                    maior = i;
            
            cout << "* " << listaDisciplinas[maior].getNome() << endl << endl << endl;
        }

        else if (opcaoMenu == "6")
        {
            vector<int> alunosMaiorMedia; // guarda os alunos com as maiores médias por período
            vector<float> maioresMedias;  // guarda as maiores meédias por período

            cout << endl << endl;
            for (int p=0; p < NUM_PERIODOS; p++)
            {
                int posAluno;      // posição do aluno com a maior média final no periodo p
                float maiorMedia;  // média do aluno com a maior média final no periodo p

                for (int i=0; i < NUM_ALUNOS; i++)
                {
                    vector<float> mediaAluno;
                    listaAlunos[i].getMedia(mediaAluno);
                    
                    if (i==0) // primeira verificação
                    {
                        posAluno = 0;
                        maiorMedia = mediaAluno[p];
                        continue;
                    }

                    if (mediaAluno[p] > maiorMedia)
                    {
                        posAluno = i;
                        maiorMedia = mediaAluno[p];
                    }
                }

                alunosMaiorMedia.push_back(posAluno);
                maioresMedias.push_back(maiorMedia);
            }
            
            for (int p=0; p < NUM_PERIODOS; p++)
            {
                cout << "Período " << p << setw(    30) << "Média: " << setprecision(2) << fixed << maioresMedias[p] << setw(30);
                cout << listaAlunos[p].getNome() << endl;
            }
            cout << endl << endl;
        }

        else
        {
            cout << "Opcao invalida! Por favor, informe uma opcao valida do MENU!" << endl;
            continue;
        }

    } while (opcaoMenu != "0");

    return 0;
}

