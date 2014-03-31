#include "OceanNode.h"
#include <stdio.h>

OceanNode::OceanNode()
{
    sea = new Ocean();
    next = NULL;
}
OceanNode::OceanNode(Ocean* s)
{
    sea = s;
    //3ayez afham elhetta de :)
    next = NULL;
}
void OceanNode::setOcean(Ocean* s)
{
    sea = s;
}
void OceanNode::setNext(OceanNode* n)
{
    next = n;
}
Ocean* OceanNode::getOcean()
{
    return sea;
}
OceanNode* OceanNode::getNext()
{
    return next;
}
OceanNode::~OceanNode()
{
    delete(sea);
}
