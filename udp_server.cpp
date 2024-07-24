#include <string>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <strings.h>
#include "comm.hpp"

int main(){
    int fd=socket(AF_INET,SOCK_DGRAM,0);
    struct sockaddr_in local;
    struct sockaddr_in peer;
    
    bzero(&local,sizeof(local));
   
    socklen_t len=sizeof(peer);
    local.sin_family=AF_INET;
    local.sin_addr.s_addr=INADDR_ANY;//htonl(inet_addr(INADDR_ANY));
    local.sin_port=htons(SPORT);
    bind(fd,(struct sockaddr*)&local,len );
    
    while(1){
        char buf[BUFFSIZE];                                                                                                                                                                              
        int size=recvfrom(fd,buf,BUFFSIZE-1,0,(struct sockaddr*)&peer,&len);
        
        printf("server receive size :%d",size);
        if(size<0){
            exit(1);
        }
        buf[size]='\0';
        printf("server receive msg :%s",buf);
        sendto(fd,buf,size,0,(struct sockaddr*)&peer,len);

    }

    return 0;
}