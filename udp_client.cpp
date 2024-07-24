#include <string>
#include <unistd.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include <string.h>
#include "comm.hpp"
int main(int argc,char* argv[]){
    if(argc<3){
        printf("please enter command ip port\n");
        exit(1);
    }
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in local;
    struct sockaddr_in des;
    bzero(&local,sizeof(local));
    bzero(&des,sizeof(des));

    des.sin_port=htons(atoi(argv[2]));
    des.sin_addr.s_addr=inet_addr(argv[1]);
    des.sin_family=AF_INET;
    
    
    socklen_t len=sizeof(local);
    while(1){
        char buf[BUFFSIZE];
        fgets(buf,sizeof(buf)-1,stdin);
        printf("fgets %s",buf);

        int size=sendto(fd,buf,strlen(buf),0,(struct sockaddr*)&des,len);
        printf("size %d\n",size);

        if(size < 0){
            perror("client sendto\n");
            exit(1);
        }
        int rsize=recv(fd,buf,BUFFSIZE-1,0);
        printf("rsize %d\n",rsize);
        buf[rsize]='\0';
        printf("client receive msg from %s :%s\n",inet_ntoa(des.sin_addr),buf);

    }
    close(fd);
    return 0;
}