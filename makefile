cc = gcc
CFLAGS = -w -std=c99

all: clean server client

server: ./src/server/*.c
	${CC} ${CFLAGS} ./src/server/*.c -o ./out/server_c

client: ./src/client/C_CPP/*.c
	${CC} ${CFLAGS} ./src/client/C_CPP/*.c -o ./out/client_c

clean: cleanserver cleanclient

cleanserver:
	rm -f ./out/server_c

cleanclient:
	rm -f ./out/client_c
