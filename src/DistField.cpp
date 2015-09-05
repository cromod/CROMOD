/** 
 * @file DistField.cpp
 * @brief Source file of DistField class
 * @author cromod
 * @date september 2015
 */

#include "DistField.hpp"
#include "Exception.hpp"

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
        Exception::logWarning("DistField attributes are not consistent",__FILE__,__LINE__);
}

DistField::DistField(const Mesh& mesh): Field(mesh)
{
    mesh_ = mesh;
    int size = mesh_.size();
    vector<bool> status(2,false);
    vector< vector<bool> > listStatus(size,status);
    listStatus_ = listStatus;
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
            if (this->getStatus(around["haut"])==unknown and around["haut"].isInside()) {
                this->setStatus(around["haut"],narrow);
                this->setValue(around["haut"],step);
            }
            if (this->getStatus(around["bas"])==unknown and around["bas"].isInside()) {
                this->setStatus(around["bas"],narrow);
                this->setValue(around["bas"],step);
            }
            if (this->getStatus(around["droite"])==unknown and around["droite"].isInside()) {
                this->setStatus(around["droite"],narrow);
                this->setValue(around["droite"],step);
            }
            if (this->getStatus(around["gauche"])==unknown and around["gauche"].isInside()) {
                this->setStatus(around["gauche"],narrow);
                this->setValue(around["gauche"],step);
            }
        }
        else if (this->getStatus(mesh_[i])==unknown) this->setValue(mesh_[i],inf);
    }
}