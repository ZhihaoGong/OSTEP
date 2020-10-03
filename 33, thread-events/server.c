#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define BUFFSIZE 1024

int main()
{
    int server_sockfd = setup_tcp_server(8888, 5);

    int client_sockfd;
    int client_len;
    struct sockaddr_in client_address;

    int result;
    fd_set readfds, testfds;

    FD_ZERO(&readfds);
    FD_SET(server_sockfd, &readfds);

    while (1)
    {
        char ch;
        int fd;
        int nread;
        testfds = readfds;
        printf("server waiting\n");

        result = select(FD_SETSIZE, &testfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0);
        if (result < 1)
        {
            perror("select return error");
            exit(1);
        }

        for (fd = 0; fd < FD_SETSIZE; fd++)
        {
            if (FD_ISSET(fd, &testfds))
            {
                if (fd == server_sockfd)
                {
                    client_len = sizeof(client_address);
                    client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
                    FD_SET(client_sockfd, &readfds);
                    printf("adding client on fd %d\n", client_sockfd);
                }
                else
                {
                    ssize_t pos = 0;
                    ssize_t filelen = BUFFSIZE;
                    char *filename = (char *)malloc(BUFFSIZE);

                    while (1)
                    {
                        ssize_t n;
                        char buf[BUFFSIZE];
                        if ((n = read(fd, buf, sizeof(buf))) < 0)
                        {
                            if (errno != EAGAIN)
                            {
                                // error(1, errno, "read error");
                                close(fd);
                                FD_CLR(fd, &readfds);
                            }
                            break;
                        }

                        if (n == 0)
                        {
                            close(fd);
                            FD_CLR(fd, &readfds);
                            break;
                        }

                        if (pos + n > filelen)
                        {
                            filelen += BUFFSIZE;
                            filename = (char *)realloc(filename, filelen);
                        }

                        memcpy(filename + pos, buf, n);
                    }

                    // add line teminate
                    printf("%s\n", filename);
                }
            }
        }

        return 0;
    }
}