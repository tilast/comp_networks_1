//
//  main.c
//  comp_networks
//
//  Created by Ihor Krush on 10/6/15.
//  Copyright © 2015 Ihor Krush. All rights reserved.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

const char *byte_to_binary(int x)
{
    static char b[20];
    b[0] = '\0';
    
    int z;
    for (z = 1048576; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }
    
    return b;
}


int main(int argc, const char * argv[]) {
    struct sockaddr_in peer;
    int s;
    int rc;
    char buf[1];
    
    peer.sin_family = AF_INET;
    peer.sin_port = htons(7500);
    
    printf("%s %d\n", byte_to_binary(7500), 7500);
    printf("%s %d\n", byte_to_binary(htons(7500)), htons(7500));
    
    return 0;
}
