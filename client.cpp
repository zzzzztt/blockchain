//g++ -std=c++14 client.cpp -lpthread -o client

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
 
#include "BlockChain.h"
#include "BlockChain.cpp"
#include "Block.h"
#include "Block.cpp"
#include "sha256.h"
#include "sha256.cpp"

#define MYPORT 7000
#define BUFFER_SIZE 1024
int main()
{
	int sock_cli;
	fd_set rfds;
	struct timeval tv;
	int retval, maxfd;
	
	int blockIndex = 1;
	BlockChain bChain = BlockChain();
	string bhash;
	bool envoyer = false;

///definir sockfd
	sock_cli = socket(AF_INET,SOCK_STREAM, 0);
// definir sockaddr_in
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(MYPORT); ///porte de serveur
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); ///ip de serveur

/* connecter au serveur 
* return : 0 si succes, -1 sinon
*/
	if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("connect");
		exit(1);
	}

	while(1){

		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		maxfd = 0;
		FD_SET(sock_cli, &rfds);
		if(maxfd < sock_cli)
		maxfd = sock_cli;
		//set timeout*/
		tv.tv_sec = 10;
		tv.tv_usec = 0;
		//attendre la communication
		retval = select(maxfd+1, &rfds, NULL, NULL, &tv);
		if(retval == -1){
			printf("erreur de selection，processus de cote client quitter\n");
			break;
		}else if(retval == 0){
			continue;
		}else{
			//recu le message du serveur
			if(FD_ISSET(sock_cli,&rfds)){
				char recvbuf[BUFFER_SIZE];
				//int len;
				recv(sock_cli, recvbuf, sizeof(recvbuf),0);
				printf("recvbuf %s", recvbuf);
				if(strcmp(recvbuf, "bienrecu") != 0) {
					Block b = Block(blockIndex, recvbuf);
				
					blockIndex++;
					bhash = bChain.AddBlock(b);
					
					envoyer = true;
			
					//cout<< "envoyer status : " << envoyer << endl;
					memset(recvbuf, 0, sizeof(recvbuf));
				}
			}
			//envoyer le hachage au serveur
			
			if( envoyer ){
				char sendbuf[BUFFER_SIZE];
				//fgets(sendbuf, sizeof(sendbuf), stdin);
				
				//cout<<"envoyer"<< bhash.data()<<endl;
				strcpy(sendbuf, bhash.data());
				cout<<"envoyer "<< sendbuf <<endl;
				send(sock_cli, sendbuf, strlen(sendbuf),0); 
					
				memset(sendbuf, 0, sizeof(sendbuf));	
				envoyer = false;
			}
		}
	}

	close(sock_cli);
	return 0;
}
