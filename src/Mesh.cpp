/** 
 * @file Mesh.cpp
 * @brief Source file of Mesh class
 * @author cromod
 * @date july 2015
 */

#include "Mesh.hpp"
#include "Exception.hpp"
#include "Constants.hpp"
#include <cmath>
#include <iostream>

using namespace Cromod::GeomAPI;
using namespace Cromod::Tools;
using namespace std;

Mesh::Mesh() : listNode_(), 
               polygon_(),
               init_(false),
               detect_(false),
               step_(1.),
               dim_(2,0.)
{
}

Mesh::Mesh(const Mesh& mesh) 
{
    if (mesh.dim_.size()!=2) 
        throw(Exception("mesh.dim_ out of range in Mesh::Mesh",__FILENAME__,__LINE__)) ;
    if (mesh.step_<=0.)
        throw(Exception("Wrong step value of mesh argument in Mesh::Mesh",__FILENAME__,__LINE__)) ;
    listNode_ = mesh.listNode_ ;
    polygon_ = mesh.polygon_ ;
    init_ = mesh.init_ ;
    detect_ = mesh.detect_ ;
    step_ = mesh.step_ ;
    dim_ = mesh.dim_ ;
}

Mesh::~Mesh() 
{
}

Node& Mesh::operator[](const unsigned int& i)
{
    return listNode_[i] ;
}

unsigned int Mesh::size() const
{
    return listNode_.size() ;
}

unsigned int Mesh::index(const Node &node) const
{
    if (this->size()==0) throw(Exception("Nothing to find with Mesh::index"
                                ,__FILENAME__,__LINE__)) ;
    
    unsigned int it=0;
    unsigned int size=this->size();
    while (listNode_[it]!=node && it<(size-1)) it++;
    
    if (listNode_[it]==node) return it;
    else throw(Exception("Node object not found with Mesh::index"
                                ,__FILENAME__,__LINE__)) ;
}

void Mesh::addNode(Node node)
{
    listNode_.push_back(node) ;
}

void Mesh::deleteNode()
{
    if (this->size()>0) listNode_.pop_back();
    else throw(Exception("Nothing to delete with Mesh::deleteNode"
                                ,__FILENAME__,__LINE__)) ;
}

void Mesh::deleteAll()
{
    if (this->size()==0) throw(Exception("Nothing to delete with Mesh::deleteAll"
                                ,__FILENAME__,__LINE__)) ;
    while (this->size()>0) this->deleteNode();
}

bool Mesh::isInit() const
{
    return init_ ;
}

void Mesh::setInit(bool init)
{
    init_ = init ;
}

bool Mesh::isDetect() const
{
    return detect_ ;
}

void Mesh::setDetect(bool detect)
{
    detect_ = detect ;
}

Polygon Mesh::getPolygon()
{
    return polygon_ ;
}

void Mesh::setPolygon(Polygon polygon)
{
    polygon_ = polygon ;
}

double Mesh::getStep()
{
    return step_ ;
}

void Mesh::setStep(double step)
{
    if (step > 0.) step_ = step ;
    else throw(Exception("Wrong value of step argument in Mesh::setStep",
                                __FILENAME__,__LINE__)) ;
}

std::vector<int> Mesh::getDim() const
{
    if (!this->isInit()) 
        Exception::logWarning("Mesh::getDim returns a wrong value",__FILENAME__,__LINE__);
    return dim_ ;
}

void Mesh::setDim(std::vector<int> dim)
{
    if (dim[0]*dim[1]==this->size()) dim_ = dim ;
    else Exception::logWarning("Argument does not suit in Mesh::setDim",
                                __FILENAME__,__LINE__) ;
}

void Mesh::setInitGrid()
{
    Polygon polygon(this->getPolygon());
    if (this->size()>0) this->deleteAll();
    double step(this->getStep());
    // Recherche des coordonnees extremes
    map<string,double> coord(polygon.getBottom());
    // Definition des vecteurs de la grille
    int nx = static_cast<int>(floor(abs(coord["xmax"]-coord["xmin"])/step));
    int ny = static_cast<int>(floor(abs(coord["ymax"]-coord["ymin"])/step));
    // Construction de la grille
    Point point(0.,2);
    for(int i=0; i<(ny+3); i++) { // Boucle sur les y
        point[1] = coord["ymin"]+(i-1)*step;
        for(int j=0; j<(nx+3); j++) { // Boucle sur les x
            point[0] = coord["xmin"]+(j-1)*step;
            Node node(point);
            this->addNode(node);
        }
    }
    // Test sur le point d'arrivee
    if (abs(coord["xmax"]+step-point[0])>GEOM_TOLERANCE || abs(coord["ymax"]+step-point[1])>GEOM_TOLERANCE)
        Exception::logWarning("Corrupted initial grid in Mesh::setInitGrid",
                                __FILENAME__,__LINE__);
    this->setInit(true);
    // Enregistrement des dimensions de la grille
    vector<int> dim;
    dim.push_back(nx+3);
    dim.push_back(ny+3);
    this->setDim(dim);
}

void Mesh::detectNode()
{
    Polygon polygon(this->getPolygon());
    int size(this->size());
    int size_p(polygon.size());
    double step(this->getStep());
    
    for(int i=0; i<size; i++) {
        Point point((*this)[i].getPosition());

        if (polygon.isInside(point)) {
            (*this)[i].setInside(true);
            
            for(int j=0; j<size_p; j++) { 

                if (polygon[j].getMinDist(point) < step) {
                    (*this)[i].setNearEdge(true);
                    break;
                }
            }
        }
    }
    this->setDetect(true);
}