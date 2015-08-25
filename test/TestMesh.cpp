#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TestMesh
#include <boost/test/unit_test.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include "Mesh.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI ;
using namespace Cromod::Tools ;
using namespace std ;

BOOST_AUTO_TEST_CASE( BasicTests ) 
{
    cout << "<<< Starting TestMesh >>>" << endl;
    
    cout << "- Default constructor test" << endl;
    try { 
        Mesh mesh;
    }
    catch(...) {
        BOOST_FAIL("Default constructor failure");
    }
    
    cout << "- Copy constructor test" << endl;
    Mesh mesh;
    try { 
        Mesh new_mesh(mesh);
    }
    catch(...) {
        BOOST_FAIL("Copy constructor failure");
    }
    
    cout << "- Mesh::addNode test" << endl;
    double val1[] = {0.,1.};
    Point point1(val1,2);
    Node node1(point1);
    try {
        mesh.addNode(node1);
    }
    catch(...) {
        BOOST_FAIL("Mesh::addNode failure");
    }
    
    cout << "- Mesh::size test" << endl;
    double val2[] = {2.,1.};
    Point point2(val2,2);
    Node node2(point2);
    mesh.addNode(node2);
    BOOST_REQUIRE_MESSAGE(mesh.size()==2,"Mesh::size failure");
    
    cout << "- [] operator test" << endl;
    BOOST_REQUIRE_MESSAGE(mesh[0]==node1,"[] operator failure");
    
    cout << "- Mesh::deleteNode test" << endl;
    double val3[] = {0.,1.};
    Point point3(val3,2);
    Node node3(point3);
    mesh.addNode(node3);
    try {
        mesh.deleteNode();
    }
    catch(...) {
        BOOST_FAIL("Mesh::deleteNode failure");
    }
    BOOST_REQUIRE_MESSAGE(mesh.size()==2,"Mesh::deleteNode failure");
    
    cout << "- Mesh::deleteAll test" << endl;
    try {
        mesh.deleteAll();
    }
    catch(...) {
        BOOST_FAIL("Mesh::deleteAll failure");
    }
    BOOST_REQUIRE_MESSAGE(mesh.size()==0,"Mesh::deleteAll failure");
}

BOOST_AUTO_TEST_CASE( MethodTests )
{
    double listVal[13][2]= {{200.,-100.},{200.,50.},{150.,100.},{100.,100.},{100.,200.},{-100.,200.},{-100.,100.},
                                         {-200.,100.},{-200.,-100.},{-100.,-100.},{-100.,-200.},{100.,-200.},{100.,-100.}};
    vector<Point> listPoints;
    for(int i=0; i<13; i++) {
        Point point(listVal[i],2);
        listPoints.push_back(point);
    }
    Polygon polygon(listPoints);
    Mesh mesh;
    
    cout << "- Mesh::setPolygon test" << endl;
    try {
        mesh.setPolygon(polygon);
    }
    catch(...) {
        BOOST_FAIL("Mesh::setPolygon failure");
    }
    
    cout << "- Mesh::getPolygon test" << endl;
    try {
        Polygon pol(mesh.getPolygon());
    }
    catch(...) {
        BOOST_FAIL("Mesh::getPolygon failure");
    }
    
    cout << "- Mesh::setStep test" << endl;
    try {
        mesh.setStep(10.);
    }
    catch(...) {
        BOOST_FAIL("Mesh::setStep failure");
    }
    
    cout << "- Mesh::getStep test" << endl;
    BOOST_REQUIRE_MESSAGE(mesh.getStep()==10.,"Mesh::getStep failure");
    
    cout << "- Mesh::setInitGrid test" << endl;
    try {
        mesh.setInitGrid();
    }
    catch(...) {
        BOOST_FAIL("Mesh::setInitGrid failure");
    }
    cout << "  Nb de noeuds = " << mesh.size() << endl;
    
    cout << "- Mesh::isInit test" << endl;
    BOOST_REQUIRE_MESSAGE(mesh.isInit(),"Mesh::isInit failure");
    
    cout << "- Mesh::setInit test" << endl;
    try {
        mesh.setInit(false);
    }
    catch(...) {
        BOOST_FAIL("Mesh::setInit failure");
    }
    BOOST_REQUIRE_MESSAGE(!mesh.isInit(),"Mesh::setInit failure");
    
    cout << "- Mesh::detectNode test" << endl;
    sf::Clock clock;
    try {
        mesh.detectNode();
    }
    catch(...) {
        BOOST_FAIL("Mesh::detectNode failure");
    }
    sf::Time time = clock.getElapsedTime();
    cout << "  Time = " << time.asSeconds() << " s"<< endl;
    cout << "  Nb de noeuds = " << mesh.size() << endl;
    
    cout << "- Mesh::isDetect test" << endl;
    BOOST_REQUIRE_MESSAGE(mesh.isDetect(),"Mesh::isDetect failure");
    
    cout << "- Mesh::setDetect test" << endl;
    try {
         mesh.setDetect(false);
    }
    catch(...) {
        BOOST_FAIL("Mesh::setDetect failure");
    }
    BOOST_REQUIRE_MESSAGE(!mesh.isDetect(),"Mesh::setInit failure");
    
    cout << "- Graphic test of Mesh" << endl;
    sf::RenderWindow window(sf::VideoMode(500, 500), "Test of Mesh class");
    // on fait tourner le programme jusqu'à ce que la fenêtre soit fermée
    while (window.isOpen()) {
        // on inspecte tous les evenements de la fenetre qui ont ete emis depuis la precedente itération
        sf::Event event;
        while (window.pollEvent(event)) {
            // evenement "fermeture demandee" : on ferme la fenetre
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // fenetre en blanc
        window.clear(sf::Color::White);
        // trace du maillage
        for(int i=0; i<mesh.size(); i++) {
            Point point(mesh[i].getPosition());
            sf::CircleShape c_in(4);
	    c_in.setOrigin(4.,4.);
            c_in.setFillColor(sf::Color::Green);
            c_in.setPosition(point[0]+250.,point[1]+250.);
            window.draw(c_in);
            if (mesh[i].isNearEdge()) {
                sf::CircleShape c_near(2);
		c_near.setOrigin(2.,2.);
                c_near.setFillColor(sf::Color::Red);
                c_near.setPosition(point[0]+250.,point[1]+250.);
                window.draw(c_near);
            }
        }
        // fin de la frame courante, affichage de tout ce qu'on a dessine
        window.display();
    }

    cout << "<<< End of TestMesh >>>" << endl;
}