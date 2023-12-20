cc = gcc
CFLAGS = -w -std=c99 -pthread

all: clean server client

server: ./src/server/*.c
	${CC} ${CFLAGS} ./src/server/*.c -o ./out/server

client: ./src/client/linux/*.c
	${CC} ${CFLAGS} ./src/client/linux/*.c -o ./out/linux/client

clean: cleanserver cleanclient

cleanserver:
	rm -f ./out/server_c

cleanclient:
	rm -f ./out/linux/client
