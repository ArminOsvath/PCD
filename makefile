all: pcd

runc:
	client/client -I Img2.jpg
runa:
	client/client -I unnamed.jpg -v 1 -b -B -c -e -G -g -h -m -s
runs:
	server/server

pcd: client.o server.o mylib.o

mylib.o: lib/mylib.c
	gcc -c lib/mylib.c -o lib/mylib

client.o: client/client.c
	gcc client/client.c lib/mylib.c -o client/client

server.o: server/server.c
	gcc server/server.c lib/mylib.c -o server/server

git:
	git push -u origin main

clean: 
	rm -rf ./server/output/* ./server/image/* ./client/output/*