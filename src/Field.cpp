/** 
 * @file Field.cpp
 * @brief Source file of Field class
 * @author cromod
 * @date september 2015
 */

#include "Field.hpp"
#include "Exception.hpp"
#include <iostream>

using namespace Cromod::GeomAPI;
using namespace Cromod::FieldAPI;
using namespace Cromod::Tools;
using namespace std;

Field::Field() : mesh_(),
                 listValue_()
{
}

Field::Field(const Field& field) 
{
    mesh_ = field.mesh_;
    listValue_ = field.listValue_;
    if (mesh_.size() != listValue_.size())
        Exception::logWarning("Field argument of Field::Field is not consistent",__FILENAME__,__LINE__);
}

Field::Field(const Mesh& mesh)
{
    this->build(mesh);
}

Field::~Field() {
}

Vector& Field::operator[](const unsigned int& i)
{
    if (this->size()>0) return listValue_[i];
    else throw(Exception("Nothing to get with Field::operator[]"
                                 ,__FILENAME__,__LINE__)) ;
}

Field& Field::operator=(const Field &field)
{
    mesh_ = field.mesh_;
    listValue_ = field.listValue_;
}

unsigned int Field::size()
{
    return listValue_.size();
}

void Field::delValue()
{
    if (this->size()>0) listValue_.pop_back();
    else throw(Exception("Nothing to delete with Field::delFNode"
                                ,__FILENAME__,__LINE__)) ;
}

void Field::deleteAll()
{
    if (this->size()==0) throw(Exception("Nothing to delete with Field::deleteAll"
                                ,__FILENAME__,__LINE__)) ;
    while (this->size()>0) this->delValue();
}

void Field::setMesh(const Mesh &mesh)
{
    mesh_ = mesh;
}

Mesh Field::getMesh() const
{
    return mesh_;
}

void Field::setStep(double step)
{
    Mesh mesh(this->getMesh());
    mesh.setStep(step);
    this->setMesh(mesh);
}

double Field::getStep() const
{
    return (this->getMesh()).getStep();
}

void Field::setValue(const Node &node, const Vector &value)
{
    int index = mesh_.index(node);
    (*this)[index] = value;
}

Vector Field::getValue(const Node &node)
{
    int index = mesh_.index(node);
    return (*this)[index];
}

map<string,Node> Field::getNodesAround(const Node &node)
{
    int index = mesh_.index(node);
    vector<int> dim = mesh_.getDim();
    if (!mesh_[index].isInside())
        throw(Exception("Impossible to use Field::getNodesAround (Node object not inside)"
                                ,__FILENAME__,__LINE__)) ;
    
    map<string,Node> around;
    around["up"]    = mesh_[index+dim[0]];
    around["down"]  = mesh_[index-dim[0]];
    around["right"] = mesh_[index+1];
    around["left"]  = mesh_[index-1];
    return around;
}

void Field::build(const Mesh &mesh)
{
    if ( !(mesh.isInit() && mesh.isDetect()) )
        Exception::logWarning("Mesh argument of Field::build is not complete",__FILENAME__,__LINE__);
    mesh_ = mesh;
    int size = mesh_.size();
    Vector inf(INFINITY,1);
    vector<Vector> listValue(size,inf);
    listValue_ = listValue;
}

double Field::computeRelErr(double val1, double val2)
{
    if(val1!=0.) return abs(1.-val2/val1);
    else if(val2!=0.) return abs(1.-val1/val2);
    else return 0.;
}

double Field::bilinearInt(vector<Point> listPts, vector<double> listVal, Point point)
{
      Polygon pol(listPts);
      if( pol.isInside(point) )
      {
          double x = (point[0]-listPts[0][0])/(listPts[1][0]-listPts[0][0]);
	  cout<< x << endl;
          double y = (point[1]-listPts[0][1])/(listPts[2][1]-listPts[0][1]);
	  cout<< y << endl;
          double a00 = listVal[0];
          double a10 = listVal[1] - listVal[0];
          double a01 = listVal[3] - listVal[0];
          double a11 = listVal[2] - listVal[0] - (listVal[3] - listVal[1]);
          return a00 + a10*x + a01*y + a11*x*y;
      }
      else throw(Exception("Impossible to use Field::BilinearInt (point outside area)"
                                   ,__FILENAME__,__LINE__)) ;
}