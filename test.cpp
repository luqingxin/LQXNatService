#include<sys/socket.h>
#include<cstring>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<arpa/inet.h>
#include <netinet/in.h>

using namespace std;

const unsigned short defaltPort = 27123;

int main(){
    int serviceSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    sockaddr_in serviceAddr;
    memset(&serviceAddr,0,sizeof(serviceAddr));
    serviceAddr.sin_port = htons(defaltPort);
    serviceAddr.sin_family = AF_INET;
    serviceAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(serviceSock,(sockaddr*)&serviceAddr,sizeof(serviceAddr));

    listen(serviceSock, 5);

    sockaddr_in targetAddr;
    socklen_t targetAddrLen;
    int targetSock;
    memset(&targetAddr,0,sizeof(targetAddr));
    targetSock = accept(serviceSock,(struct sockaddr*)&targetAddr,&targetAddrLen);

    printf("");

    return 0;
}