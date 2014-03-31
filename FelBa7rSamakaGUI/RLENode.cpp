#include "RLENode.h"
#include <stdio.h>

RLENode::RLENode(RunLengthEncoding* s)
{
    sea = s;
    //3ayez afham elhetta de :)
    next = NULL;
}
void RLENode::setRunLengthEncoding(RunLengthEncoding* s)
{
    sea = s;
}
void RLENode::setNext(RLENode* n)
{
    next = n;
}
RunLengthEncoding* RLENode::getRunLengthEncoding()
{
    return sea;
}
RLENode* RLENode::getNext()
{
    return next;
}
RLENode::~RLENode()
{
    delete(sea);
}
