/** 
 * @file Vector.cpp
 * @brief Source file of Vector class
 * @author cromod
 * @date july 2015
 */

#include "Vector.hpp"

using namespace Cromod::GeomAPI;
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
