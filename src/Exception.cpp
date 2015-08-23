/* 
 * File:   Exception.cpp
 * Author: florent
 * 
 * Created on 20 juin 2015, 08:58
 */

#include "Exception.hpp"
#include <iostream> 
#include <sstream> 

using namespace Cromod::Tools ;
using namespace std ;

void Exception::logWarning(string Msg, const char * File , int Line)
{
    cerr << "Warning (" << File << ":" << Line << ") : " << Msg << endl ;
}

Exception::Exception(string Msg, const char * File , int Line) throw ()
{
    ostringstream oss ; 
    oss << "Error (" << File << ":" << Line << ") : " << Msg ; 
    this->msg_ = oss.str() ;
}

Exception::~Exception() throw() {
}

const char * Exception::what() const throw()
{
    return this->msg_.c_str();
}
