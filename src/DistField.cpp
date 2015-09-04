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

DistField::DistField(): Field()
{
}

DistField::DistField(const DistField& distfield)  
{
    mesh_ = distfield.mesh_;
    listValue_ = distfield.listValue_;
    if (mesh_.size() != listValue_.size())
        Exception::logWarning("DistField argument of DistField::DistField is not consistent",__FILE__,__LINE__);
}

DistField::DistField(const Mesh& mesh): Field(mesh)
{
}

DistField::~DistField() {
}

void DistField::setBoundaryCondition(Segment &segment)
{
    Polygon polygon = mesh_.getPolygon();
    int index = polygon.index(segment);
    segment.setExit(true);
    polygon[index] = segment;
    mesh_.setPolygon(polygon);
    
    int size = this->size();
    double step = this->getStep();
    for(int i=0; i<size; i++) {
        if (segment.getMinDist(mesh_[i].getPosition())<step && mesh_[i].isInside()) {
            //(*this)[i].setStatus([True,False]);
            Vector value(0.,1);
            (*this).setValue(mesh_[i],value);
        }
    }
}