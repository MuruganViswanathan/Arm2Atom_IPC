/*
 * socket_server.c
 *
 *  Created on: Sep 7, 2017
 *      Author: Murugan Viswanathan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MV_PORT 50123
#define DATASIZE (4*1024)

int main()
{
    int ret = 0;

    //Create Raw socket that allows TCP packets
    //int sock = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);

    //Create TCP socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("[SERVER SOCKET] Error Creating Socket!\n");
        return 1;
    }

    /* set socket opt
    int opt = 1;
    ret = setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    if(ret == -1)
    {
        perror("[SERVER SOCKET] Error setsockopt!\n");
        return 1;
    }
    */

    // bind : attach MV_PORT to socket
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = INADDR_ANY;
    servAddr.sin_port = htons(MV_PORT);
    int addrlen = sizeof(servAddr);

    ret = bind(sockfd, (struct sockaddr*)&servAddr, addrlen);
    if(ret == -1)
    {
        perror("[SERVER SOCKET] Error bind!\n");
        return 1;
    }

    // listen for connection from client
    printf("[SERVER SOCKET] listening for connection...\n");
    static int count = 0;
    ret = listen(sockfd, 5); //max 5 connections allowed
    if(ret == -1)
    {
        perror("[SERVER SOCKET] Error listen!\n");
        return 1;
    }

    printf("[SERVER SOCKET] accepting connection... %d\n", ++count);
    //accept connection
    int new_socket = accept(sockfd, (struct sockaddr*)&servAddr, (socklen_t*)&addrlen);
    if(new_socket == -1)
    {
        perror("[SERVER SOCKET] Error accept!\n");
        return 1;
    }

    // read data
    char data[DATASIZE] = {0}; //4K buffer
    int valread = 0;
    do
    {
        valread = read(new_socket, data, DATASIZE);
        //printf("[SERVER SOCKET] read %d bytes on connection %d : \n%s\n", valread, count, data); fflush(stdout);
        //sleep(1);
        send(new_socket , data , strlen(data) , 0 );
    }while (valread);



    return 0;
}


