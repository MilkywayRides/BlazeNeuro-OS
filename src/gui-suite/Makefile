CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`

all: greeter_bin panel_bin

greeter_bin: greeter/main.c
	$(CC) greeter/main.c -o greeter/blazeneuro-greeter $(CFLAGS) $(LIBS)

panel_bin: panel/main.c
	$(CC) panel/main.c -o panel/blazeneuro-panel $(CFLAGS) $(LIBS)

clean:
	rm -f greeter/blazeneuro-greeter panel/blazeneuro-panel
