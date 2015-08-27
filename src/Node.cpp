/* 
 * File:   Node.cpp
 * Author: florent
 * 
 * Created on 6 juillet 2015, 21:21
 */

#include "Node.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI;
using namespace Cromod::Tools;
using namespace std;

Node::Node() : point_(0.,2), 
               near_(false),
               inside_(false),
               value_(),
               status_(false,2)
{
}

Node::Node(const Node& node) 
{
    if (node.point_.size()!=2) 
        throw(Exception("Wrong vector<double> size in Node::Node",__FILE__,__LINE__)) ;
    point_ = node.point_;
    near_ = node.near_;
    inside_ = node.inside_;
    value_ = node.value_;
    status_ = node.status_;
}

Node::Node(const Point& point, bool near, bool inside) : value_(),status_(false,2)
{
    if (point.size()!=2) 
        throw(Exception("Wrong vector<double> size in Node::Node",__FILE__,__LINE__)) ;
    point_ = point;
    near_ = near;
    inside_ = inside;
}

Node::~Node() {
}

bool Node::operator==(const Node &node) const
{
    return (this->getPosition() == node.getPosition());
}

bool Node::operator!=(const Node &node) const
{
    return !(*this== node);
}

Node& Node::operator=(const Node &node)
{
    if (node.point_.size()!=2) 
        throw(Exception("Wrong vector<double> size in Node::operator=",__FILE__,__LINE__)) ;
    point_ = node.point_;
    near_ = node.near_;
    inside_ = node.inside_;
}

void Node::setPosition(const Point &point)
{
    if (point.size()!=2) 
        throw(Exception("Wrong vector<double> size in Node::setPosition",__FILE__,__LINE__)) ;
    point_ = point;
}

Point Node::getPosition() const
{
    return point_;
}

void Node::setNearEdge(bool near)
{
    near_ = near;
}

bool Node::isNearEdge() const
{
    return near_;
}

void Node::setInside(bool inside)
{
    inside_ = inside;
}

bool Node::isInside() const
{
    return inside_;
}

void Node::setValue(const Vector &value)
{
    value_ = value;
}

Vector Node::getValue() const
{
    return value_;
}

void Node::setStatus(const vector<bool> &status)
{
    status_ = status;
}

vector<bool> Node::getStatus() const
{
    return status_;
}