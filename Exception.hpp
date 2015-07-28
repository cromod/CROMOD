/* 
 * File:   Exception.hpp
 * Author: florent
 *
 * Created on 20 juin 2015, 08:58
 */

#ifndef EXCEPTION_HPP
#define	EXCEPTION_HPP

#include <exception> 
#include <string>

namespace Cromod {
    namespace Tools {
        
        class Exception : public std::exception {
        public:
            Exception(std::string Msg, const char * File, int Line) throw() ;
            virtual ~Exception() throw() ;
            virtual const char * what() const throw() ;
            static void logWarning(std::string Msg, const char * File, int Line) ;
        private:
            std::string msg_ ;
            
        };
    }
}

#endif	/* EXCEPTION_HPP */