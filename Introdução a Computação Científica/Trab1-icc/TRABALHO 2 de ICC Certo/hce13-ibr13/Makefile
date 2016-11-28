#variaveis
CC=gcc
INC=inc/
SRC=src/
SOURCE=$(SRC)pdeSolver.c $(SRC)main.c

#geral
all: pdeSolver clean

pdeSolver: $(SOURCE:.c=.o)
	$(CC) -o $@ $(SOURCE:.c=.o) -lm

pdeSolver.o: $(INC)pdeSolver.h $(SRC)pdeSolver.c $(SRC)main.c
	$(CC) -c $(SRC)pdeSolver.c

clean:
	rm -rf $(SOURCE:.c=.o)
