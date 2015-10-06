//
//  server.c
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
#include <time.h>

#define FIRST_AMOUNT 2
#define FIRST_TYPE int
#define FIRST_TYPE_FORMAT "%d "

#define SECOND_AMOUNT 5
#define SECOND_TYPE int
#define SECOND_TYPE_FORMAT "%d "

#define PORT 7500

int main(int argc, const char * argv[]) {
    srand(time(NULL));

    struct sockaddr_in local;
    int s, s1;
    int rc;
    FIRST_TYPE* first_buf = (FIRST_TYPE*)malloc(sizeof(FIRST_TYPE) * FIRST_AMOUNT);
    SECOND_TYPE* second_buf = (SECOND_TYPE*)malloc(sizeof(SECOND_TYPE) * SECOND_AMOUNT);
    
    for(int i = 0; i < FIRST_AMOUNT; ++i) {
        first_buf[i] = rand() % 100;
        printf(FIRST_TYPE_FORMAT, first_buf[i]);
    }
    printf("\n");
    
    for(int i = 0; i < SECOND_AMOUNT; ++i) {
        second_buf[i] = rand() % 100;
        printf(SECOND_TYPE_FORMAT, second_buf[i]);
    }
    printf("\n");
    
    local.sin_family = AF_INET;
    local.sin_port = htons(PORT);
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    
    s = socket(AF_INET, SOCK_STREAM, 0);
    
    if(s < 0) {
        perror("[ERROR] socket");
        exit(1);
    }
    
    rc = bind(s, (struct sockaddr *)&local, sizeof(local));
    
    if(rc < 0) {
        perror("[ERROR] bind");
        exit(1);
    }
    
    rc = listen(s, 5);
    
    if(rc) {
        perror("[ERROR] listen");
        exit(1);
    }
    
    s1 = accept(s, NULL, NULL);
    
    if(s1 < 0) {
        perror("[ERROR] accept");
        exit(1);
    }
    
    rc = send(s1, first_buf, sizeof(FIRST_TYPE) * FIRST_AMOUNT, 0);
    
    if(rc < 0) {
        perror("[ERROR] send");
        exit(1);
    }
    
    rc = send(s1, second_buf, sizeof(SECOND_TYPE) * SECOND_AMOUNT, 0);
    
    if(rc < 0) {
        perror("[ERROR] send");
        exit(1);
    }
    
    return 0;
}
