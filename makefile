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
runall: runa1 runa2 runa3 runa4 
java:
	mvn package exec:java
ad:
	client/admin
runs:
	server/threader

pcd: client.o threader.o mylib.o admin.o 

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

admin.o: client/admin.c
	gcc client/admin.c lib/mylib.c -o client/admin

unix.o: server/unix.c
	gcc server/unix.c lib/mylib.c -o server/unix

threader.o: server/threader.c
	gcc server/server.c server/unix.c server/threader.c lib/mylib.c -l pthread -o server/threader 

git: prepare
	git push -u origin main
prepare: 
	tee  ./client/output/unnamed.jpg ./server/image/unnamed.jpg ./server/output/unnamed.jpg < ./client/image/unnamed.jpg 

clean: 
	rm -rf ./server/output/* ./server/image/* ./client/output/* ./jclient/*_*.jpg