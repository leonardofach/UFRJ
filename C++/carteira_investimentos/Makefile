##################################################################
# UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
#
# Autor: Leonardo Fachetti Jovêncio
# Curso: Engenharia eletrônia e de computação
#
# Disciplina: Linguagens de programação - 2023.2
# Professor: Miguel Elias Mitre Campista
#
# Data: 07/12/2023
# Arquivo: Mekefile
# Descrição: Arquivo referente ao makefile do programa.
##################################################################

# INFO DE COMANDOS:
#       make ou make all 		 -> gera o executável do programa
#       make run                 -> roda o programa
#       make clean               -> apaga todos os arquivos
##################################################################

all:
	pip install pandas
	pip install yfinance
	g++ acao.cpp funcoes_aux.cpp carteira.cpp main.cpp -o programa -I/usr/include/python3.8 -lpython3.8

run:
	./programa

clean:
	rm -f *.o programa