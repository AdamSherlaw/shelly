all: shelly

shelly: main.o builtins.o execution.o token.o
	gcc main.o builtins.o execution.o token.o -o shelly

main.o: main.c
	gcc -c main.c

builtins.o: builtins.c
	gcc -c builtins.c

execution.o: execution.c
	gcc -c execution.c

token.o: token.c
	gcc -c token.c

clean:
	rm -rf *o shelly


