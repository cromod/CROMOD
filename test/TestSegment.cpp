/** 
 * @file TestSegment.cpp
 * @brief Unit test of Segment class
 * @author cromod
 * @date june 2015
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestSegment
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <cmath>
#include "Constants.hpp"
#include "Segment.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI ;
using namespace Cromod::Tools ;
using namespace std ;

BOOST_AUTO_TEST_CASE( BasicTests ) 
{    
    cout << "- Default constructor test" << endl;
    try { 
        Segment seg;
    }
    catch(...) {
        BOOST_FAIL("Default constructor failure");
    }
    
    cout << "- Copy constructor test" << endl;
    try { 
        Segment seg;
        Segment new_seg(seg);
    }
    catch(...) {
        BOOST_FAIL("Copy constructor failure");
    }
    
    cout << "- Constructor test" << endl;
    Point point1(0.,2);
    Point point2(21.,2);
    bool exit(false);
    Point pointf(0.,3);
    BOOST_REQUIRE_THROW(Segment(pointf,pointf,exit), Exception);
    try {
        Segment seg(point1,point2,exit);
    }
    catch(...) {
        BOOST_FAIL("Constructor failure");
    }
    
    cout << "- Equality operator test" << endl;
    Segment seg1(point1,point2,exit);
    Segment seg2(point1,point2,exit);
    BOOST_REQUIRE_MESSAGE(seg1==seg2,"Equality operator failure");
    
    cout << "- Inequality operator test" << endl;
    Point point3(-2.,2);
    Segment seg3(point1,point3,exit);
    BOOST_REQUIRE_MESSAGE(seg1!=seg3,"Inequality operator failure");
    
    cout << "- Segment::setExit test" << endl;
    try {
        seg1.setExit(true);
    }
    catch(...) {
        BOOST_FAIL("Segment::setExit failure");
    }
    
    cout << "- Segment::isExit test" << endl;
    BOOST_REQUIRE_MESSAGE(seg1.isExit(),"Segment::isExit failure");
    
    cout << "- Segment::setOne/Segment::setTwo test" << endl;
    BOOST_REQUIRE_THROW (seg1.setOne(pointf), Exception);
    BOOST_REQUIRE_THROW (seg1.setTwo(pointf), Exception);
    try {
        seg1.setOne(point2);
        seg1.setTwo(point3);
    }
    catch(...) {
        BOOST_FAIL("Segment::setOne/Segment::setTwo failure");
    }

    cout << "- Segment::getOne/Segment::getTwo test" << endl;
    BOOST_REQUIRE_MESSAGE(seg1.getOne()==point2,"Segment::getOne failure");
    BOOST_REQUIRE_MESSAGE(seg1.getTwo()==point3,"Segment::getTwo failure");
    
    cout << "- Segment::setPoints test" << endl;
    BOOST_REQUIRE_THROW(seg1.setPoints(pointf,pointf), Exception);
    BOOST_REQUIRE_THROW(seg1.setPoints(point2,pointf), Exception);
    BOOST_REQUIRE_THROW(seg1.setPoints(pointf,point3), Exception);
    try {
        seg1.setPoints(point2,point3);
    }
    catch(...) {
        BOOST_FAIL("Segment::setPoints failure");
    }
    
    cout << "- Segment::getPoints test" << endl;
    vector<Point> points;
    points.push_back(point2);
    points.push_back(point3);
    BOOST_REQUIRE_MESSAGE(seg1.getPoints()==points,"Segment::getPoints failure");
    
    cout << "- Segment::getVector test" << endl;
    Vector vect(point3-point2);
    BOOST_REQUIRE_MESSAGE(seg1.getVector()==vect,"Segment::getVector failure");
    
    cout << "- Segment::getLength test" << endl;
    double norm(sqrt(pow(vect[0],2)+pow(vect[1],2)));
    BOOST_REQUIRE_MESSAGE(seg1.getLength()==norm,"Segment::getLength failure");
    
    cout << "- Segment::isSegment test" << endl;
    BOOST_REQUIRE_MESSAGE(seg1.isSegment(),"Segment::isSegment failure");
}

BOOST_AUTO_TEST_CASE( MethodTests ) 
{
    cout << "- Segment::orientation test" << endl;
    double pt1[] = {-1.,1.} ;
    Point point1(pt1,2);
    Point point2(0.,2);
    Point point3(1.,2);
    double pt4[] = {1.,-1.} ;
    Point point4(pt4,2);
    Segment seg;
    BOOST_REQUIRE_MESSAGE(Segment::orientation(point1,point2,point3)>0.,
                            "Segment::orientation failure");
    BOOST_REQUIRE_MESSAGE(Segment::orientation(point3,point2,point1)<0.,
                            "Segment::orientation failure");
    BOOST_REQUIRE_MESSAGE(Segment::orientation(point1,point2,point4)==0.,
                            "Segment::orientation failure");

    cout << "- Segment::checkIntersect test" << endl;
    double pt5[] = {2.,0.} ;
    Point point5(pt5,2);
    Segment seg1(point1,point2);
    Segment seg2(point2,point3);
    Segment seg3(point2,point4);
    Segment seg4(point3,point5);
    BOOST_REQUIRE_MESSAGE(seg1.checkIntersect(seg2),
                            "Segment::checkIntersect failure");
    BOOST_REQUIRE_MESSAGE(!(seg3.checkIntersect(seg4)),
                            "Segment::checkIntersect failure");
    
    cout << "- Segment::checkParallel test" << endl;
    BOOST_REQUIRE_MESSAGE(!(seg1.checkParallel(seg2)),
                            "Segment::checkParallel failure");
    BOOST_REQUIRE_MESSAGE(seg3.checkParallel(seg4),
                            "Segment::checkParallel failure");
    
    cout << "- Segment::checkInclude test" << endl;
    seg.setPoints(point1,point4);
    BOOST_REQUIRE_MESSAGE(seg.checkInclude(point2),
                            "Segment::checkInclude failure");
    BOOST_REQUIRE_MESSAGE(!(seg.checkInclude(point3)),
                            "Segment::checkInclude failure");
    
    cout << "- Segment::findPerPoint test" << endl;
    Point proj = seg.findPerPoint(point3);
    seg.setPoints(proj,point2);
    BOOST_REQUIRE_MESSAGE(seg.getLength()<GEOM_TOLERANCE,
                            "Segment::findPerPoint failure");
    
    cout << "- Segment::getMinDist test" << endl;
    double val = seg2.getLength();
    BOOST_REQUIRE_MESSAGE(seg.getMinDist(point3)==val,
                            "Segment::getMinDist failure");
}