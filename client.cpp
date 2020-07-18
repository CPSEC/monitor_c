#include <arpa/inet.h>
#include <poll.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

#define MAXLINE 1024
#define SERV_PORT 6666
#define LISTENQ 4
#define INFTIM -1
#define SERV_IP "127.0.0.1"

int main() {
    int connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, SERV_IP, &servaddr.sin_addr);

    if (connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) == -1)
        printf("connect e\n");

    char sendbuf[MAXLINE], recvbuf[MAXLINE];
    bzero(sendbuf, sizeof(sendbuf));
    bzero(recvbuf, sizeof(recvbuf));
    pollfd pfds[2];
    pfds[0].fd = sockfd;
    pfds[0].events = POLLIN;
    pfds[1].fd = STDIN_FILENO;
    pfds[1].events = POLLIN;
    printf("%s", "start..\n");
    for (;;) {
        poll(pfds, 2, -1);
        if (pfds[0].revents & POLLIN) {
            read(pfds[0].fd, recvbuf, MAXLINE);
            write(STDOUT_FILENO, recvbuf, MAXLINE);
        }
        if (pfds[1].revents & POLLIN) {
            read(STDIN_FILENO, sendbuf, MAXLINE);
            write(pfds[0].fd, sendbuf, MAXLINE);
            printf("send\n");
        }
    }
}
