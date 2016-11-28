CC=gcc
CFLAGS=-Wall -I.
OBJ = conflito.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

conflito: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ)
