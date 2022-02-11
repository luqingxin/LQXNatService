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
    serveAddr.sin_family = AF_INET;
    serveAddr.sin_port =htons(27123);
    serveAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ir = connect(clientSock,(sockaddr *)&serveAddr,sizeof(serveAddr));

    printf("%d\n",ir);
    char res[105];
    while(recv(clientSock,res,50,0) > 0){
        printf("%s\n",res);
    }
    shutdown(clientSock,SHUT_RDWR);
    close(clientSock);
    return 0;
}
