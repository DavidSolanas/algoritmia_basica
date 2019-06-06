#*********************************************************
# Fichero Makefile
# Práctica 2 Algoritmia Básica
# Autores: Diego Martínez Baselga      735969
#          David Solanas Sanz          738630
#*********************************************************

#---------------------------------------------------------
# macros
RM = /bin/rm -f  # para limpiar
CC = g++         # compilador
#---------------------------------------------------------
# compilación
CPPFLAGS=-std=c++11 -O3 # opciones compilación
#---------------------------------------------------------
# vars
PROG = transporte
all: ${PROG}
#---------------------------------------------------------
# compilar programa
${PROG}: ${PROG}.cpp
	${CC} ${CPPFLAGS} ${PROG}.cpp -o ${PROG}

#---------------------------------------------------------
# Cuidado con lo que se pone aquí, que se borra sin preguntar
clean:
	$(RM) ${PROG}
