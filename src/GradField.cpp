/** 
 * @file GradField.cpp
 * @brief Source file of GradField class
 * @author cromod
 * @date september 2015
 */

#include "GradField.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI;
using namespace Cromod::FieldAPI;
using namespace Cromod::Tools;
using namespace std;

GradField::GradField(): Field()
{
}

GradField::GradField(const GradField& gradfield)  
{
    mesh_ = gradfield.mesh_;
    listValue_ = gradfield.listValue_;
    if (mesh_.size() != listValue_.size())
        Exception::logWarning("GradField attributes are not consistent",__FILENAME__,__LINE__);
}

GradField::GradField(const DistField& distfield)
{
    if (!distfield.isComputed())
        throw(Exception("DistField argument not computed in GradField::GradField",__FILENAME__,__LINE__)) ; 
    this->Field::build(distfield.getMesh(),2);
    this->compute(distfield.getListValue());
}

GradField::~GradField() {
}

void GradField::compute(const vector<Vector>& listValue)
{
    if (listValue.size()!=this->size())
        throw(Exception("DistField argument not computed in GradField::GradField",__FILENAME__,__LINE__)) ; 
    Vector value(0.,2);
    map<Around,int> around;
    double x(0.),y(0.);
    bool flag(true);
    double step = this->getStep();
    
    for(unsigned int i=0; i<this->size(); i++)
    {
        if(mesh_[i].isInside())
        {
            around = this->getNodesAround(i);
            if( !mesh_[i].isNearEdge() )
            {
                x = (listValue[around[RIGHT]][0] - listValue[around[LEFT]][0])/(2.*step);
                y = (listValue[around[UP]][0] - listValue[around[DOWN]][0])/(2.*step);
            }
            else
            {
                flag = false;

                if( mesh_[around[UP]].isInside() && mesh_[around[DOWN]].isInside() )
                    y = (listValue[around[UP]][0] - listValue[around[DOWN]][0])/(2.*step);
                else if( (!mesh_[around[UP]].isInside()) && mesh_[around[DOWN]].isInside() )
                    y = (listValue[i][0] - listValue[around[DOWN]][0])/step;
                else if( mesh_[around[UP]].isInside() && (!mesh_[around[DOWN]].isInside()) )
                    y = (listValue[around[UP]][0] - listValue[i][0])/step;
                else flag = true;

                if( mesh_[around[RIGHT]].isInside() && mesh_[around[LEFT]].isInside() )
                    y = (listValue[around[RIGHT]][0] - listValue[around[LEFT]][0])/(2.*step);
                else if( (!mesh_[around[RIGHT]].isInside()) && mesh_[around[LEFT]].isInside() )
                    y = (listValue[i][0] - listValue[around[LEFT]][0])/step;
                else if( mesh_[around[RIGHT]].isInside() && (!mesh_[around[LEFT]].isInside()) )
                    y = (listValue[around[RIGHT]][0] - listValue[i][0])/step;
                else flag = true;

                if( abs(listValue[i][0]) < VAL_TOLERANCE ) flag = true;
                if(flag) {
                    x = 0.;
                    y = 0.; 
                }
            }
        }
        else {
            x = 0.;
            y = 0.;
        }
        value[0] = x;
        value[1] = y;
        (*this)[i] = value;
    }
    computed_ = true;
}

Vector GradField::interpolate(double x, double y)
{
    return this->Field::interpolate(x,y,2,0.);
}