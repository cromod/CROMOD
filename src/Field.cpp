/** 
 * @file Field.cpp
 * @brief Source file of Field class
 * @author cromod
 * @date september 2015
 */

#include "Field.hpp"
#include "Exception.hpp"
#include <cmath>
#include <iostream>

using namespace Cromod::GeomAPI;
using namespace Cromod::FieldAPI;
using namespace Cromod::Tools;
using namespace std;

Field::Field() : mesh_(),
                 listValue_(),
                 computed_(false)
{
}

Field::~Field() {
}

Vector& Field::operator[](const unsigned int& i)
{
    if (this->size()>0) return listValue_[i];
    else throw(Exception("Nothing to get with Field::operator[]"
                                 ,__FILENAME__,__LINE__)) ;
}

unsigned int Field::size()
{
    return listValue_.size();
}

Mesh Field::getMesh() const
{
    return mesh_;
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

bool Field::isComputed() const
{
    return computed_;
}

vector<Vector> Field::getListValue() const
{
    return listValue_;
}

map<Around,Node> Field::getNodesAround(const Node &node)
{
    int index = mesh_.index(node);
    vector<int> dim = mesh_.getDim();
    if (!mesh_[index].isInside())
        throw(Exception("Impossible to use Field::getNodesAround (Node object not inside)"
                                ,__FILENAME__,__LINE__)) ;
    
    map<Around,Node> around;
    around[UP]    = mesh_[index+dim[0]];
    around[DOWN]  = mesh_[index-dim[0]];
    around[RIGHT] = mesh_[index+1];
    around[LEFT]  = mesh_[index-1];
    return around;
}

map<Around,int> Field::getNodesAround(int index)
{
    vector<int> dim = mesh_.getDim();
    if (!mesh_[index].isInside())
        throw(Exception("Impossible to use Field::getNodesAround (Node object not inside)"
                                ,__FILENAME__,__LINE__)) ;
    
    map<Around,int> around;
    around[UP]    = index+dim[0];
    around[DOWN]  = index-dim[0];
    around[RIGHT] = index+1;
    around[LEFT]  = index-1;
    return around;
}

void Field::build(const Mesh &mesh, int dim)
{
    if ( !(mesh.isInit() && mesh.isDetect()) )
        Exception::logWarning("Mesh argument of Field::build is not complete",__FILENAME__,__LINE__);
    mesh_ = mesh;
    int size = mesh_.size();
    Vector inf(VAL_INFINITY,dim);
    vector<Vector> listValue(size,inf);
    listValue_ = listValue;
    computed_ = false;
}

double Field::computeRelErr(double val1, double val2)
{
    if(val1!=0.) return abs(1.-val2/val1);
    else if(val2!=0.) return abs(1.-val1/val2);
    else return 0.;
}

Vector Field::bilinearInt(vector<Point> listPts, vector<Vector> listVal, Point point)
{
      Polygon pol(listPts);
      if( pol.isInside(point) )
      {
          double x = (point[0]-listPts[0][0])/(listPts[1][0]-listPts[0][0]);
          double y = (point[1]-listPts[0][1])/(listPts[2][1]-listPts[0][1]);
          Vector a00, a10, a01, a11, val;
          a00 = listVal[0];
	  //cout << a00[0] << endl;
          a10 = listVal[1]; a10 -= listVal[0];
          a10 *= x;
	  //cout << a10[0] << endl;
          a01 = listVal[3]; a01 -= listVal[0];
          a01 *= y;
	  //cout << a01[0] << endl;
          a11 = listVal[2]; a11 -= listVal[0]; a11 -= listVal[3]; a11 += listVal[1];
          a11 *= x*y;
	  //cout << a11[0] << endl;
	  val = a00; val += a10; val += a01; val += a11;
          return val;
      }
      else throw(Exception("Impossible to use Field::BilinearInt (point outside area)"
                                   ,__FILENAME__,__LINE__)) ;
}

Vector Field::renorm(Vector vec)
{
    double norm = 0.;
    for(unsigned int i=0; i<vec.size(); i++) norm += pow(vec[i],2.);
    norm = sqrt(norm);
    if( norm > VAL_TOLERANCE ) vec /= norm;
    else vec *= 0.;
    return vec;
}