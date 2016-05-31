#include "socklib.h"

/*构造函数*/
Socket::Socket(sockfd_t fd)
{
    this->m_Sockfd = fd;
}

/*创建套结字*/
bool Socket::create(int domain, int type, int procol)
{
    bool res = false;

    this->m_Sockfd = socket(domain, type, procol);
    this->m_addr.sin_family=domain;
    if (IsOk(m_Sockfd)) {
        res = true;
    }/*end if*/

    return res;
}

/*连接函数*/
bool Socket::connect(int port, string host)
{
    bool res = false;
    int flag = NG;

    if (IsOk(m_Sockfd)) {
        this->m_addr.sin_addr.s_addr = inet_addr(host.c_str());
        this->m_addr.sin_port=htons(port);

        flag = ::connect(m_Sockfd, (struct sockaddr*)&m_addr,sizeof(m_addr));
        if (IsOk(flag)) {
            res = true;
        }/*end if*/
    }/*end if*/

    return res;
}

/*绑定套结字*/
bool Socket::bind(int port, string host)
{
    bool res = false;
    int flag = OK;
    if (IsOk(m_Sockfd)) {
        this->m_addr.sin_addr.s_addr = inet_addr(host.c_str());
        this->m_addr.sin_port=htons(port);

        flag = ::bind(m_Sockfd,(struct sockaddr*)&m_addr,sizeof(m_addr));
        if (IsOk(flag)) {
            res = true;
        }/*end if*/
    }/*end if*/

    return res;
}

/*监听连接请求*/
bool Socket::listen(int connum) const
{
    bool res = false;
    int flag = NG;

    if (IsOk(m_Sockfd)) {
        flag = ::listen(m_Sockfd, connum);
        if (IsOk(flag)) {
            res = true;
        }/*end if*/
    }/*end if*/

    return res;
}

/*接收函数*/
bool Socket::accept(Socket &mesg) const
{
    bool res = false;
    int  len = NG;

    len = sizeof(mesg.m_addr);
    if (IsOk(m_Sockfd)) {
       mesg.m_Sockfd = ::accept(m_Sockfd, (struct sockaddr*)&m_addr,
                                (socklen_t *)&len);
       if (IsOk(mesg.m_Sockfd)) {
           res = true;
       }/*end if*/
    }/*end if*/

    return res;
}

/*发送消息*/
bool Socket::sendMesg(Socket &mesg, string &send_buf)
{
    bool res = false;
    int flag = NG;

    if (IsOk(m_Sockfd)) {
        flag = write(mesg.m_Sockfd, send_buf.c_str(), send_buf.length());
        if (IsOk(flag)) {
            res = true;
        }/*end if*/
    }/*end if*/

    return res;
}

/*接收消息*/
bool Socket::recvMesg(Socket &mesg, string &recv_buf)
{
    bool res = false;
    int flag = NG;
    char buf[MAX];

    recv_buf.clear();
    memset(buf, 0x0, MAX);

    if (IsOk(m_Sockfd)) {
        flag = read(mesg.m_Sockfd, &buf, MAX - 1);
        if (IsOk(flag)) {
            res = true;
            recv_buf = buf;
        }/*end if*/
    }/*end if*/

    return res;
}

/*判断描述符是否合法*/
bool Socket::IsOk(int res) const
{
    return res != NG;
}

/*析构函数*/
Socket::~Socket()
{
    if (IsOk(m_Sockfd)) {
        close(m_Sockfd);
    }/*end if*/
}
