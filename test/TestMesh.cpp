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
    double val[] = {0.,1.};
    Point point1(val,2);
    Node node1(point1);
    try {
        mesh.addNode(node1);
    }
    catch(...) {
        BOOST_FAIL("Mesh::addNode failure");
    }
}

BOOST_AUTO_TEST_CASE( GraphicTest )
{
    cout << "- Graphic test" << endl;
    
    double listVal[13][2]= {{200.,-100.},{200.,50.},{150.,100.},{100.,100.},{100.,200.},{-100.,200.},{-100.,100.},
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
    
    cout << "Grille initiale" << endl;
    mesh.setInitGrid();
    cout << "Nb de noeuds = " << mesh.size() << endl;
    
    cout << "Detection des noeuds" << endl;
    sf::Clock clock;
    mesh.detectNode();
    sf::Time time = clock.getElapsedTime();
    cout << "Time = " << time.asSeconds() << " s"<< endl;
    cout << "Nb de noeuds = " << mesh.size() << endl;
    
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
            c_in.setFillColor(sf::Color::Green);
            c_in.setPosition(point[0]+250.,point[1]+250.);
            window.draw(c_in);
            if (mesh[i].isNearEdge()) {
                sf::CircleShape c_near(2);
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