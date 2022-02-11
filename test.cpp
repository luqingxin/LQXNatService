#include<sys/socket.h>
#include<cstring>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<arpa/inet.h>
#include <netinet/in.h>
#include<algorithm>
#include<errno.h>


using namespace std;

const unsigned short defaltPort = 27123;

char *itoa(int x){
    char *c ;
    c = (char *)malloc(sizeof(char)*100);
    int n;
    for(n=0;x;n++){
        c[n] = x%10 + '0';
        x/=10;
    }
    for(int i=0;i<n/2;i++){
        swap(c[i],c[n-i-1]);
    }
    return c;
}

int main(){
    int serviceSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    sockaddr_in serviceAddr;
    memset(&serviceAddr,0,sizeof(serviceAddr));
    serviceAddr.sin_port = htons(defaltPort);
    //printf("%d\n",serviceAddr.sin_port);
    serviceAddr.sin_family = AF_INET;
    serviceAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int k = bind(serviceSock,(sockaddr*)&serviceAddr,sizeof(serviceAddr));

    while(k)
    {
        printf("%d\n",errno);
        k = bind(serviceSock,(sockaddr*)&serviceAddr,sizeof(serviceAddr));
    }
/*  sockaddr_in addr;
    socklen_t iLen = sizeof(addr);
    getsockname(serviceSock,(struct sockaddr*)&addr,&iLen);
    //addr = *((struct sockaddr_in*)result->ai_addr);
    printf("%d\n",addr.sin_port);
    printf("%d\n",addr.sin_addr);
    printf("%x\n",addr.sin_addr);
*/
    listen(serviceSock, 5);

    
    sockaddr_in targetAddr;
    socklen_t targetAddrLen = sizeof(sockaddr_in); // set addrLen
    int targetSock;
    memset(&targetAddr,0,sizeof(targetAddr));
    targetSock = accept(serviceSock,(struct sockaddr*)&targetAddr,&targetAddrLen);
    
    send(targetSock,inet_ntoa(targetAddr.sin_addr),1+sizeof(inet_ntoa(targetAddr.sin_addr)),0);
    send(targetSock,itoa(ntohs(targetAddr.sin_port)),1+sizeof(itoa(targetAddr.sin_port)),0);
    
    sockaddr_in addr;
    socklen_t iLen = sizeof(sockaddr_in);

    /*printf("%d\n",targetAddr.sin_port);
    printf("%d\n",ntohs(targetAddr.sin_port));
    printf("%s\n",inet_ntoa(targetAddr.sin_addr));

    //getpeername(targetSock,(struct sockaddr*)&addr,&iLen);
    printf("%d\n",ntohs(addr.sin_port));
    printf("%s\n",inet_ntoa(addr.sin_addr));*/

    //getsockname(targetSock,(struct sockaddr*)&addr,&iLen);
    /*printf("%d\n",ntohs(addr.sin_port));
    printf("%s\n",inet_ntoa(addr.sin_addr));

    printf("%d\n",targetAddr.sin_port);
    printf("%d\n",ntohs(targetAddr.sin_port));
    printf("%s\n",inet_ntoa(targetAddr.sin_addr));
*/
    shutdown(serviceSock,SHUT_RDWR);
    shutdown(targetSock,SHUT_RDWR);
    close(serviceSock);
    close(targetSock);
    return 0;
}