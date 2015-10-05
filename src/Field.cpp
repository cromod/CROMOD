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

double Cromod::FieldAPI::computeRelErr(double val1, double val2)
{
    if(val1!=0.) return abs(1.-val2/val1);
    else if(val2!=0.) return abs(1.-val1/val2);
    else return 0.;
}

Vector Cromod::FieldAPI::renorm(Vector vec)
{
    double norm = 0.;
    for(unsigned int i=0; i<vec.size(); i++) norm += pow(vec[i],2.);
    norm = sqrt(norm);
    if( norm > VAL_TOLERANCE ) vec /= norm;
    else vec *= 0.;
    return vec;
}

Vector Cromod::FieldAPI::bilinearInt(vector<Point> listPts, vector<Vector> listVal, Point point)
{
      if(listPts.size()!=4 && listVal.size()!=4)
          throw(Exception("Need 4 points and 4 values to use Field::Bilinear"
                                   ,__FILENAME__,__LINE__)) ;
      Polygon pol(listPts);
      if( pol.isInside(point) )
      {
          double x = (point[0]-listPts[0][0])/(listPts[1][0]-listPts[0][0]);
          double y = (point[1]-listPts[0][1])/(listPts[2][1]-listPts[0][1]);
          Vector a00(listVal[0]);
          //cout << a00[0] << endl;
          Vector a10(listVal[1]-listVal[0]);
          //cout << a10[0] << endl;
          Vector a01(listVal[3]-listVal[0]);
          //cout << a01[0] << endl;
          Vector a11(listVal[2]+listVal[0]-listVal[3]-listVal[1]);
          //cout << a11[0] << endl;
          Vector val(a00+a10*x+a01*y+a11*x*y);
          return val;
      }
      else throw(Exception("Impossible to use Field::BilinearInt (point outside area)"
                                   ,__FILENAME__,__LINE__)) ;
}

Vector Cromod::FieldAPI::linearInt3Pts(vector<Point> listPts, vector<Vector> listVal, Point point)
{
    if(listPts.size()!=3 && listVal.size()!=3)
        throw(Exception("Need 3 points and 3 values to use Field::linear3DInt"
                                   ,__FILENAME__,__LINE__)) ;

    double x1(listPts[0][0]),y1(listPts[0][1]);
    Vector z1(listVal[0]);
    double x2(listPts[1][0]),y2(listPts[1][1]);
    Vector z2(listVal[1]);
    double x3(listPts[2][0]),y3(listPts[2][1]);
    Vector z3(listVal[2]);
    
    Vector nx((y2-y1)*(z3-z1)-(z2-z1)*(y3-y1));
    Vector ny((z2-z1)*(x3-x1)-(x2-x1)*(z3-z1));
    double nz((x2-x1)*(y3-y1)-(y2-y1)*(x3-x1));
    if(abs(nz)<GEOM_TOLERANCE)
        throw(Exception("3 colinear points in Field::linear3DInt",__FILENAME__,__LINE__)) ;

    Vector val(z1-(point[0]-x1)/nz*nx-(point[1]-y1)/nz*ny);
    return val;
}

Vector Cromod::FieldAPI::linearInt2Pts(vector<Point> listPts, vector<Vector> listVal, Point point)
{
    if(listPts.size()!=2 && listVal.size()!=2)
        throw(Exception("Need 2 points and 2 values to use Field::linear2DInt"
                                   ,__FILENAME__,__LINE__)) ;

    Vector valA(listVal[0]);
    Vector valB(listVal[1]);
    Segment AB(listPts[0],listPts[1]);
    double lAB = AB.getLength();
    Segment AM(listPts[0],point);
    double lAM = AM.getLength();    

    Vector val(valA*(1.-lAM/lAB)+valB*lAM/lAB);
    return val;
}
