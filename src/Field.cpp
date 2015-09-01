/** 
 * @file Field.cpp
 * @brief Source file of Field class
 * @author cromod
 * @date september 2015
 */

#include "Field.hpp"
#include "Exception.hpp"

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
}

Field::Field(const Mesh& mesh)
{
    mesh_ = mesh;
}

Field::~Field() {
}

Vector& Field::operator[](const unsigned int& i)
{
    if (this->size()>0) return listValue_[i];
    else throw(Exception("Nothing to get with Field::operator[]"
                                 ,__FILE__,__LINE__)) ;
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
                                ,__FILE__,__LINE__)) ;
}

void Field::deleteAll()
{
    if (this->size()==0) throw(Exception("Nothing to delete with Field::deleteAll"
                                ,__FILE__,__LINE__)) ;
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
    
}

Vector Field::getValue(const Node &node) const
{
    
}