/*
 * socket_client.c
 *
 *  Created on: Sep 7, 2017
 *      Author: Murugan Viswanathan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>

#include <sys/time.h>

#define MV_PORT 50123
#define SERVERADDR "127.0.0.1"
#define PAYLOAD_SIZE 1024
#define TOTAL_ROUNDTRIPS 100

int main(int argc, char* argv[])
{
    int ret = 0;
    if(argc < 2)
    {
        printf("[CLIENT SOCKET] Usage: ./%s <name> \n", argv[0]);
        return 1;
    }

    // create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1)
    {
        perror("[CLIENT SOCKET] Error creating socket!\n");
        return 1;
    }

    // connect to server
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(MV_PORT);
    if(inet_pton(AF_INET, SERVERADDR, &addr.sin_addr) <= 0)
    {
        perror("[CLIENT SOCKET] Error in address!\n");
        return 1;
    }

    ret = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(ret == -1)
    {
        perror("[CLIENT SOCKET] Error connect!\n");
        return 1;
    }

    // send
    char data[PAYLOAD_SIZE+1] = {0};
    char readbuf[PAYLOAD_SIZE+1] = {0};
    int i = 0;
    unsigned long long totaltime = 0;
    struct timeval tv1, tv2;

    for (i = 0; i < TOTAL_ROUNDTRIPS; i++)
    {
        memset(data, 'A'+(i%26), PAYLOAD_SIZE);

        gettimeofday(&tv1, NULL);
        send(sockfd, data, strlen(data), 0);
        read(sockfd, readbuf, PAYLOAD_SIZE);
        gettimeofday(&tv2, NULL);

        totaltime += (unsigned long long)(tv2.tv_sec - tv1.tv_sec)*1000000
                   + (unsigned long long)(tv2.tv_usec - tv1.tv_usec);
    }

    printf("[CLIENT SOCKET] Transferred and Received total of %d bytes..\n", TOTAL_ROUNDTRIPS * PAYLOAD_SIZE);
    printf("[CLIENT SOCKET] Measured total time (for full payload): %llu microseconds, Round trip latency: %llu microseconds per trip with payload size of %d bytes.\n", totaltime, totaltime/TOTAL_ROUNDTRIPS, PAYLOAD_SIZE);

    return 0;
}


