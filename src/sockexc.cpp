#include "sockexc.h"

SockException::SockException(string str)
{
    this->m_StrRes = str;
}
string &SockException::GetReason()
{
    return m_StrRes;
}
SockException::~SockException()
{
}
