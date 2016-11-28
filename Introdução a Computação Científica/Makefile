BIN:=ex01
SRC:=ex01.c
CC:=gcc
CFLAGS:=-Wall
LDFLAGS:=-lm

$(BIN): $(SRC)
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS)

test: $(BIN)
	./$(BIN) 16 16

clean:
	$(RM) $(BIN)

.PHONY: clean test

