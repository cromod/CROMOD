/* 
 * File:   Polygon.cpp
 * Author: florent
 * 
 * Created on 25 juin 2015, 20:22
 */

#include "Constants.hpp"
#include "Segment.hpp"
#include "Polygon.hpp"
#include "Exception.hpp"
#include <list>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace Cromod::GeomAPI;
using namespace Cromod::Tools;
using namespace std;

Polygon::Polygon()
{
}

Polygon::Polygon(const Polygon& polygon) 
{
    listSeg_ = polygon.listSeg_ ;
}

Polygon::Polygon(const vector<Point>& listPoints) 
{
    unsigned int size = listPoints.size();    
    Segment segment;
    
    if (size > 0) {
        for(int i=0; i<size; i++) {
            if (i < size-1) segment.setPoints(listPoints[i],listPoints[i+1]);
            else if (i == size-1) segment.setPoints(listPoints[i],(*this)[0].getOne());
            if (segment.isSegment()) this->addSegment(segment);
        }
    }
    else Exception::logWarning("Empty list of Point type in Polygon constructor"
                                ,__FILE__,__LINE__);
}

Polygon::~Polygon() 
{
}

Segment& Polygon::operator[](const unsigned int& i)
{
    if (this->size()>0) return listSeg_[i];
    else throw(Exception("Nothing to get with Polygon::operator[]"
                                 ,__FILE__,__LINE__)) ;
}

Polygon& Polygon::operator=(const Polygon &polygon)
{
    listSeg_ = polygon.listSeg_ ;
}

unsigned int Polygon::size()
{
    return listSeg_.size();
}

void Polygon::addSegment(Segment seg)
{
    if (this->size()>0) {
        Point point1 = listSeg_.back().getTwo();
        Point point2 = seg.getOne();
        Segment seg_test(point1,point2);
        if (seg_test.getLength()>GEOM_TOLERANCE) {
            throw(Exception("Non-adjacent Segment argument in Polygon::addSegment"
                                ,__FILE__,__LINE__)) ;
        }
        else {
            seg.setOne(point1);
            listSeg_.push_back(seg);
        } 
    }
    else listSeg_.push_back(seg);
}

void Polygon::delSegment()
{
    if (this->size()>0) listSeg_.pop_back();
    else throw(Exception("Nothing to delete with Polygon::delSegment"
                                ,__FILE__,__LINE__)) ;
}

void Polygon::deleteAll()
{
    if (this->size()==0) throw(Exception("Nothing to delete with Polygon::deleteAll"
                                ,__FILE__,__LINE__)) ;
    while (this->size()>0) this->delSegment();
}

void Polygon::addPoint(const Point& point)
{
    if (listSeg_.size()>0) {
        Point point_back = listSeg_.back().getTwo();
        Segment new_seg(point_back,point);
        listSeg_.push_back(new_seg);
    }
    else {
        throw(Exception("Adding a Point type is impossible with Polygon::addPoint"
                                ,__FILE__,__LINE__)) ;
    }
}

vector<Segment> Polygon::getList()
{
    return listSeg_;
}

void Polygon::setList(const vector<Segment>& listSeg)
{
    listSeg_ = listSeg;
}

bool Polygon::isClosed()
{
    Polygon pol(*this);
    unsigned int size = pol.size();
    
    if (size == 0) {
        Exception::logWarning("No Segment object in Polygon",__FILE__,__LINE__);
        return false;
    }
    
    if (pol[size-1].getTwo()!=pol[0].getOne()) return false;
    
    for(int i=0 ; i<(size-1) ; i++) {
        if (pol[i].getTwo()!=pol[i+1].getOne()) return false;
    }

    return true;
}

void Polygon::close()
{
    unsigned int size = this->size();
    
    if (size > 0) {
        Segment segment((*this)[size-1].getTwo(),(*this)[0].getOne());
        if (segment.getLength()>GEOM_TOLERANCE) this->addSegment(segment);
    }
    else Exception::logWarning("Nothing to close with Polygon::close"
                                ,__FILE__,__LINE__);
}

vector<Point> Polygon::getPoints()
{
    unsigned int size = this->size();
    vector<Point> listPoints;
    
    for(int i=0; i<size; i++) {
        listPoints.push_back((*this)[i].getOne());
    }

    if (!(this->isClosed())) {
        Exception::logWarning("Using Polygon::getPoints with unclosed Polygon object"
                                ,__FILE__,__LINE__);
        listPoints.push_back((*this)[size-1].getTwo());
    }
    
    return listPoints;
}

Point Polygon::getOutside()
{  
    double pt[] = {INFINITY,0.};
    Point point(pt,2);
    return point;
}

map<string,double> Polygon::getBottom()
{
    unsigned int size = this->size();
    if ( size == 0 ) {
        throw(Exception("Nothing to get with Polygon::getBottom"
                                ,__FILE__,__LINE__)) ;
    }
    
    vector<Point> list = this->getPoints();
    double xmax(list[0][0]), xmin(list[0][0]);
    double ymax(list[0][1]), ymin(list[0][1]);
    
    for(vector<Point>::iterator pt=list.begin(); pt!=list.end(); ++pt) {
        xmax = max(xmax,(*pt)[0]);
        xmin = min(xmin,(*pt)[0]);
        ymax = max(ymax,(*pt)[1]);
        ymin = min(ymin,(*pt)[1]);
    }

    map<string,double> coord;
    coord["xmax"]=xmax;
    coord["xmin"]=xmin;
    coord["ymax"]=ymax;
    coord["ymin"]=ymin;
    return coord;
}

bool Polygon::isSelfIntersect()
{
    Polygon pol(*this);
    if (!pol.isClosed()) {
        throw(Exception("Polygon object is not closed in Polygon::isSelfIntersect"
                                ,__FILE__,__LINE__)) ;
    }
    
    unsigned int size = pol.size();
    if ( size < 2 ) {
        throw(Exception("Nothing to check with Polygon::isSelfIntersect"
                                ,__FILE__,__LINE__)) ;
    }
    
    for(int i=0; i<size; i++) {
        list<int> listIndex;
        for(int j=0; j<size; j++) listIndex.push_back(j);
        listIndex.remove(i);
        
        if (i>0 && i<(size-1)) {
            listIndex.remove(i-1);
            listIndex.remove(i+1);
        }
        else if (i==0) {
            listIndex.remove(1);
            listIndex.remove(size-1);
        }
        else if (i==size-1) {
            listIndex.remove(0);
            listIndex.remove(i-1);
        }
        
        for(list<int>::iterator it=listIndex.begin(); it!=listIndex.end(); ++it) {
            if ((pol[i]).checkIntersect(pol[*it])) return true;
        }
    }
    
    return false;
}

int Polygon::getNbIntersect(const Segment& segment)
{
    int nb_int(0);
    Polygon pol(*this);
    unsigned int size = pol.size();
    bool intersect;
    bool intersect_next;
    
    for(int i=0; i<size; i++) {
        intersect = pol[i].checkIntersect(segment) && !(pol[i].checkParallel(segment));
        if (i<size-1) {
            intersect_next = pol[i+1].checkIntersect(segment) && !(pol[i+1].checkParallel(segment));
        }
        else {
            intersect_next = pol[0].checkIntersect(segment) && !(pol[0].checkParallel(segment));
        }
        if ( intersect && !intersect_next )
            nb_int += 1;
    }
    
    return nb_int;
}

bool Polygon::isOnEdge(const Point& point)
{
    Polygon pol(*this);
    unsigned int size = pol.size();
    
    for(int i=0; i<size; i++) {
        if ( pol[i].checkInclude(point) ) return true;
    }
    
    return false;
}

bool Polygon::isInside(const Point& point_in)
{
    Point point_out = this->getOutside();
    Segment segment(point_in,point_out);
    if (this->isOnEdge(point_in)) {
        //cout << "On edge" << endl;
        return true;
    }
    else if ( (this->getNbIntersect(segment)) % 2 != 0 ) {
        //cout << "Nb of intersection = " << this->getNbIntersect(segment) << endl;
        return true;
    }
    else return false;
}