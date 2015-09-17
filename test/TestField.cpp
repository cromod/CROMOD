/** 
 * @file TestField.cpp
 * @brief Unit test of Field class
 * @author cromod
 * @date september 2015
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestDistField
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "DistField.hpp"
#include "Exception.hpp"
#include <SFML/System/Clock.hpp>

using namespace Cromod::GeomAPI ;
using namespace Cromod::FieldAPI ;
using namespace Cromod::Tools ;
using namespace std ;

BOOST_AUTO_TEST_CASE( BasicTests ) 
{
    cout << "<<< Starting TestDistField >>>" << endl;
    
    cout << "- Default constructor test" << endl;
    try { 
        DistField distfield;
    }
    catch(...) {
        BOOST_FAIL("Default constructor failure");
    }
    
    cout << "- Copy constructor test" << endl;
    DistField distfield;
    try { 
        DistField new_distfield(distfield);
    }
    catch(...) {
        BOOST_FAIL("Copy constructor failure");
    }

}

BOOST_AUTO_TEST_CASE( MethodTests )
{
    double listVal[13][2] = {{200.,-100.},{200.,50.},{150.,100.},{100.,100.},{100.,200.},{-100.,200.},{-100.,100.},
                                         {-200.,100.},{-200.,-100.},{-100.,-100.},{-100.,-200.},{100.,-200.},{100.,-100.}};
    vector<Point> listPoints;
    for(int i=0; i<13; i++) {
        Point point(listVal[i],2);
        listPoints.push_back(point);
    }
    Polygon polygon(listPoints);
    
    Mesh mesh;
    mesh.setPolygon(polygon);
    mesh.setStep(10.);
    mesh.setInitGrid();
    mesh.detectNode();
    
    double ptA[] = {200.,50.};
    double ptB[] = {150.,100.};
    Point pointA(ptA,2);
    Point pointB(ptB,2);
    Segment segment(pointA,pointB);
    vector<Segment> listExit;
    listExit.push_back(segment);

    cout << "- Test of DistField constructor" << endl;
    sf::Clock clock;
    sf::Time time;
    DistField distfield(mesh,listExit);
    time = clock.getElapsedTime();
    cout << "  time elapsed = " << time.asSeconds() << endl;
    cout << "- interpolate test" << endl;
    Point pointO(0.,2);
    Segment seg(pointO,pointB);
    cout << "  interpolated distance = " << distfield.interpolate(0.,0.) << endl;
    cout << "  real distance = " << seg.getLength() << endl;
    
    cout << "<<< End of TestField >>>" << endl;
}