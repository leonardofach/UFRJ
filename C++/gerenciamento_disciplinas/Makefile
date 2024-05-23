##################################################################
# UNIVERSIDADE FEDERAL DO RIO DE JANEIRO
#
# Autor: Leonardo Fachetti Jovêncio
# Curso: Engenharia eletrônia e de computação
#
# Disciplina: Linguagens de programação - 2023.2
# Professor: Miguel Elias Mitre Campista
#
# Data: 03/12/2023
# Arquivo: Mekefile
# Descrição: Arquivo referente ao makefile do programa.
##################################################################

# INFO DE COMANDOS:
#       make ou make all         -> gera o executável do programa
#       make run                 -> roda o programa
#       make clean               -> apaga todos os arquivos
##################################################################

all:
	g++ -Wall -c aluno.cpp
	g++ -Wall -c disciplina.cpp
	g++ -Wall -c main.cpp
	g++ -Wall -o programa aluno.o disciplina.o main.o

run:
	./programa

link:
	g++ -Wall -o programa aluno.o disciplina.o main.o

clean:
	rm -f *.o programa
