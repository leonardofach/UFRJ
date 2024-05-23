/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 02/11/2023
 * Arquivo: main.cpp
 * Descrição: Implementação do programa principal main.
 *******************************************************/

#include <vector>
#include "historico.h"
#include "funcoes_auxiliares.h"

int main(void)
{
    Historico historico;
    Disciplina disciplinaTemporaria;
    vector<Disciplina> disciplinasTemporarias;
    vector<short int> idsDisciplinas;
    string opcaoMenu, imprimirMenu, inputUsuario_1, inputUsuario_2;
    int num;
    short int idDisciplina, status;
    double nota;

    // Carregando os dados do histórico
    status = carregarDados ("dados_historico.txt", historico);

    if (status == 0)
        cout << endl << "Dados carregados com sucesso!" << endl << endl;

    else
    {
        cout << endl << "Erro ao carregar os dados!" << endl;
        cout << "Programa encerrado!" << endl << endl;
        return -1;
    }

    // Menu do programa
    do
    {
        cout << "Pressione a tecla m para ir ao menu: ";
        getline(cin, imprimirMenu);
        cout << endl;

        // Validando a entrada do usuário
        if ((imprimirMenu.size() != 2) && imprimirMenu[0] != 'm')
        {
            cout << "Opção inválida!" << endl;
            continue;
        }

        cout << "----------------------------------- MENU ------------------------------------" << endl;
        cout << "[0] - Sair" << endl;
        cout << "[1] - Imprimir TODAS as disciplinas do histórico" << endl;
        cout << "[2] - Imprimir UMA disciplina do histórico" << endl;
        cout << "[3] - Inserir UMA nova disciplina no histórico" << endl;
        cout << "[4] - Inserir VÁRIAS novas disciplinas no histórico" << endl;
        cout << "[5] - Remover uma disciplina do histórico" << endl;
        cout << "[6] - Buscar disciplina do histórico" << endl;
        cout << "[7] - Editar nota de uma disciplina do histórico" << endl;
        cout << "[8] - Calcular CRA" << endl;
        cout << "------------------------------------------------------------------------------" << endl;

        cout << "Escolha uma opcao do MENU: ";
        getline(cin, opcaoMenu);

        if (opcaoMenu == "0")
        {
            cout << "\nPrograma encerrado com sucesso!" << endl;
            break;
        }

        else if (opcaoMenu == "1")
            cout << historico;

        else if (opcaoMenu == "2") 
        {
            for (;;)
            {
                cout << "Informe o id da disciplina: ";
                getline(cin, inputUsuario_1);

                num = StringToInt(inputUsuario_1); // retorna -1 se conversão for inválida

                // Validando a entrada do usuário
                if (num == -1)
                {
                    cout << "Id inválido!" << endl;
                    continue;
                }

                if (num > (historico.getMaximoDisciplinas() - 1))
                {
                    cout << "Id inválido!" << endl;
                    cout << "Superior ao valor máximo de disciplinas permitidas a serem cadastradas no histórico!" << endl;
                    continue;
                }

                if (num > (historico.getNumeroDisciplinas() - 1))
                {
                    cout << "Id inválido!" << endl;
                    cout << "Superior ao número de disciplinas cadastradas no histórico!" << endl;
                    continue;
                }

                break;
            }

            cout << historico.getDisciplina(num);
        }

        else if (opcaoMenu == "3")
        {
            cin >> disciplinaTemporaria;
            idDisciplina = historico += disciplinaTemporaria;

            if (idDisciplina == -1)
            {
                cout << "ERRO! Disciplina já cadastrada -> status [" << idDisciplina << "]" << endl << endl;
                continue;
            }

            cout << "Disciplina adicionada no indice [" << idDisciplina << "]" << endl << endl;
            limparDisciplina(disciplinaTemporaria);
        }

        else if (opcaoMenu == "4")
        {
            for (;;)
            {
                cout << "Número de disciplinas a serem inseridas (mínimo = 1 e máximo = 10): ";
                getline(cin, inputUsuario_1);

                num = StringToInt(inputUsuario_1); // retorna -1 se conversão for inválida

                // Validando a entrada do usuário
                if (num == -1)
                {
                    cout << "Número inválido!" << endl;
                    continue;
                }

                if ((num + historico.getNumeroDisciplinas()) > historico.getMaximoDisciplinas())
                {
                    cout << "Valor inválido!" << endl;
                    cout << "O histórico permite cadastrar no máximo " << historico.getMaximoDisciplinas() << " disciplinas!" << endl;
                    cout << "Disciplinas restantes: " << historico.getMaximoDisciplinas() - historico.getNumeroDisciplinas() << endl;
                    continue;
                }

                if (num < 1 || num > 10)
                {
                    cout << "O valor informado está fora do intervalo permitido!" << endl;
                    continue;
                }

                break;
            }

            for (int i = 0; i < num; i++)
            {
                cout << endl
                     << "Disciplina " << i + 1 << "/" << num << endl;
                cin >> disciplinaTemporaria;
                disciplinasTemporarias.push_back(disciplinaTemporaria);
                limparDisciplina(disciplinaTemporaria);
            }

            idsDisciplinas = historico += disciplinasTemporarias; // adicionando as novas disciplinas no histórico

            for (size_t i = 0; i < idsDisciplinas.size(); i++)
            {
                if (idsDisciplinas[i] == -1)
                {
                    cout << "ERRO! Disciplina " << i+1 << " já cadastrada -> status [" << idsDisciplinas[i] << "]" << endl;
                    continue;
                }
                cout << "Disciplina " << i+1 << " adicionada no indice [" << idsDisciplinas[i] << "]" << endl;
            }

            cout << endl;
            disciplinasTemporarias.clear();
            idsDisciplinas.clear();
        }

        else if (opcaoMenu == "5")
        {
            cout << "Nome da disciplina: ";
            getline(cin, inputUsuario_1);

            idDisciplina = historico (inputUsuario_1);

            if (idDisciplina == -1)
            {
                cout << "A disciplina informada não está cadastrada no histórico -> status " << idDisciplina << endl << endl;
                continue;
            }

            disciplinaTemporaria = historico.getDisciplina (idDisciplina);
            idDisciplina = historico -= disciplinaTemporaria;
            cout << "Disciplina removida com sucesso!" << endl;
            cout << "Índice disciplina removida -> " << idDisciplina << endl << endl;
        }

        else if (opcaoMenu == "6")
        {
            cout << "Nome da disciplina: ";
            getline (cin, inputUsuario_1);

            idDisciplina = historico (inputUsuario_1);

            if (idDisciplina == -1)
            {
                cout << "A disciplina informada não foi encontrada -> status " << idDisciplina << endl << endl;
                continue;
            }

            cout << endl << "Indice da disciplina -> " << idDisciplina;
            cout << historico.getDisciplina (idDisciplina);
        }
        
        else if (opcaoMenu == "7")
        {
            cout << "Nome da disciplina: ";
            getline (cin, inputUsuario_1);

            for (;;)
            {
                cout << "Nova nota: ";
                getline (cin, inputUsuario_2);

                nota = StringToDouble(inputUsuario_2); // retorna -1 se conversão for inválida

                // Validando a entrada do usuário
                if (nota == -1)
                {
                    cout << "Nota inválida!" << endl;
                    continue;
                }

                if (nota > 10)
                {
                    cout << "Nota inválida! A nota deve ser menor que 10!" << endl;
                    continue;
                }

                break;
            }

            idDisciplina = historico(inputUsuario_1, nota);

            if (idDisciplina == -1)
            {
                cout << "A disciplina informada não foi encontrada -> status " << idDisciplina << endl << endl;
                continue;
            }

            cout << "Nota editada com sucesso!" << endl;
            cout << endl << "Indice da disciplina editada -> " << idDisciplina << endl << endl;
        }

        else if (opcaoMenu == "8")
        {
            nota = historico.calcularCRA();
            cout << "CRA: " << setprecision(2) << fixed << nota << endl << endl;   // CRA
        }

        else
        {
            cout << "Opcao invalida! Por favor, informe uma opcao valida do MENU!" << endl;
            continue;
        }

    } while (opcaoMenu != "0");

    // Salvando os dados do histórico no arquivo txt
    status = gravarDados ("dados_historico.txt", historico);

    if (status == 0)
    {
        cout << endl << "Dados gravados com sucesso!" << endl << endl;
        return 0;
    }
    else
    {
        cout << endl << "Erro ao gravar os dados!" << endl;
        return -1;
    }

    return 0;
}