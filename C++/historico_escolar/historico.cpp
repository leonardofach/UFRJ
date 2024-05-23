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
 * Arquivo: disciplina.cpp
 * Descrição: Implementação da classe Historico.
 *********************************************************/

#include "historico.h"
#include "funcoes_auxiliares.h"


ostream &operator<< (ostream &output, const Historico &infoHistorico)
{
    // Permite realizarmos cout << objeto da classe Historico

    short int id = 0;

    cout << endl << "-----------------------------------------------------------------------------" << endl;
    cout << " ID   " << "PERÍODO" << "      " << "NOTA" << "     " << "CRÉDITOS" << "     " << "DISCIPLINA" << endl;
    cout << "-----------------------------------------------------------------------------" << endl;

    for (Disciplina d : infoHistorico.disciplinas)
    {
        if (id < 10) // para uma formatação correta de impressão na tela
        {
            output << " " << id << setw (10) // espaçamento extra no id
                   << d.periodo << setw (10)
                   << d.notaFinal << setw (10)
                   << d.creditos << "         " 
                   << d.nome << endl;
        }
        else
        {
            output << id << setw (10)
                   << d.periodo << setw (10)
                   << d.notaFinal << setw (10)
                   << d.creditos << "         " 
                   << d.nome << endl;
        }
        id++;
    }
    cout << "-----------------------------------------------------------------------------" << endl << endl;

    return output;
}

short int carregarDados (string fileName, Historico &infoHistorico)
{
    // Carrega a base de dados do histórico

    string linha;
    vector<string> dados;
    fstream file;
    vector <string> stringDividida;
    string pedacoString;
    Disciplina disciplinaTemporaria;

    file.open(fileName.c_str(), fstream::in | fstream::out | fstream::app);

    //  Lendo o arquivo de texto
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline(file, linha);
            
            if (linha.size () == 0) // atingiu a última linha (última linha possui um caractere "\n")
                break;

            dados.push_back(linha);
        }

        file.close();
    }
    else
        return -1;
    
    // Salvando os dados no histórico
    for (string db : dados)
    {
        stringstream stringStream(db); // construindo uma stream a partir da string

        while (getline(stringStream, pedacoString, ';'))
            stringDividida.push_back(pedacoString);
        
        disciplinaTemporaria.periodo = stringDividida[0];
        disciplinaTemporaria.nome = stringDividida[1];
        disciplinaTemporaria.creditos = StringToInt (stringDividida[2]);
        disciplinaTemporaria.notaFinal = StringToDouble (stringDividida[3]);

        infoHistorico.disciplinas.push_back (disciplinaTemporaria);
        limparDisciplina (disciplinaTemporaria);
        stringDividida.clear ();
    }

    return 0;       
}

short int gravarDados (string fileName, const Historico &infoHistorico)
{
    // Grava todas as alterações realizadas no histórico na base de dados

    ofstream file;

    file.open(fileName.c_str());

    if (file.is_open())
        for (Disciplina d : infoHistorico.disciplinas)
            file << d.periodo << ";" << d.nome << ";" << d.creditos << ";" << d.notaFinal << "\n";
    else
        return -1;

    return 0;
}

Disciplina Historico::getDisciplina (short int idDisciplina)
{
    // Retorna a disciplina do histórico na posição idDisciplina
    return disciplinas[idDisciplina];
}

short int Historico::getNumeroDisciplinas (void)
{
    // Retorna o número de disciplinas cadastradas no histórico
    return disciplinas.size ();
}

short int Historico::getMaximoDisciplinas (void)
{
    // Retorna o número máximo de discplinas permitidas a serem cadastradas no histórico
    return maximoDisciplinas;
}

bool operator== (const Disciplina &disciplina1, const Disciplina &disciplina2)
{
    // Permite realizarmos disciplina1 == disciplina2  ->  compara os nomes das disciplinas
      
    if (disciplina1.nome == disciplina2.nome)
        return true;
    else
        return false;
}

bool operator< (const Disciplina &disciplina1, const Disciplina &disciplina2)
{
    // Permite realizarmos disciplina1 < disciplina2  ->  comparando seus períodos

    if (disciplina1.periodo < disciplina2.periodo)
        return true;
    else
        return false;
}

short int Historico::operator+= (Disciplina &novaDisciplina)
{
    // Permite realizarmos historico += disciplina
    // adiciona UMA nova disciplina no histórico de forma ordenada

    // caso em que o histórico ainda não possui disciplinas adicionadas
    if (disciplinas.size() == 0)
    {
        disciplinas.push_back (novaDisciplina);
        return 0;  // primeira posição
    }
    
    // verificando se o nome da nova disciplina é igual a outra já inserida no histórico
    for (size_t i = 0; i < disciplinas.size(); i++)
    {
        if (novaDisciplina == disciplinas[i])  // comparando os nomes usando o operador sobrecarregado ==
            return -1;
    }

    // inserindo a nova disciplina numa posição ordenada por período e nome, nesse ordem de prioridade
    for (size_t i = 0; i < disciplinas.size(); i++) 
    {
        // caso período menor
        if ((novaDisciplina < disciplinas[i]) == true)  // comparando os períodos usando o operador sobrecarregado <
        {
            disciplinas.insert (disciplinas.begin() + i, novaDisciplina);
            return i;
        }
        else
        {
            // caso períodos iguais
            if (novaDisciplina.periodo == disciplinas[i].periodo)
            {
                // se nome novaDisciplina for menor na ordem alfábética
                if (novaDisciplina.nome < disciplinas[i].nome)
                {
                    disciplinas.insert (disciplinas.begin() + i, novaDisciplina);
                    return i;
                }
                // se nome novaDisciplina for maior na ordem alfábética
                else
                {
                    if ((i+1) == disciplinas.size()) // caso seja a última disciplina
                    {
                        disciplinas.push_back (novaDisciplina); // adicionamos novaDisciplina no final
                        return i+1;
                    }
                    else
                        continue;
                }
            }
            // caso período maior
            if ((novaDisciplina < disciplinas[i]) == false) // comparando os períodos usando o operador sobrecarregado <
            {
                if ((i+1) == disciplinas.size()) // caso seja a última disciplina
                {
                        disciplinas.push_back (novaDisciplina); // adicionamos novaDisciplina no final
                        return i+1;
                }
                else
                    continue; // próxima disciplina
            }
        }
    }
    return -1;
}

vector<short int> Historico::operator+= (vector<Disciplina> &novasDisciplinas)
{
    // Permite realizarmos historico += disciplina
    // adiciona VÁRIAS novas disciplinas no histórico de forma ordenada

    size_t size = novasDisciplinas.size();
    vector<short int> retorno (size);  // guarda a posição em que novaDisciplina foi salvo no histórico / -1 se já cadastrada


    // verificando se o nome da nova disciplina é igual a outra já inserida no histórico
    for (size_t i = 0; i < novasDisciplinas.size(); i++)
    {
        retorno[i] = 0; // inicia em 0 -> indicando que novaDisciplina não está cadastrada no histórico

        for (size_t j = 0; j < disciplinas.size(); j++)
        {   
            if (novasDisciplinas[i] == disciplinas[j])  // comparando os nomes usando o operador sobrecarregado ==
            {
                retorno[i] = -1;
                break;
            }   
        }
    }

    // Caso em que não existe nenhuma disciplina cadastrada ainda

    // Cadastrando cada uma das novas disciplinas de forma ordenada por período e nome, nessa ordem de prioridade
    for (size_t i = 0; i < retorno.size (); i++)
    {
        // caso disciplina já cadastrada
        if (retorno[i] == -1)
            continue;

        for (size_t j = 0; j < disciplinas.size (); j++)
        {
            // caso período menor
            if ((novasDisciplinas[i] < disciplinas[j]) == true)   // comparando os períodos usando o operador sobrecarregado <
            {    
                disciplinas.insert (disciplinas.begin() + j, novasDisciplinas[i]);
                break;
            }
            else
            {
                // caso período igual
                if(novasDisciplinas[i].periodo == disciplinas[j].periodo)
                {
                    // se nome novaDisciplina for menor na ordem alfábética
                    if (novasDisciplinas[i].nome < disciplinas[j].nome)
                    {
                        disciplinas.insert (disciplinas.begin() + j, novasDisciplinas[i]);
                        break;
                    }
                    // se nome novaDisciplina for maior na ordem alfábética
                    else
                    {
                        if ((j+1) == disciplinas.size()) // caso seja a última disciplina do cadastro
                        {
                            disciplinas.push_back (novasDisciplinas[i]); // adicionamos novaDisciplina no final
                            break;
                        }
                        else
                            continue;   // próxima disciplina
                    }
                }
                // caso período maior
                if ((novasDisciplinas[i] < disciplinas[i]) == false) // comparando os períodos usando o operador sobrecarregado <
                {
                    if ((j+1) == disciplinas.size()) // caso seja a última disciplina
                    {
                            disciplinas.push_back (novasDisciplinas[i]); // adicionamos novaDisciplina no final
                            break;
                    }
                    else
                        continue; // próxima disciplina
                }
            }
        }
    }

    // Atribuindo os índices nas quais as novasDisciplinas foram cadastradas no vector de disciplinas do histórico
    for (size_t i = 0; i < retorno.size(); i++)
    {
        if (retorno[i] == -1)  // já cadastrada
            continue;
        
        for(size_t j = 0; j < disciplinas.size(); j++)
            if (novasDisciplinas[i] == disciplinas[j])  //  // comparando os nomes usando o operador sobrecarregado ==
                retorno[i] = j;
    }

    return retorno;
}

short int Historico::operator-= (Disciplina &disciplina)
{
    // Permite realizarmos historico -= disciplina  -->  remove uma disciplina do histórico 

    for (size_t i = 0; i < disciplinas.size (); i++) // varrendo todas as disciplinas do histórico
    {
        if (disciplina == disciplinas[i])    // comparando os nomes usando o operador sobrecarregado ==
        {
            disciplinas.erase (disciplinas.begin () + i);
            return i;
        }
    }

    return -1; // não encontrou a disciplina informada no histórico
}

short int Historico::operator() (string nomeDisciplina)
{
    // Permite realizarmos histórico (nomeDisciplina) --> retorna a posição em que a disciplina informada está cadastrada no histórico

    for (size_t i = 0; i < disciplinas.size (); i++) // varrendo todas as disciplinas do histórico
        if (nomeDisciplina == disciplinas[i].nome)
            return i;

    return -1; // não encontrou a disciplina informada no histórico
}

short int Historico::operator() (string nomeDisciplina, double novaNota)
{
    // Permite realizarmos historico (nomeDisciplina, novaNota)  ->  edita a nota da disciplina informada

    for (size_t i = 0; i < disciplinas.size (); i++) // varrendo todas as disciplinas do histórico
        if (nomeDisciplina == disciplinas[i].nome)
        {
            disciplinas[i].notaFinal = novaNota;
            return i;
        }

    return -1; // não encontrou a disciplina informada no histórico
}

double Historico::calcularCRA (void)
{
    // Calcula o CRA
    double somaNotasPonderas = 0;
    double somaPesos = 0;
    
    for (Disciplina d : disciplinas)
    {
        somaNotasPonderas += d.notaFinal * d.creditos;
        somaPesos += d.creditos;
    }

    return (somaNotasPonderas/somaPesos);
}