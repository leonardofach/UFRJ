# *******************************************************
# UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
#
# Autor: Leonardo Fachetti Jovêncio
# Curso: Engenharia eletrônia e de computação
#
# Disciplina: Linguagens de programação - 2023.2
# Professor: Miguel Elias Mitre Campista
#
# Data: 06/12/2023
# Arquivo: funcoes_externas.py
# Descrição: Implementação das funções auxiliares.
# ***********************************************************

# g++ teste.cpp -o teste -I/usr/include/python3.8 -lpython3.8

import pandas as pd
import yfinance as yf


def DadosCotacoes (acao): 
    # Recebe o ticker de uma ação e retorna seu preco de abertura no dia e
    # sua cotação mais atualizada.

    db = yf.download(tickers=acao, period="1d", interval="1m", progress=False)

    abertura = round (list(db.iloc[0])[0], 2)
    atual = round (list(db.iloc[-1])[4], 2)

    dados = (abertura, atual)

    return dados


def DadosEmpresa (empresa):
    # Recebe o ticker de uma empresa como argumento e retorna diversas informações 
    # sobre ela, como seus índices financeiros e outras métricas importantes.

    db = yf.Ticker(empresa).info

    metricas = (db["profitMargins"],
                db["operatingMargins"],
                db["ebitdaMargins"],
                db["grossMargins"],
                db["revenueGrowth"],
                db["returnOnAssets"],
                db["revenuePerShare"])
    
    return metricas


def DadosDolar (ticker):
    # Retorna o valor atual do dólar.

    db = yf.download (tickers=ticker, interval="1m", progress=False)

    dados = round (list(db.iloc[-1])[4], 2)

    return dados


def DadosIPCA (dia, mes, ano):
    # Retorna o valor do IPCA atual e no acumulado do ano vigente.
    # A função retorna uma tupla na forma (atual, acumulado)

    url = "http://api.bcb.gov.br/dados/serie/bcdata.sgs.{}/dados?formato=json".format(433)
    df = pd.read_json(url)
    df["data"] = pd.to_datetime(df["data"], dayfirst=True)
    df.set_index("data", inplace=True)

    db = df.loc[f"{ano}-01-01" : f"{ano}-{mes}-{dia}"]  # df.loc[inicio : fim] -> período

    # Valor IPCA atual
    atual = round (float(db.iloc[-1]), 2)

    # Valor IPCA acumulado no ano
    mensal = list(db["valor"])
    acumulado = 0
    for m in range(0, len(mensal)):
        acumulado += float(mensal[m])

    dados = (atual, round (acumulado, 2))
    
    return dados