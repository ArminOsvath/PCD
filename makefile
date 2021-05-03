all: pcd

runc:
	client/client
runs:
	server/server

pcd: client.o server.o mylib.o

mylib.o: lib/mylib.c
	gcc -c lib/mylib.c -o lib/mylib

client.o: client/client.c
	gcc client/client.c lib/mylib.c -o client/client

server.o: server/server.c
	gcc server/server.c lib/mylib.c -o server/server

clean: 
	rm -rf *.o *.jpg *.png all