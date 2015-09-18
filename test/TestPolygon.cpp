/** 
 * @file TestPolygon.cpp
 * @brief Unit test of Polygon class
 * @author cromod
 * @date june 2015
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestPolygon
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "Polygon.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI ;
using namespace Cromod::Tools ;
using namespace std ;

BOOST_AUTO_TEST_CASE( BasicTests ) 
{    
    cout << "- Default constructor test" << endl;
    try { 
        Polygon polygon;
    }
    catch(...) {
        BOOST_FAIL("Default constructor failure");
    }
    
    cout << "- Copy constructor test" << endl;
    try { 
        Polygon pol;
        Polygon pol_copy(pol);
    }
    catch(...) {
        BOOST_FAIL("Copy constructor failure");
    }
    
    Point point1(0.,2);
    Point point2(2.,2);
    Point point3(-1.,2);
    vector<Point> listPoints;
    listPoints.push_back(point1);
    listPoints.push_back(point2);
    listPoints.push_back(point3);
    
    cout << "- Constructor test" << endl;
    try { 
        Polygon polygon(listPoints);
    }
    catch(...) {
        BOOST_FAIL("Constructor failure");
    }
    
    cout << "- Polygon::size test" << endl;
    Polygon polygon(listPoints);
    BOOST_REQUIRE_MESSAGE(polygon.size()==3,"Polygon:size failure");
    
    cout << "- [] operator test" << endl;
    Segment seg(point2,point3);
    BOOST_REQUIRE_MESSAGE(polygon[1]==seg,"[] operator failure");
    try {
        polygon[1]=seg;
    }
    catch(...) {
        BOOST_FAIL("[] operator failure");
    }
    
    cout << "- Polygon::deleteAll test" << endl;
    try {
        polygon.deleteAll();
    }
    catch(...) {
        BOOST_FAIL("Polygon::deleteAll failure");
    }
    BOOST_REQUIRE_THROW (polygon.deleteAll(), Exception);
    
    cout << "- Polygon::addSegment test" << endl;
    Segment seg1(point1,point2);
    Segment seg2(point2,point3);
    try {
        polygon.addSegment(seg1);
        polygon.addSegment(seg2);
    }
    catch(...) {
        BOOST_FAIL("Polygon::addSegment failure");
    }
    Point point4(point3);
    point4[1]=0;
    Segment seg3(point4,point1);
    BOOST_REQUIRE_THROW (polygon.addSegment(seg3), Exception);
    
    cout << "- Polygon::addPoint test" << endl;
    polygon.deleteAll();
    BOOST_REQUIRE_THROW (polygon.addPoint(point1), Exception);
    polygon.addSegment(seg1);
    polygon.addSegment(seg2);
    try {
        polygon.addPoint(point4);
    }
    catch(...) {
        BOOST_FAIL("Polygon::addPoint failure");
    }
    
    cout << "- Polygon::delSegment test" << endl;
    try {
        while (polygon.size()>0) polygon.delSegment();
    }
    catch(...) {
        BOOST_FAIL("Polygon::delSegment failure");
    }
    BOOST_REQUIRE_THROW (polygon.delSegment(), Exception);
    
    cout << "- Polygon::isClosed/Polygon::close test" << endl;
    polygon.addSegment(seg1);
    polygon.addSegment(seg2);
    BOOST_REQUIRE_MESSAGE(!(polygon.isClosed()),"Polygon::isClosed failure");
    try {
        polygon.close();
    }
    catch(...) {
        BOOST_FAIL("Polygon::close failure");
    }
    BOOST_REQUIRE_MESSAGE(polygon.isClosed(),"Polygon::isClosed failure");
    
    cout << "- Polygon::getList test" << endl;
    vector<Segment> list;
    seg3.setPoints(point3,point1);
    list.push_back(seg1);
    list.push_back(seg2);
    list.push_back(seg3);
    BOOST_REQUIRE_MESSAGE(polygon.getList()==list,"Polygon::getList failure");
    
    cout << "- Polygon::setList test" << endl;
    Polygon pol;
    try {
        pol.setList(list);
    }
    catch(...) {
        BOOST_FAIL("Polygon::setList failure");
    }
    
    cout << "- Polygon::getPoints test" << endl;
    vector<Point> listPts;
    listPts.push_back(point1);
    listPts.push_back(point2);
    listPts.push_back(point3);
    BOOST_REQUIRE_MESSAGE(polygon.getPoints()==listPts,"Polygon::getPoints failure");
}

BOOST_AUTO_TEST_CASE( MethodTests ) 
{
    double pt1[] = {2.,0.} ;
    Point point1(pt1,2);
    double pt2[] = {0.,2.} ;
    Point point2(pt2,2);
    double pt3[] = {-2.,0.} ;
    Point point3(pt3,2);
    double pt4[] = {0.,-2.} ;
    Point point4(pt4,2);

    vector<Point> list;
    list.push_back(point1);
    list.push_back(point2);
    list.push_back(point3);
    list.push_back(point4);
    Polygon pol(list);
    
    vector<Point> list_bis;
    list_bis.push_back(point1);
    list_bis.push_back(point2);
    list_bis.push_back(point4);
    list_bis.push_back(point3);
    Polygon pol_bis(list_bis);
    
    cout << "- Polygon::isSelfIntersect test" << endl;
    BOOST_REQUIRE_MESSAGE(!(pol.isSelfIntersect()),"Polygon::isSelfIntersect failure");
    BOOST_REQUIRE_MESSAGE(pol_bis.isSelfIntersect(),"Polygon::isSelfIntersect failure");
    
    cout << "- Polygon::getNbIntersect test" << endl;
    Point A(2.,2);
    Point B(-2.,2);
    Segment seg(A,B);
    BOOST_REQUIRE_MESSAGE(pol.getNbIntersect(seg)==2,"Polygon::getNbIntersect failure");
    
    cout << "- Polygon::isOnEdge test" << endl;
    Point C(1.,2);
    BOOST_REQUIRE_MESSAGE(pol.isOnEdge(C),"Polygon::isOnEdge failure");
    
    cout << "- Polygon::isInside test" << endl;
    Point D(0.,2);
    BOOST_REQUIRE_MESSAGE(pol.isInside(D),"Polygon::isInside failure");
    
    cout << "- Polygon::getBottom test" << endl;
    map<Bottom,double> bottom;
    try {
        bottom = pol.getBottom();
    }
    catch(...) {
        BOOST_FAIL("Polygon::getBottom failure");
    }
    BOOST_REQUIRE_MESSAGE(bottom[XMAX]==2.,"Polygon::getBottom failure");
    BOOST_REQUIRE_MESSAGE(bottom[YMAX]==2.,"Polygon::getBottom failure");
    BOOST_REQUIRE_MESSAGE(bottom[XMIN]==-2.,"Polygon::getBottom failure");
    BOOST_REQUIRE_MESSAGE(bottom[YMIN]==-2.,"Polygon::getBottom failure");
}