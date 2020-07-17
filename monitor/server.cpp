#include "server.h"

#include <arpa/inet.h>
#include <limits.h>
#include <poll.h>
#include <stdio.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <QDebug>

#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace std;
using namespace rapidjson;

#define MAXLINE 1024
#define SERV_PORT 6666
#define LISTENQ 1
#define INFTIM -1
#define OPEN_MAX 2

Server::Server() {}

void Server::receiveloop() {
    int i, maxi, listenfd, connfd, sockfd;
    int nready;
    ssize_t n;
    char buf[MAXLINE];
    socklen_t clilen;
    struct pollfd pfds[OPEN_MAX];
    struct sockaddr_in cliaddr, servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    bind(listenfd, (sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);
    pfds[0].fd = listenfd;
    pfds[0].events = POLLIN;
    for (i = 1; i < OPEN_MAX; ++i) {
        pfds[i].fd = -1;
    }
    maxi = 0;
    qDebug() << "starting server...\n";
    for (;;) {
        nready = poll(pfds, maxi + 1, INFTIM);
        if (pfds[0].revents & POLLIN) {  // new conncection
            clilen = sizeof(cliaddr);
            connfd = accept(listenfd, (sockaddr *)&cliaddr, &clilen);
            qDebug() << "connected\n";
            for (i = 1; i < OPEN_MAX; ++i) {
                if (pfds[i].fd < 0) {
                    pfds[i].fd = connfd;
                    break;
                }
            }
            if (i == OPEN_MAX) return;
            pfds[i].events = POLLIN | POLLOUT;
            if (i > maxi) maxi = i;
            if (--nready <= 0) continue;
        }
        for (int i = 1; i <= maxi; ++i) {
            if ((sockfd = pfds[i].fd) < 0) continue;
            if (pfds[i].revents & POLLIN) {
                readJson(pfds[i].fd);
            }
            if (pfds[i].revents & POLLOUT) {
                writeJson(pfds[i].fd);
            }
            if (--nready <= 0) break;
        }
    }
}

void Server::readJson(int &fd) {
    char buf[MAXLINE];
    read(fd, buf, MAXLINE);
    write(fd, buf, MAXLINE);
    Document d;
    d.Parse(buf);
    emit update(buf);
    qDebug() << buf << endl;
}

void Server::sendsetting() {}

void Server::writeJson(int &fd) {}
