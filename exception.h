#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>
/*
#include <exception>
class Exception: public std::exception
{
public:
    Exception();
    Exception(const Exception& cpy){
        if (&cpy==this) return;
        msg = cpy.msg;
    }

    virtual ~Exception()throw(){};

private:
     std::string msg;
};
*/
class Exception{
    public:

    Exception(const std::string& msg);
    Exception();
    virtual ~Exception(){};
    virtual const std::string& what();
    private:
        const std::string m_msg;
};

#endif // EXCEPTION_H
