all : server client
.PHONY : all
server : server/server.c 
	gcc -Wall -02 server/server.c -o server
client : client/client.c 
	gcc -Wall -O2 client/client.c -o client
clean :
	rm client/client server/server