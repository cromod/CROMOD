/** 
 * @file Segment.cpp
 * @brief Source file of Segment class
 * @author cromod
 * @date june 2015
 */

#include "Constants.hpp"
#include "Segment.hpp"
#include "Exception.hpp"
#include <cmath>
#include <iostream>

using namespace Cromod::GeomAPI;
using namespace Cromod::Tools;
using namespace std ;

Segment::Segment() : point1_(0.,2), 
                     point2_(0.,2),
                     exit_(false)
{
}

Segment::Segment(const Segment& seg)
{
    point1_ = seg.point1_ ;
    point2_ = seg.point2_ ;
    exit_ = seg.exit_ ;
}

Segment::Segment(const Point &point1, const Point &point2, const bool &exit)
{
    if (point1.size()!=2 || point2.size()!=2) 
        throw(Exception("Wrong vector<double> size in Segment::Segment",__FILE__,__LINE__)) ;
    point1_ = point1 ;
    point2_ = point2 ;
    exit_ = exit ;
}

Segment::~Segment() {
}

bool Segment::operator==(const Segment &seg) const
{
    return (this->getOne()==seg.getOne() && this->getTwo()==seg.getTwo()) ;
}

bool Segment::operator!=(const Segment &seg) const
{
    return !(*this==seg) ;
}

Segment& Segment::operator=(const Segment &seg)
{
    point1_ = seg.point1_ ;
    point2_ = seg.point2_ ;
    exit_ = seg.exit_ ;
}

void Segment::setExit(bool exit)
{
    exit_ = exit ;
}

bool Segment::isExit() const
{
    return exit_ ;
}

void Segment::setOne(Point point1)
{
    if (point1.size()!=2) 
        throw(Exception("Wrong argument size in Segment::setOne",__FILE__,__LINE__)) ;
    point1_ = point1 ;
}

Point Segment::getOne() const
{
    return point1_ ;
}

void Segment::setTwo(Point point2)
{
    if (point2.size()!=2) 
        throw(Exception("Wrong argument size in Segment::setTwo",__FILE__,__LINE__)) ;
    point2_ = point2 ;
}

Point Segment::getTwo() const
{
    return point2_ ;
}

void Segment::setPoints(Point point1,Point point2)
{
    if (point1.size()!=2 || point2.size()!=2) 
        throw(Exception("Wrong argument size in Segment::setPoints",__FILE__,__LINE__)) ;
    this->setOne(point1) ;
    this->setTwo(point2) ;
}

vector<Point> Segment::getPoints() const
{
    vector<Point> points ;
    points.push_back(this->getOne()) ;
    points.push_back(this->getTwo()) ;
    return points ;
}

Vector Segment::getVector() const
{
    Point point1(this->getOne()) ;
    Point point2(this->getTwo()) ;
    Vector vec(point2-point1) ;
    return vec ;
}

double Segment::getLength() const
{
    Vector vec(this->getVector()) ;
    return sqrt(pow(vec[0],2)+pow(vec[1],2)) ;
}

bool Segment::isSegment() const
{
    return (this->getOne()!=this->getTwo()) ;
    //return (this->getLength()>GEOM_TOLERANCE);
}

double Segment::orientation(const Point &pointA, 
                            const Point &pointB, 
                            const Point &pointC)
{
    return ( (pointB[0]-pointA[0])*(pointC[1]-pointA[1]) 
            - (pointC[0]-pointA[0])*(pointB[1]-pointA[1]) );
}

bool Segment::checkIntersect(const Segment &seg) const
{
    double orient1 = orientation(this->getOne(),this->getTwo(),seg.getOne()) * 
                        orientation(this->getOne(),this->getTwo(),seg.getTwo());
    double orient2 = orientation(seg.getOne(),seg.getTwo(),this->getOne()) * 
                        orientation(seg.getOne(),seg.getTwo(),this->getTwo());
    return !( orient1>0. || orient2>0. );
}

bool Segment::checkParallel(const Segment &seg) const
{
    Vector vect1(this->getVector());
    Vector vect2(seg.getVector());
    double prod(vect1[0]*vect2[1]-vect1[1]*vect2[0]);
    return (abs(prod) < GEOM_TOLERANCE);
}

bool Segment::checkInclude(const Point &pointB) const
{
    Point pointA = this->getOne();
    Point pointC = this->getTwo();
    Segment AB(pointA,pointB);
    Segment AC(pointA,pointC);
    
    if (AB.checkParallel(AC)) {
        Vector vAB = AB.getVector();
        Vector vAC = AC.getVector();
    
        Vector vNull(2,0.);
        double coef;
        if (vAC==vNull && vAB==vNull) coef = 1.;
        else if (vAC[0]!=0.) coef = vAB[0]/vAC[0];
        else if (vAC[1]!=0.) coef = vAB[1]/vAC[1];
        else coef = 2.;
        
        return (0.<=coef && coef<=1.);
    }
    else return false;
}

Point Segment::findPerPoint(const Point &pointC) const
{
    Segment AB(*this);
    Point pointA = AB.getOne();
    Segment AC(pointA,pointC);
    
    // C appartient a (AB)
    if (AB.checkParallel(AC)) return pointC;
    
    // Calcul des coordonnees du point
    Vector vAB = AB.getVector();
    Vector vAC = AC.getVector();
    double nAB = AB.getLength(); // norme du vecteur AB
    double dot_prod = (vAB*vAC).sum(); // produit scalaire AB.AC
    double coef = dot_prod/pow(nAB,2);
    Vector vAH(coef*vAB);
    Point pointH(vAH+pointA);
    return pointH;
}

double Segment::getMinDist(const Point &point)
{
    Point proj = this->findPerPoint(point);
    if (this->checkInclude(proj)) {
        Segment perp(point,proj);
        return perp.getLength();
    }
    else {
        Point pointA = this->getOne();
        Point pointB = this->getTwo();
        Segment segA(pointA,point);
        Segment segB(pointB,point);
        return min(segA.getLength(),segB.getLength());
    }
}
