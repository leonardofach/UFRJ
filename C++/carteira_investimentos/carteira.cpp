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
 * Arquivo: carteira.cpp
 * Descrição: Implementação dos métodos da classe Carteira.
 *********************************************************/


#include <iomanip>
#include <iostream>
#include <fstream>
#include <Python.h>
#include "carteira.h"
#include "funcoes_aux.h"

#define PY_SSIZE_T_CLEAN


Carteira::Carteira (string nomeUsuario, float saldoInicial)
{
    usuario = nomeUsuario;
    saldo = saldoInicial;
}

ostream &operator<< (ostream &output, Carteira &minhaCarteira)
{
    string divisor (ESPACAMENTO, '-');

    minhaCarteira.computarInvestimento ();
    
    output << endl << endl;
    output << divisor << endl;
    output << "Meu patrimônio: R$ " << setprecision (2) << fixed << minhaCarteira.saldo + minhaCarteira.investimentos << endl;
    output << "Meus investimentos: R$ " << setprecision (2) << fixed << minhaCarteira.investimentos << endl;
    output << "Saldo da conta: R$ " << setprecision (2) << fixed << minhaCarteira.saldo << endl << endl;
    output << "Rentabilidade: " << setprecision (2) << fixed << minhaCarteira.rentabilidade << " %" << endl << endl;

    output << minhaCarteira.acoesUsuario;

    return output;
}

int Carteira::iniciarSistema (vector<string> &listaAcoes, vector<Acao> &dadosAcoes)
{   
    int status;

    // Carregando a lista de ações a serem disponibilizadas pelo sistema
    status = CarregarListaAcoes (listaAcoes);

    if (status != 0)
        return ERRO_CARREGAR_LISTA_ACOES;

    // Construindo da base de dados da ações a serem disponibilizadas
    status = atualizarCotacoes (listaAcoes, dadosAcoes, 0);

    if (status != 0)
        return ERRO_ATUALIZAR_COTACOES;

    // Carregando os dados do usuário
    status = CarregarDadosUsuario (listaAcoes, dadosAcoes);

    if (status != 0)
        return ERRO_CARREGAR_DADOS_USUARIO;

    // Computando o valor investido e a rentabilidade da carteira do usuário
    computarInvestimento ();

    return SUCESSO;
}

int Carteira::atualizarCotacoes (vector<string> &listaAcoes, vector<Acao> &dadosAcoes, int modo)
{
    for (size_t i=0; i < listaAcoes.size(); i++)
    {
        int status;
        double abertura, cotacao, variacao;

        status = dbCotacoes (listaAcoes[i], abertura, cotacao);

        variacao = 100 * ((cotacao - abertura) / abertura);

        // Caso o processo não seja realizado com sucesso
        if (status != SUCESSO)
            return ERRO_ATUALIZAR_COTACOES;

        else
        {
            // Caso seja a primeira cotação na execução do sistema  ->  modo = 0
            // A primeira cotação é realizada na inicialização do sistema
            // Nesse caso, o vector dadosAcoes estará vazio
            if (modo == 0)
            {
                Acao acao (listaAcoes[i], abertura, cotacao, 0, 0, variacao);
                dadosAcoes.push_back (acao);
            }

            // Nesse caso, o sistema já realizou uma atualização da cotação  -> modo = 1
            // Nesse caso, o vector dadosAcoes não estará vazio
            else
            {
                // Atualizamos apenas a cotação e variação
                dadosAcoes[i].setValorAtual (cotacao);
                dadosAcoes[i].setVariacao (variacao);
            }
        }
    }
    return SUCESSO;
}

void Carteira::computarInvestimento (void)
{
    investimentos = 0;
    rentabilidade = 0;
    double totalInvestido = 0;

    for (size_t i=0; i < acoesUsuario.size(); i++)
    {
        investimentos += acoesUsuario[i].getValorAtual() * acoesUsuario[i].getQuantidade();
        totalInvestido += acoesUsuario[i].getValorCompra() * acoesUsuario[i].getQuantidade();
    }

    rentabilidade = 100 * ((investimentos - totalInvestido) / totalInvestido);
}

double Carteira::getSaldo (void)
{
    return saldo;
}

Acao Carteira::getAcao (int idAcao)
{
    return acoesUsuario[idAcao];
}

int Carteira::totalAcoesCarteira (void)
{
    return acoesUsuario.size ();
}

int Carteira::operator+ (Acao &novaAcao)
{
    double total = novaAcao.getValorAtual() * novaAcao.getQuantidade();

    // Avaliando se o usuário possui saldo suficiente na conta
    if (total > saldo)
        return -1;

    else
    {
        // Adicionando a ação comprada na carteira
        acoesUsuario.push_back (novaAcao);

        saldo -= total;
        investimentos += total;
        return SUCESSO;
    }
}

void Carteira::operator- (Acao &acao)
{
    double total = acao.getQuantidade() * acao.getValorAtual ();    
    
    saldo += total;
    investimentos -= total;

    // Procurando a ação a ser vendida na carteira de ações do usuário
    size_t pos = 0;

    for (size_t i=0; i < acoesUsuario.size(); i++)
    {
        if (acoesUsuario[i].getTicker().compare (acao.getTicker()) == 0)
            pos = i;
    }

    // Caso for vendido todas as ações
    if (acao.getQuantidade() == acoesUsuario[pos].getQuantidade())
        acoesUsuario.erase (acoesUsuario.begin() + pos);    // removendo a ação da carteira

    else
        acoesUsuario[pos].setQuantidade (acoesUsuario[pos].getQuantidade() - acao.getQuantidade());
}

int Carteira::analiseFundamentalista (string empresa)
{
    int espacamento = 15;
    string divisor (ESPACAMENTO, '-');

    // Carregando dados da empresa
    Empresa dadosEmpresa;
    int status = dbEmpresa (empresa, dadosEmpresa);

    if (status != SUCESSO)
        return ERRO_DADOS_EMPRESA;

    // Exibindo dados da empresa
    cout << endl << endl;
    cout << divisor << endl;
    cout << "INFO" << endl;
    cout << divisor << endl;
    cout << "Ação na bolsa: " << empresa << endl;
    cout << "Margem de lucro: " << dadosEmpresa.margemLucro << endl;
    cout << "Margem operacional: " << dadosEmpresa.margemOperacional << endl;
    cout << "Margem EBITDA: " << dadosEmpresa.margemEBITDA << endl;
    cout << "Margem bruta: " << dadosEmpresa.margemBruta << endl;
    cout << "Crescimento receita: " << dadosEmpresa.crescimentoReceita << endl;
    cout << "Retorno sobre ativos: " << dadosEmpresa.retornoSobreAtivos << endl;
    cout << "Receita por ação: " << dadosEmpresa.receitaPorAcao << endl;
    cout << divisor << endl << endl;

    return SUCESSO;
}

void Carteira::exibirIPCA (int dia, int mes, int ano)
{
    string divisor (ESPACAMENTO, '-');
    vector <string> valoresIPCA;
    float atual, acumulado;
    int status;

    status = dbIPCA (atual, acumulado, dia, mes, ano);

    if (status != 0)
    {
        cout << "Erro no sistema!" << endl;
    }

    else
    {
        cout << endl << endl;
        cout << divisor << endl;
        cout << "IPCA atual:   " << atual << " %" << endl;
        cout << "IPCA em " << ano << ": " << acumulado << " %" << endl;
        cout << divisor << endl;
    }
}

void Carteira::exibirDolar (void)
{
    string divisor (ESPACAMENTO, '-'); 
    double valor;
    int status;

    status = dbDolar (valor);

    if (status != 0)
    {
        cout << "Erro no sistema!" << endl;
    }

    else
    {
        cout << endl << endl;
        cout << divisor << endl;
        cout << "Cotação: R$ " << valor << endl; 
        cout << divisor << endl << endl;
    }
}

int Carteira::CarregarDadosUsuario (vector<string> listaAcoes, vector<Acao> &dadosAcoes)
{
    ifstream file;
    vector<string> linhas;

    // Lendo o arquivo txt com os dados do usuario
    file.open(DADOS_USUARIO);

    if (file.is_open())
    {
        while (!file.eof())
        {
            string linha;
            getline (file, linha);
            linhas.push_back (linha);         
        }
        file.close();
    }

    else
        return ERRO_CARREGAR_DADOS_USUARIO;

    // Salvando os dados do usuario
    for (size_t i=0; i < linhas.size(); i++)
    {
        string linhaDividida;
        vector<string> dados;

        // Caso em que consta apenas labels no arquivo txt
        if (i == 0 || i == 2)
            continue;

        // pega uma linha de dados e divide no caractere informado
        stringstream stringStream(linhas[i]);
        while (getline(stringStream, linhaDividida, ';'))
            dados.push_back(linhaDividida);
        
        // Caso em que consta informações sobre o nome e o saldo da conta do usuario
        if (i == 1)
        {
            usuario = dados[0];
            saldo = StringToDouble (dados[1]);
        }
        // Caso em que consta informações sobre as ações compradas pelo usuário
        else
        {
            int id = StringToInt (dados[0]);
            int quantidade = StringToInt (dados[1]);
            double valorCompra = StringToDouble (dados[2]);

            double cotacao = dadosAcoes[id].getValorAtual ();
            float variacao = 100 * ((cotacao - valorCompra) / valorCompra);

            // Adicionando as ações na carteira do usuário
            Acao acao (listaAcoes[id], 0, cotacao, quantidade, valorCompra, variacao);
            acoesUsuario.push_back (acao);
        }
    }

    return SUCESSO;
}

int Carteira::CarregarListaAcoes (vector<string> &listaAcoes)
{
    ifstream file;
    vector<string> linhas;

    // Lendo o arquivo txt com a lista de ações a serem disponibilizadas pelo sistema
    file.open(DADOS_ACOES);

    if (file.is_open())
    {
        while (!file.eof())
        {
            string linha;
            getline (file, linha);
            listaAcoes.push_back (linha);         
        }
        file.close();
    }

    else
        return ERRO_CARREGAR_LISTA_ACOES;

    return SUCESSO;
}

int Carteira::dbCotacoes (string acao, double &abertura, double &cotacao)
{
    PyObject *file, *function, *args, *resul;

    // Obtendo o diretório atual de trabalho
    char LOCAL_DIR[FILENAME_MAX];

    if (!Define_CurrentDir(LOCAL_DIR, sizeof(LOCAL_DIR)))
    {
        return errno;
    }

    // Inicializa o acesso ao intepretador python
    Py_Initialize();

    // Localiza o endereço atual de trabalho
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString(LOCAL_DIR));

    // Importa o codigo escrito em python
    file = PyImport_ImportModule("funcoes_externas");

    if (file)
    {
        // Acessa a função externa em python descrita no segundo argumento
        function = PyObject_GetAttrString(file, "DadosCotacoes");

        // Avalia se a função python informada pode ser chamada
        if (function && PyCallable_Check(function))
        {
            // Cria uma tupla para guardar os argumentos da função
            args = PyTuple_New(1);

            char *pontAcao;
            pontAcao = &acao[0];
            PyTuple_SetItem(args, 0, PyUnicode_FromString (pontAcao));

            // Executa a função python informada e guarda seu retorno em resul
            resul = PyObject_CallObject(function, args);
            Py_DECREF(args);
            Py_DECREF(function);
            Py_DECREF(file);

            // Avalia o valor de retorno
            if (resul)
            {
                // Converte o resultado recebido para um tipo c++ válido            
                abertura = PyFloat_AsDouble (PyTuple_GetItem (resul, 0));
                cotacao = PyFloat_AsDouble (PyTuple_GetItem (resul, 1));
                return SUCESSO;
            }
            // Caso erro no valor retornado
            else
            {
                Py_Finalize();
                return ERRO_ATUALIZAR_COTACOES;
            }
        }
        // Caso não seja possível execultar a função python informada
        else
        {
            Py_Finalize();
            return ERRO_ATUALIZAR_COTACOES;
        }
    }
    // Caso não seja possível acessar o arquivo .py informado
    else
    {
        Py_Finalize();
        return ERRO_ATUALIZAR_COTACOES;
    }

    Py_Finalize();
    return SUCESSO;
}

int Carteira::dbIPCA (float &atual, float &acumulado, int dia, int mes, int ano)
{
    PyObject *file, *function, *args, *resul;

    // Obtendo o diretório atual de trabalho
    char LOCAL_DIR[FILENAME_MAX];

    if (!Define_CurrentDir(LOCAL_DIR, sizeof(LOCAL_DIR)))
    {
        return errno;
    }

    // Inicializa o acesso ao intepretador python
    Py_Initialize();

    // Localiza o endereço atual de trabalho
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString(LOCAL_DIR));

    // Importa o codigo escrito em python
    file = PyImport_ImportModule("funcoes_externas");

    if (file)
    {
        // Acessa a função externa em python descrita no segundo argumento
        function = PyObject_GetAttrString(file, "DadosIPCA");

        // Avalia se os atributos da função python informada pode ser chamado com sucesso
        if (function && PyCallable_Check(function))
        {
            // Cria uma tupla para guardar os argumentos da função
            args = PyTuple_New(3);
            PyTuple_SetItem(args, 0, PyLong_FromLong(dia));
            PyTuple_SetItem(args, 1, PyLong_FromLong(mes));
            PyTuple_SetItem(args, 2, PyLong_FromLong(ano));

            // Executa a função python informada e guarda seu retorno em resul
            resul = PyObject_CallObject(function, args);
            Py_DECREF(args);
            Py_DECREF(function);
            Py_DECREF(file);

            // Avalia o valor de retorno
            if (resul)
            {
                // Converte o resultado recebido para um tipo c++ válido            
                atual = PyFloat_AsDouble (PyTuple_GetItem (resul, 0));
                acumulado = PyFloat_AsDouble (PyTuple_GetItem (resul, 1));
                return SUCESSO;
            }
            // Caso erro no valor retornado
            else
            {
                Py_Finalize();
                return ERRO_COTACAO_IPCA;
            }
        }
        // Caso não seja possível execultar a função python informada
        else
        {
            Py_Finalize();
            return ERRO_COTACAO_IPCA;
        }
    }
    // Caso não seja possível acessar o arquivo .py informado
    else
    {
        Py_Finalize();
        return ERRO_COTACAO_IPCA;
    }

    Py_Finalize();
    return SUCESSO;
}

int Carteira::dbDolar (double &atual)
{
    PyObject *file, *args, *function, *resul;

    // Obtendo o diretório atual de trabalho
    char LOCAL_DIR[FILENAME_MAX];

    if (!Define_CurrentDir(LOCAL_DIR, sizeof(LOCAL_DIR)))
    {
        return errno;
    }

    // Inicializa o acesso ao intepretador python
    Py_Initialize();

    // Localiza o endereço atual de trabalho
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString(LOCAL_DIR));

    // Importa o codigo escrito em python
    file = PyImport_ImportModule("funcoes_externas");

    if (file)
    {
        // Acessa a função externa em python descrita no segundo argumento
        function = PyObject_GetAttrString(file, "DadosDolar");

        // Avalia se os atributos da função python informada pode ser chamado com sucesso
        if (function && PyCallable_Check(function))
        {
            // Cria uma tupla para guardar os argumentos da função
            args = PyTuple_New(1);

            string tickerDolar = "BRL=X";
            char *pont;
            pont = &tickerDolar[0];
            PyTuple_SetItem(args, 0, PyUnicode_FromString (pont));

            // Executa a função python informada e guarda seu retorno em resul
            resul = PyObject_CallObject(function, args);
            Py_DECREF(function);
            Py_DECREF(file);

            // Avalia o valor de retorno
            if (resul)
            {
                // Converte o resultado recebido para um tipo c++ válido
                atual = PyFloat_AsDouble (resul); 
                return SUCESSO;
            }
            // Caso erro no valor retornado
            else
            {
                Py_Finalize();
                return ERRO_COTACAO_DOLAR;
            }
        }
        // Caso não seja possível execultar a função python informada
        else
        {
            Py_Finalize();
            return ERRO_COTACAO_DOLAR;
        }
    }
    // Caso não seja possível acessar o arquivo .py informado
    else
    {
        Py_Finalize();
        return ERRO_COTACAO_DOLAR;
    }

    Py_Finalize();
    return SUCESSO;
}

int Carteira::dbEmpresa (string empresa, Empresa &dadosEmpresa)
{
    PyObject *file, *args, *function, *resul;

    // Obtendo o diretório atual de trabalho
    char LOCAL_DIR[FILENAME_MAX];

    if (!Define_CurrentDir(LOCAL_DIR, sizeof(LOCAL_DIR)))
    {
        return errno;
    }

    // Inicializa o acesso ao intepretador python
    Py_Initialize();

    // Localiza o endereço atual de trabalho
    PyObject *sys_path = PySys_GetObject("path");
    PyList_Append(sys_path, PyUnicode_FromString(LOCAL_DIR));

    // Importa o codigo escrito em python
    file = PyImport_ImportModule("funcoes_externas");

    if (file)
    {
        // Acessa a função externa em python descrita no segundo argumento
        function = PyObject_GetAttrString(file, "DadosEmpresa");

        // Avalia se os atributos da função python informada pode ser chamado com sucesso
        if (function && PyCallable_Check(function))
        {
            // Cria uma tupla para guardar os argumentos da função
            args = PyTuple_New(1);

            char *pontEmp;
            pontEmp = &empresa[0];
            PyTuple_SetItem(args, 0, PyUnicode_FromString (pontEmp));

            // Executa a função python informada e guarda seu retorno em resul
            resul = PyObject_CallObject(function, args);
            Py_DECREF(function);
            Py_DECREF(file);

            // Avalia o valor de retorno
            if (resul)
            {
                // Converte o resultado recebido para um tipo c++ válido
                dadosEmpresa.margemLucro =  PyFloat_AsDouble (PyTuple_GetItem (resul, 0));
                dadosEmpresa.margemOperacional = PyFloat_AsDouble (PyTuple_GetItem (resul, 1));
                dadosEmpresa.margemEBITDA = PyFloat_AsDouble (PyTuple_GetItem (resul, 2));
                dadosEmpresa.margemBruta = PyFloat_AsDouble (PyTuple_GetItem (resul, 3));
                dadosEmpresa.crescimentoReceita = PyFloat_AsDouble (PyTuple_GetItem (resul, 4));
                dadosEmpresa.retornoSobreAtivos = PyFloat_AsDouble (PyTuple_GetItem (resul, 5)); 
                dadosEmpresa.receitaPorAcao = PyFloat_AsDouble (PyTuple_GetItem (resul, 6)); 

                return SUCESSO;
            }
            // Caso erro no valor retornado
            else
            {
                Py_Finalize();
                return ERRO_DADOS_EMPRESA;
            }
        }
        // Caso não seja possível execultar a função python informada
        else
        {
            Py_Finalize();
            return ERRO_DADOS_EMPRESA;
        }
    }
    // Caso não seja possível acessar o arquivo .py informado
    else
    {
        Py_Finalize();
        return ERRO_DADOS_EMPRESA;
    }

    Py_Finalize();
    return SUCESSO;
}