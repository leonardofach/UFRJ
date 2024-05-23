/*******************************************************
 * UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
 *
 * Autor: Leonardo Fachetti Jovêncio
 * Curso: Engenharia eletrônia e de computação
 *
 * Disciplina: Linguagens de programação - 2023.2
 * Professor: Miguel Elias Mitre Campista
 *
 * Data: 06/12/2023
 * Arquivo: main.h
 * Descrição: Implementação de um sistema de gerenciamento
 * de investimentos.
 *********************************************************/

#include <iostream>
#include <iomanip>
#include <ctime>
#include "carteira.h"
#include "funcoes_aux.h"


int main (void)
{
    int status, modo;
    Carteira minhaCarteira;
    string opcaoMenu, entrada;
    vector<string> listaAcoes;
    vector <Acao> dadosAcoes;
    time_t timer;
    struct tm *horarioLocal;

    string mensagemErro = ":( Erro no sistema!";
    string divisor (ESPACAMENTO, '-');

    // Pegando a data atual
    time(&timer);
    horarioLocal = localtime(&timer); // Converte a hora atual para a hora local

    int dia = horarioLocal->tm_mday;
    int mes = horarioLocal->tm_mon + 1;
    int ano = horarioLocal->tm_year + 1900;


    // Inicialização do sistema
    cout << endl << endl;
    cout << "Caregando dados do sistema ..." << endl;
    status = minhaCarteira.iniciarSistema (listaAcoes, dadosAcoes);
    modo = 1;   // modo = 1 significa que a base de dados das ações já foi construído

    if (status != SUCESSO)
    {
        cout << ":( Erro ao iniciar o sistema!" << endl;
        return status;
    }

    // Menu
    do 
    {
        cout << endl << endl;
        cout << "PRESSIONE A TECLA ENTER PARA EXIBIR O MENU: ";
        getline (cin, entrada);

        cout << divisor << endl;
        cout << setw (20) << "MENU" <<  endl;
        cout << divisor << endl;

        cout << "[0] - Encerrar o programa" << endl;
        cout << "[1] - Exibir carteira de investimentos" << endl;
        cout << "[2] - Comprar ações" << endl;
        cout << "[3] - Vender ações" << endl;
        cout << "[4] - Exibir dados do IPCA" << endl;
        cout << "[5] - Exibir dados do dólar" << endl;
        cout << "[6] - Realizar análise fundamentalista" << endl;

        cout << divisor << endl;

        cout << "Escolha uma opção do menu: ";
        getline (cin, opcaoMenu);

        if (opcaoMenu == "0")
        {
            cout << endl << endl;
            cout << "Programa encerrado com sucesso!" << endl << endl;
            break;   
        }

        else if (opcaoMenu == "1")
        {
            cout << minhaCarteira;
        }

        else if (opcaoMenu == "2")
        {
            // Loop de compra até que o usuário sair
            for (;;)
            {
                string idAcao, quantidade;
                int id, qtd;
                bool encerrarCompra;

                // Exibindo ações disponíveis na bolsa
                cout << endl << endl;
                cout << "Saldo da conta: R$" << setprecision (2) << fixed << minhaCarteira.getSaldo () << endl;
                cout << divisor << endl;
                cout << " ID" << setw(9);
                cout << "ACAO" << setw(25); 
                cout << "COTAÇÃO (R$)" << setw(25);
                cout << "VARIACAO DIA (%)" << endl;
                cout << divisor << endl;

                for (size_t i=0; i < dadosAcoes.size(); i++)
                {
                    // Formatando a impressão
                    if (i <= 9)
                        cout << "[0" << i << "]" << setw (10);
                    else
                        cout << "[" << i << "]" << setw (10);
                    
                    cout << dadosAcoes[i].getTicker() << setw(16);
                    cout << setprecision(2) << fixed << dadosAcoes[i].getValorAtual() << setw(22);
                    cout << setprecision(2) << fixed << dadosAcoes[i].getVariacao() << endl;
                }

                cout << divisor << endl;

                // Recebendo do usuário o ID da ação
                do
                {
                    cout << "ID ação: ";
                    getline (cin, idAcao);

                    // Validando o ID informado
                    id = StringToInt (idAcao);

                    if (id == -1 || id >= listaAcoes.size ())
                    {
                        cout << "ID inválido. Por favor, informe um ID válido!" << endl;
                        continue;
                    }

                    else
                        break;

                } while (true);
                
                // Recebendo do usuário a quantidade de ações a serem compradas
                do
                {
                    cout << "Quantidade: ";
                    getline (cin, quantidade);

                    qtd = StringToInt (quantidade);

                    if (qtd == -1 || qtd == 0)
                    {
                        cout << "Quantidade inválida. Por favor, informe um valor válido!" << endl;
                        continue;
                    }

                    else
                        break;
                        
                } while (true);
                
                // Realizando a compra da ação
                double cotacao = dadosAcoes[id].getValorAtual();

                dadosAcoes[id].setQuantidade (qtd);
                dadosAcoes[id].setValorCompra (cotacao);

                int statusCompra = minhaCarteira + dadosAcoes[id];

                // Avaliando se a compra foi realizada com sucesso
                if (statusCompra != 0)
                {
                    cout << endl;
                    cout << divisor << endl;
                    cout << "Saldo insuficiente!" << endl;
                    cout << divisor << endl;
                }

                else
                {
                    cout << endl;
                    cout << divisor << endl;
                    cout << "Compra realizada com sucesso!" << endl << endl;
                    cout << "RESUMO DA COMPRA: " << endl;
                    cout << divisor << endl;
                    cout << "AÇÃO: " << listaAcoes[id] << " | ";
                    cout << "QTD: " << qtd << " | ";
                    cout << "COTAÇÃO: R$" << setprecision(2) << fixed << cotacao << " | ";
                    cout << "VALOR INVESTIDO: R$ " << setprecision(2) << fixed << qtd * cotacao << endl;
                    cout << divisor << endl;
                }

                // Solicitando ao usuário se ele deseja continuar comprando
                cout << endl << "Deseja continuar comprando?" << endl;
                cout << "[0] - sim" << endl;
                cout << "[1] - não" << endl << endl;

                do
                {
                    string opcao;

                    cout << "Opção: ";
                    getline (cin, opcao);

                    // Validando a opção informada
                    if (opcao == "0")
                    {
                        encerrarCompra = false;
                        break;
                    }

                    else if (opcao == "1")
                    {
                        encerrarCompra = true;
                        break;
                    }

                    else
                    {
                        cout << "Opção inválida! Tente novamente!" << endl;
                        continue;
                    }

                } while (true);

                if (encerrarCompra == true)
                    break;  // encerra o loop e volta ao menu principal
            }                   
        } 

        else if (opcaoMenu == "3")
        {
            // Loop de venda até que o usuário sair
            for (;;)
            {
                bool encerrarVenda;
                int id, quantidade;
                Acao acaoVendida;

                cout << minhaCarteira;

                // Solicitando o id da ação a ser vendida
                do
                {
                    string idAcao;
                    
                    cout << "Id ação: ";
                    getline (cin, idAcao);

                    id = StringToInt (idAcao);

                    // Validando o id informado
                    if (id == -1 || id >= minhaCarteira.totalAcoesCarteira ())
                    {
                        cout << "O id informado é inválido!" << endl;
                        continue;
                    }

                    else
                    {
                        acaoVendida = minhaCarteira.getAcao (id);
                        break;
                    }
                    
                } while (true);

                // Solicitando a quantidade da ação a ser vendida
                do
                {
                    string qtd;
                     
                    cout << "Quantidade: ";
                    getline (cin, qtd);

                    quantidade = StringToInt (qtd);

                    // Validando a quantidade informada
                    if (quantidade == -1 || quantidade == 0 || quantidade > acaoVendida.getQuantidade ())
                    {
                        cout << "A quantidade informada é inválida!" << endl;
                        continue;
                    }

                    else
                        break;
                    
                } while (true);

                // Realizando a venda da ação
                acaoVendida.setQuantidade (quantidade);
                double cotacao = acaoVendida.getValorAtual();
                
                minhaCarteira - acaoVendida;
        
                cout << endl;
                cout << divisor << endl;
                cout << "Venda realizada com sucesso!" << endl << endl;
                cout << "RESUMO DA VENDA: " << endl;
                cout << divisor << endl;
                cout << "AÇÃO: " << acaoVendida.getTicker() << " | ";
                cout << "QTD: " << quantidade << " | ";
                cout << "COTAÇÃO: R$" << setprecision(2) << fixed << cotacao << " | ";
                cout << "VALOR RECEBIDO: R$ " << setprecision(2) << fixed << quantidade * cotacao << endl;
                cout << divisor << endl;

                // Solicitando ao usuário se ele deseja continuar vendendo
                cout << endl << "Deseja continuar vendendo?" << endl;
                cout << "[0] - sim" << endl;
                cout << "[1] - não" << endl << endl;

                do
                {
                    string opcao;

                    cout << "Opção: ";
                    getline (cin, opcao);

                    // Validando a opção informada
                    if (opcao == "0")
                    {
                        encerrarVenda = false;
                        break;
                    }

                    else if (opcao == "1")
                    {
                        encerrarVenda = true;
                        break;
                    }

                    else
                    {
                        cout << "Opção inválida! Tente novamente!" << endl;
                        continue;
                    }

                } while (true);

                if (encerrarVenda == true)
                    break;  // encerra o loop e volta ao menu principal
            }
        } 

        else if (opcaoMenu == "4")
        {
            minhaCarteira.exibirIPCA (dia, mes, ano);
        } 

        else if (opcaoMenu == "5")
        {
            minhaCarteira.exibirDolar ();
        }  

        else if (opcaoMenu == "6")
        {
            // Loop até que o usuário sair
            for (;;)
            {
                bool encerrar;
                string idEmpresa;
                int id;

                cout << endl;
                cout << divisor << endl;
                cout << "LISTA DE EMPRESAS DA BOLSA" << endl;
                cout << divisor << endl;

                for (size_t i=0; i < listaAcoes.size (); i++)
                {
                    if (i <= 9)
                        cout << "[0" << i << "] - " << listaAcoes[i] << endl;
                    else
                        cout << "[" << i << "] - " << listaAcoes[i] << endl;
                }
                
                cout << divisor << endl << endl;

                // Recebendo do usuário o ID da empresa
                do
                {
                    cout << "ID empresa: ";
                    getline (cin, idEmpresa);

                    // Validando o ID informado
                    id = StringToInt (idEmpresa);

                    if (id == -1 || id >= listaAcoes.size ())
                    {
                        cout << "ID inválido. Por favor, informe um ID válido!" << endl;
                        continue;
                    }

                    else
                        break;

                } while (true);

                int status = minhaCarteira.analiseFundamentalista (listaAcoes[id]);

                if (status != SUCESSO)
                {
                    cout << mensagemErro << endl;
                    return ERRO_DADOS_EMPRESA;
                }

                // Solicitando ao usuário se ele deseja continuar avaliando as empresas
                cout << endl << "Deseja avaliar outra empresa?" << endl;
                cout << "[0] - sim" << endl;
                cout << "[1] - não" << endl << endl;

                do
                {
                    string opcao;

                    cout << "Opção: ";
                    getline (cin, opcao);

                    // Validando a opção informada
                    if (opcao == "0")
                    {
                        encerrar = false;
                        break;
                    }

                    else if (opcao == "1")
                    {
                        encerrar = true;
                        break;
                    }

                    else
                    {
                        cout << "Opção inválida! Tente novamente!" << endl;
                        continue;
                    }

                } while (true);

                if (encerrar == true)
                    break;  // encerra o loop e volta ao menu principal
            }
        } 

    } while (true);

    return 0;
}