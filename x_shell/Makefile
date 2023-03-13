CC=g++
CFLAGS=-c -Wall

all: x_shell

x_shell: x_shell.o
	$(CC) x_shell.o redirection.o fork_exec.o helper.o -o x_shell

x_shell.o: x_shell.cxx
	$(CC) $(CFLAGS) x_shell.cxx redirection.cxx fork_exec.cxx helper.cxx

clean:
	rm -rf *o x_shell
