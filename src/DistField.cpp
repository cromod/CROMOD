/** 
 * @file DistField.cpp
 * @brief Source file of DistField class
 * @author cromod
 * @date september 2015
 */

#include "DistField.hpp"
#include "Exception.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace Cromod::GeomAPI;
using namespace Cromod::FieldAPI;
using namespace Cromod::Tools;
using namespace std;

DistField::DistField(): Field(),
                        listStatus_()
{
}

DistField::DistField(const DistField& distfield)  
{
    mesh_ = distfield.mesh_;
    listValue_ = distfield.listValue_;
    computed_ = distfield.computed_;
    listStatus_ = distfield.listStatus_;
    if (mesh_.size() != listValue_.size() || mesh_.size() != listStatus_.size())
        Exception::logWarning("DistField attributes are not consistent",__FILENAME__,__LINE__);
}

DistField::DistField(const Mesh& mesh, vector<Segment> &listExit)
{
    this->build(mesh);
    if(!listExit.empty()) {
        for(unsigned int i=0; i<listExit.size(); i++)
            this->setBoundaryCondition(listExit[i]);
    }
    else throw(Exception("No boundary condition in DistField::DistField",__FILENAME__,__LINE__)) ;
    //cout << "Initializing field of distance..." << endl;
    this->initialize();
    //cout << "Computing field of distance..." << endl;
    this->compute();
    //cout << "Field of distance built" << endl;
}

DistField::~DistField() {
}

void DistField::setStatus(const Node &node, Status status)
{
    int index = mesh_.index(node);
    listStatus_[index] = status;
}

Status DistField::getStatus(const Node &node)
{
    int index = mesh_.index(node);
    return listStatus_[index];
}

void DistField::setStatus(int index, Status status)
{
    listStatus_[index] = status;
}

Status DistField::getStatus(int index)
{
    return listStatus_[index];
}

void DistField::setBoundaryCondition(Segment &segment)
{
    // Update mesh_ attribute to set boundary condition
    Polygon polygon = mesh_.getPolygon();
    int index = polygon.index(segment);
    segment.setExit(true);
    polygon[index] = segment;
    mesh_.setPolygon(polygon);
    
    // Distance value on boundary condition
    Vector value(0.,1);
    
    int size = this->size();
    double step = this->getStep();
    for(int i=0; i<size; i++) {
        if (segment.getMinDist(mesh_[i].getPosition())<step && mesh_[i].isInside()) {
            this->setStatus(i,FROZEN);
            (*this)[i] = value;
        }
    }
}

void DistField::build(const Mesh &mesh)
{
    this->Field::build(mesh,1);
    int size = mesh_.size();
    vector<Status> listStatus(size,UNKNOWN);
    listStatus_ = listStatus;
}

void DistField::initialize()
{
    int size = mesh_.size();
    
    Vector step(this->getStep(),1); // step value
    Vector inf(VAL_INFINITY,1); // infinity value

    for(int i=0; i<size; i++)
    {
        if (this->getStatus(i)==FROZEN) 
        {
            map<Around,int> around = this->getNodesAround(i);
            if (this->getStatus(around[UP])==UNKNOWN && mesh_[around[UP]].isInside()) {
                this->setStatus(around[UP],NARROW);
                (*this)[around[UP]] = step;
            }
            if (this->getStatus(around[DOWN])==UNKNOWN && mesh_[around[DOWN]].isInside()) {
                this->setStatus(around[DOWN],NARROW);
                (*this)[around[DOWN]] = step;
            }
            if (this->getStatus(around[RIGHT])==UNKNOWN && mesh_[around[RIGHT]].isInside()) {
                this->setStatus(around[RIGHT],NARROW);
                (*this)[around[RIGHT]] = step;
            }
            if (this->getStatus(around[LEFT])==UNKNOWN && mesh_[around[LEFT]].isInside()) {
                this->setStatus(around[LEFT],NARROW);
                (*this)[around[LEFT]] = step;
            }
        }
    }
}

void DistField::compute()
{
    int size = mesh_.size();
    
    double step(this->getStep());
    double min_val(0.);
    double d1(0.);
    double d2(0.);
    Vector dist(0.,1);
    
    bool flag = true;
    map<Around,int> around;
    
    while(flag)
    {
         vector<double> listVal;
         vector<int> listNode;
    
         for(int i=0; i<size; i++)
         {
             if( this->getStatus(i)==NARROW )
             {
                 around = this->getNodesAround(i);
                 d1 = min((*this)[around[RIGHT]][0],(*this)[around[LEFT]][0]);
                 d2 = min((*this)[around[UP]][0],(*this)[around[DOWN]][0]);
                 if( abs(d1-d2) < step ) dist[0] = ( d1+d2 + sqrt( 2.*pow(step,2.) - pow(d1-d2,2.) ) ) / 2.;
                 else dist[0] = min(d1,d2) + step;
                 listVal.push_back(dist[0]);
                 listNode.push_back(i);
                 (*this)[i] = dist;
             }
         }
         if( !listVal.empty() )
         {
             min_val = *min_element(listVal.begin(),listVal.end());
             for(unsigned int i=0; i<listVal.size(); i++)
             {
                 if( computeRelErr(listVal[i],min_val) < VAL_TOLERANCE )
                 {  
                     int index = listNode[i];
                     this->setStatus(index,FROZEN);
                     around = this->getNodesAround(index);
                     if( this->getStatus(around[RIGHT])==UNKNOWN && mesh_[around[RIGHT]].isInside() )
                         this->setStatus(around[RIGHT],NARROW);
                     if( this->getStatus(around[LEFT])==UNKNOWN && mesh_[around[LEFT]].isInside() )
                         this->setStatus(around[LEFT],NARROW);
                     if( this->getStatus(around[UP])==UNKNOWN && mesh_[around[UP]].isInside() )
                         this->setStatus(around[UP],NARROW);
                     if( this->getStatus(around[DOWN])==UNKNOWN && mesh_[around[DOWN]].isInside() )
                         this->setStatus(around[DOWN],NARROW);
                 }
             }
         }
         else flag = false;
    }
    computed_ = true;
}

Vector DistField::interpolate(double x, double y)
{
    return this->Field::interpolate(x,y,1,VAL_INFINITY);
}