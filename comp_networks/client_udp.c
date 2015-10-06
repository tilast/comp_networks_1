//
//  client_udp.c
//  comp_networks
//
//  Created by Ihor Krush on 10/6/15.
//  Copyright © 2015 Ihor Krush. All rights reserved.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 7500

int main(int argc, char**argv)
{
    int sockfd,n;
    struct sockaddr_in servaddr,cliaddr;
    char sendline[1000];
    char recvline[1000];
    
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    servaddr.sin_port=htons(PORT);
    
    while (fgets(sendline, 10000,stdin) != NULL)
    {
        sendto(sockfd,sendline,strlen(sendline),0,
               (struct sockaddr *)&servaddr,sizeof(servaddr));
        n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
        recvline[n]=0;
        fputs(recvline,stdout);
    }
}