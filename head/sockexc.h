#ifndef SOCKEXC_H
#define SOCKEXC_H

#include <iostream>
#include <string>
using namespace std;

class SockException
{
public:
    SockException(string str);
    string &GetReason();
    virtual ~SockException();
private:
    string m_StrRes;
};

#endif/*SOCKEXC_H*/
