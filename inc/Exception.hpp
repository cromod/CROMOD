/** 
 * @file Exception.hpp
 * @brief Header file of Exception class
 * @author cromod
 * @date june 2015
 */

#ifndef EXCEPTION_HPP
#define	EXCEPTION_HPP

#include <exception> 
#include <string>

namespace Cromod {
    namespace Tools {
        /** @class Exception Exception.hpp
         *  @brief Class to define a exception
         */        
        class Exception : public std::exception {
            public:
                /** @brief Constructor
                 *  @param Msg error message
                 *  @param File file name
                 *  @param Line line number
                 */
                Exception(std::string Msg, const char * File, int Line) throw() ;
                /** @brief Destructor */
                virtual ~Exception() throw() ;
                /** @brief Method to get error message
                 *  @return character string
                 */
                virtual const char * what() const throw() ;
                /** @brief Static function to generate warning message
                 *  @param Msg error message
                 *  @param File file name
                 *  @param Line line number
                 */
                static void logWarning(std::string Msg, const char * File, int Line) ;
            private:
                /** @brief Error message */ 
                std::string msg_ ;
            
        };
    }
}

#endif	/* EXCEPTION_HPP */