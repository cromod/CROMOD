/** 
 * @file TestException.cpp
 * @brief Unit test of Exception class
 * @author cromod
 * @date june 2015
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestException
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Exception.hpp"

using namespace Cromod::Tools ;
using namespace std ;

string testException() 
{
    string Msg("Coucou !");
    const char * File("Machin.cpp");
    int Line(1237);
    Exception e(Msg,File,Line);
    return static_cast<string>(e.what());
}

BOOST_AUTO_TEST_CASE( TestException ) 
{
    cout << "Unit test on class Exception..." << endl;
    BOOST_CHECK( testException() == "Error (Machin.cpp:1237) : Coucou !" );
}
