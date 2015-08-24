/* 
 * File:   TestNode.cpp
 * Author: florent
 *
 * Created on 7 juil. 2015, 21:54:27
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestNode
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Node.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI ;
using namespace Cromod::Tools ;
using namespace std ;

BOOST_AUTO_TEST_CASE( BasicTests ) 
{    
    cout << "<<< Starting TestNode >>>" << endl;
    
    cout << "- Default constructor test" << endl;
    try { 
        Node node;
    }
    catch(...) {
        BOOST_FAIL("Default constructor failure");
    }
    
    cout << "- Copy constructor test" << endl;
    try { 
        Node node;
        Node new_node(node);
    }
    catch(...) {
        BOOST_FAIL("Copy constructor failure");
    }
    
    cout << "- Constructor test" << endl;
    Point point(0.,2);
    Point pointf(0.,4);
    bool near(false);
    bool inside(false);
    BOOST_REQUIRE_THROW(Node(pointf,near,inside), Exception);
    try {
        Node node(point,near,inside);
    }
    catch(...) {
        BOOST_FAIL("Constructor failure");
    }
    
    cout << "- Equality operator test" << endl;
    Node node1(point);
    Node node2(point);
    BOOST_REQUIRE_MESSAGE(node1==node2,"Equality operator failure");
    
    cout << "- Inequality operator test" << endl;
    Point point1(-2.,2);
    Node node3(point1);
    BOOST_REQUIRE_MESSAGE(node1!=node3,"Inequality operator failure");
    
    cout << "- Copy operator test" << endl;
    node2 = node3;
    BOOST_REQUIRE_MESSAGE(node2==node3,"Copy operator failure");
    
    cout << "- Node::setPosition test" << endl;
    Point point2(2.,2);
    BOOST_REQUIRE_THROW(node1.setPosition(pointf), Exception);
    try {
        node1.setPosition(point2);
    }
    catch(...) {
        BOOST_FAIL("Node::setPosition failure");
    }
    
    cout << "- Node::getPosition test" << endl;
    BOOST_REQUIRE_MESSAGE(node1.getPosition()==point2,"Node::getPosition failure");
    
    cout << "- Node::setNearEdge test" << endl;
    try {
        node2.setNearEdge(true);
    }
    catch(...) {
        BOOST_FAIL("Node::setNearEdge failure");
    }

    cout << "- Node::isNearEdge test" << endl;
    BOOST_REQUIRE_MESSAGE(node2.isNearEdge(),"Node::isNearEdge failure");
    
    cout << "- Node::setInside test" << endl;
    try {
        node2.setInside(true);
    }
    catch(...) {
        BOOST_FAIL("Node::setInside failure");
    }

    cout << "- Node::isInside test" << endl;
    BOOST_REQUIRE_MESSAGE(node2.isInside(),"Node::isInside failure");
    
    cout << "<<< End of TestNode >>>" << endl;
}