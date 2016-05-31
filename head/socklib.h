#ifndef SOCKELIB_H
#define SOCKELIB_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <string>
#include <iostream>

using namespace std;

#define OK      (0)
#define NG      (-1)

#define MAX     (4096)

#define LOCAL   ("127.0.0.1")
#define PORT    (22222)

typedef int sockfd_t;

class Socket
{
public:
    Socket(sockfd_t fd = NG);
    bool create(int domain = AF_INET, int type = SOCK_STREAM,
                int protocol = 0);
    bool bind(int port, string host = LOCAL);
    bool listen(int connum = 1) const;
    bool accept(Socket &mesg) const;
    bool connect(int port, string host = LOCAL);
    bool recvMesg(Socket &mesg, string &recv_buf);
    bool sendMesg(Socket &mesg, string &send_buf);
    virtual ~Socket();

private:
    bool IsOk(int res) const;

    sockfd_t       m_Sockfd;
    struct sockaddr_in m_addr;
};

#endif/*SOCKELIB_H*/
