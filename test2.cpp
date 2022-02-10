#include<sys/socket.h>
#include<cstring>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<arpa/inet.h>
#include <netinet/in.h>
#include<algorithm>

using namespace std;

int main(){
    int clientSock;

    clientSock = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in serveAddr;
    serveAddr.sin_port = 27123;
    serveAddr.sin_addr.s_addr = inet_addr("124.223.84.18");
    connect(clientSock,(sockaddr *)&serveAddr,sizeof(serveAddr));

    char * res[105];
    while(recv(clientSock,res,50,0) > 0){
        printf("%s\n",res);
    }
    close(clientSock);
    return 0;
}
