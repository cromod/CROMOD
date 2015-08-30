/** 
 * @file FNode.cpp
 * @brief Source file of FNode class
 * @author cromod
 * @date august 2015
 */

#include "FNode.hpp"
#include "Exception.hpp"

using namespace Cromod::GeomAPI;
using namespace Cromod::FieldAPI;
using namespace Cromod::Tools;
using namespace std;

FNode::FNode() : Node(),
                 value_(),
                 status_(false,2)
{
}

FNode::FNode(const FNode& fnode) 
{
    if (fnode.getPosition().size()!=2) 
        throw(Exception("Wrong vector<double> size in FNode::FNode",__FILE__,__LINE__)) ;
    point_ = fnode.getPosition();
    near_ = fnode.isNearEdge();
    inside_ = fnode.isInside();
    value_ = fnode.value_;
    status_ = fnode.status_;
}

FNode::FNode(const Node& node) : value_(),status_(false,2)
{
    if (node.getPosition().size()!=2) 
        throw(Exception("Wrong vector<double> size in FNode::FNode",__FILE__,__LINE__)) ;
    point_ = node.getPosition();
    near_ = node.isNearEdge();
    inside_ = node.isInside();
}

FNode::~FNode() {
}

bool FNode::operator==(const FNode &fnode) const
{
    return (this->getPosition() == fnode.getPosition())
              && (this->getValue() == fnode.getValue());
}

bool FNode::operator!=(const FNode &fnode) const
{
    return !(*this== fnode);
}

FNode& FNode::operator=(const FNode &fnode)
{
    if (fnode.getPosition().size()!=2) 
        throw(Exception("Wrong vector<double> size in FNode::operator=",__FILE__,__LINE__)) ;
    point_ = fnode.getPosition();
    near_ = fnode.isNearEdge();
    inside_ = fnode.isInside();
    value_ = fnode.value_;
    status_ = fnode.status_;
}

void FNode::setValue(const Vector &value)
{
    value_ = value;
}

Vector FNode::getValue() const
{
    return value_;
}

void FNode::setStatus(const vector<bool> &status)
{
    status_ = status;
}

vector<bool> FNode::getStatus() const
{
    return status_;
}