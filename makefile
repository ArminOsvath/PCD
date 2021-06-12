all: pcd

runc:
	client/client -I Img2.jpg -v 1 -b
runa1:
	client/client -I Img2.jpg -v 1 -b -B -c -e -G -g -h -m -s
runa2:
	client/client -I Img3.jpg -v 1 -b -B -c -e -G -g -h -m -s
runa3:
	client/client -I smoke.jpg -v 1 -b -B -c -e -G -g -h -m -s
runa4:
	client/client -I butterfly.jpg -v 1 -b -B -c -e -G -g -h -m -s
runs:
	server/server

pcd: client.o server.o mylib.o

gdb: 
	cc -g server/server.c lib/mylib 
	mv a.out server/a.out
	cc -g client/client.c lib/mylib 
	mv a.out client/a.out
rungs:
	gdb server/a.out
rungc:
	gdb client/a.out

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