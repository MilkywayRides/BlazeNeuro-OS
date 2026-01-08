CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
SRC = main.c
OBJ = blazeneuro-optimizer

all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(SRC) -o $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJ)
