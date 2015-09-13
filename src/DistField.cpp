/** 
 * @file DistField.cpp
 * @brief Source file of DistField class
 * @author cromod
 * @date september 2015
 */

#include "DistField.hpp"
#include "Exception.hpp"
#include "Constants.hpp"
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
    listStatus_ = distfield.listStatus_;
    if (mesh_.size() != listValue_.size() || mesh_.size() != listStatus_.size())
        Exception::logWarning("DistField attributes are not consistent",__FILENAME__,__LINE__);
}

DistField::DistField(const Mesh& mesh)
{
    this->build(mesh);
}

DistField::~DistField() {
}

void DistField::setStatus(const Node &node, const vector<bool> &status)
{
    int index = mesh_.index(node);
    listStatus_[index] = status;
}

vector<bool> DistField::getStatus(const Node &node)
{
    int index = mesh_.index(node);
    return listStatus_[index];
}

void DistField::setBoundaryCondition(Segment &segment)
{
    Polygon polygon = mesh_.getPolygon();
    int index = polygon.index(segment);
    segment.setExit(true);
    polygon[index] = segment;
    mesh_.setPolygon(polygon);
    
    vector<bool> frozen(2,false);
    frozen[0] = true;
    Vector value(0.,1);
    
    int size = this->size();
    double step = this->getStep();
    for(int i=0; i<size; i++) {
        if (segment.getMinDist(mesh_[i].getPosition())<step && mesh_[i].isInside()) {
            this->setStatus(mesh_[i],frozen);
            this->setValue(mesh_[i],value);
        }
    }
}

void DistField::build(const Mesh &mesh)
{
    this->Field::build(mesh);
    int size = mesh_.size();
    vector<bool> status(2,false);
    vector< vector<bool> > listStatus(size,status);
    listStatus_ = listStatus;
}

void DistField::initialize()
{
    int size = mesh_.size();
    
    Vector step(this->getStep(),1); // step value
    Vector inf(INFINITY,1); // infinity value
    
    // Definition of status possibilities
    vector<bool> unknown(2,false);
    vector<bool> frozen(unknown);
    frozen[0] = true;
    vector<bool> narrow(unknown);
    narrow[1] = true;

    for(int i=0; i<size; i++)
    {
        if (this->getStatus(mesh_[i])==frozen) 
        {
            map<string,Node> around = this->getNodesAround(mesh_[i]);
            if (this->getStatus(around["up"])==unknown && around["up"].isInside()) {
                this->setStatus(around["up"],narrow);
                this->setValue(around["up"],step);
            }
            if (this->getStatus(around["down"])==unknown && around["down"].isInside()) {
                this->setStatus(around["down"],narrow);
                this->setValue(around["down"],step);
            }
            if (this->getStatus(around["right"])==unknown && around["right"].isInside()) {
                this->setStatus(around["right"],narrow);
                this->setValue(around["right"],step);
            }
            if (this->getStatus(around["left"])==unknown && around["left"].isInside()) {
                this->setStatus(around["left"],narrow);
                this->setValue(around["left"],step);
            }
        }
        else if (this->getStatus(mesh_[i])==unknown) this->setValue(mesh_[i],inf);
    }
}

void DistField::compute()
{
    int size = mesh_.size();
    double step(this->getStep());
    bool flag = true;
    double min_val(0.);
    
    // Definition of status possibilities
    vector<bool> unknown(2,false);
    vector<bool> frozen(unknown);
    frozen[0] = true;
    vector<bool> narrow(unknown);
    narrow[1] = true;
    
    Vector vect(0.,1);
    vector<double> listVal;
    vector<Node> listNode;
    
    while(flag)
    {
         listVal.clear();
         listNode.clear();
    
         for(int i=0; i<size; i++)
         {
             if( this->getStatus(mesh_[i])==narrow )
             {
                 map<string,Node> around = this->getNodesAround(mesh_[i]);
                 double d1 = min(this->getValue(around["right"])[0],this->getValue(around["left"])[0]);
                 double d2 = min(this->getValue(around["up"])[0],this->getValue(around["down"])[0]);
                 double dist;
                 if( abs(d1-d2) < step ) dist = ( d1+d2 + sqrt( 2.*pow(step,2.) - pow(d1-d2,2.) ) ) / 2.;
                 else dist = min(d1,d2) + step;
                 listVal.push_back(dist);
                 listNode.push_back(mesh_[i]);
                 vect[0] = dist;
                 this->setValue(mesh_[i],vect);
             }
         }
         cout << listVal.size() << endl;
         if( !listVal.empty() )
         {
             min_val = *min_element(listVal.begin(),listVal.end());
             for(int i=0; i<listVal.size(); i++)
             {
                 if( Field::computeRelErr(listVal[i],min_val) < VAL_TOLERANCE )
                 {  
                     Node node = listNode[i];
                     this->setStatus(node,frozen);
                     map<string,Node> around = this->getNodesAround(node);
                     if( this->getStatus(around["right"])==unknown && around["right"].isInside() )
                         this->setStatus(around["right"],narrow);
                     if( this->getStatus(around["left"])==unknown && around["left"].isInside() )
                         this->setStatus(around["left"],narrow);
                     if( this->getStatus(around["up"])==unknown && around["up"].isInside() )
                         this->setStatus(around["up"],narrow);
                     if( this->getStatus(around["down"])==unknown && around["down"].isInside() )
                         this->setStatus(around["down"],narrow);
                 }
             }
         } 
         else flag = false;
    }
}

double DistField::interpolate(double x, double y)
{
    double step(this->getStep());
    Mesh mesh(this->getMesh());
    double pt[] = {x,y};
    Point point(pt,2);
    Polygon polygon(mesh.getPolygon());
    map<string,double> coord(polygon.getBottom());

    int nx = mesh.getDim()[0];
    int index = static_cast<int>((x-coord["xmin"])/step+1.)
                  + static_cast<int>((y-coord["ymin"])/step+1.)*nx;

    if(polygon.isInside(point))
    {
        Segment seg(point,mesh[index].getPosition());
        if( seg.getLength() < step*sqrt(2.) )
        {
            vector<Point> listPts;
            listPts.push_back(mesh[index].getPosition());
            listPts.push_back(mesh[index+1].getPosition());
            listPts.push_back(mesh[index+1+nx].getPosition());
            listPts.push_back(mesh[index+nx].getPosition());
            Polygon square(listPts);
            if(square.isInside(point))
            {
                vector<double> listVal;  
                listVal.push_back(this->getValue(mesh[index])[0]); 
                listVal.push_back(this->getValue(mesh[index+1])[0]); 
                listVal.push_back(this->getValue(mesh[index+1+nx])[0]); 
                listVal.push_back(this->getValue(mesh[index+nx])[0]); 
		for(vector<double>::iterator l=listVal.begin(); l!=listVal.end(); ++l) cout << *l << endl;
                double val = Field::bilinearInt(listPts,listVal,point);
                if( val < 0. ) val = 0.;
                return val;
            }
            else return INFINITY;
        }
        else return INFINITY;
    }
    else return INFINITY;
}