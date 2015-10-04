/** 
 * @file Vector.cpp
 * @brief Source file of Vector class
 * @author cromod
 * @date july 2015
 */

#include "Vector.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI;
using namespace Cromod::Tools;
using namespace std;

Vector::Vector(): valarray()
{
}

Vector::Vector(const double& val,size_t n): valarray(val,n)
{
}

Vector::Vector(const double* val,size_t n): valarray(val,n)
{
}

Vector::Vector(const valarray<double>& vec): valarray(vec)
{
}

bool Vector::operator==(const Vector& vec) const
{
    if (this->size()!=vec.size()) return false;
    bool val(true);
    for(unsigned int i=0;i<vec.size();i++) val&=((*this)[i]==vec[i]);
    return val;    
}

bool Vector::operator!=(const Vector& vec) const
{
    return !(*this==vec);    
}

Vector Cromod::GeomAPI::crossProd(const Vector& vec1, const Vector& vec2)
{
    if(vec1.size()!=vec2.size())
        throw(Exception("Not same dimension of vectors in crossProd function",__FILENAME__,__LINE__)) ;
    if(vec1.size()!=3)
        throw(Exception("Not three-dimensionnal vectors in crossProd function",__FILENAME__,__LINE__)) ;
    
    double x = vec1[2]*vec2[3] - vec1[3]*vec2[2];
    double y = vec1[3]*vec2[1] - vec1[1]*vec2[3];
    double z = vec1[1]*vec2[2] - vec1[2]*vec2[1];
    
    double list[] = {x,y,z};
    Vector vec(list,3);
    return vec;
}

double Cromod::GeomAPI::dotProd(const Vector& vec1, const Vector& vec2)
{
    return (vec1*vec2).sum();
}