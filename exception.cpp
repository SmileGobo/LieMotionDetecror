#include "exception.h"

Exception::Exception(const std::string& msg):m_msg(msg){}
Exception::Exception():m_msg(""){}
Exception::~Exception();
const std::string& Exception::what(){return m_msg;}
