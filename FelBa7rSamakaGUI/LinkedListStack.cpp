#include "LinkedListStack.h"
#include "OceanNode.h"
#include <stdio.h>
#include <stdlib.h>

LinkedListStack::LinkedListStack()
{
    StackSize = 0;
    head = NULL;
}
LinkedListStack::~LinkedListStack()
{
    Clear();
    printf("Deleted Successfully\n");
}
int LinkedListStack::GetStackSize()
{
    return StackSize;
}
OceanNode* LinkedListStack::GetHead()
{
    return head;
}
bool LinkedListStack::isEmpty()
{
    if(StackSize == 0)
        return true;
    else
        return false;
}
Ocean* LinkedListStack::peek()
{
    if(StackSize == 0)
        throw 0; //0 Error Stack is Empty (underflow)
    return head->getOcean();
}
Ocean* LinkedListStack::pop()
{
    if(StackSize == 0)
        throw 0; //0 Error Stack is Empty (underflow)
    else
    {
        Ocean* value = head->getOcean();
        head = head->getNext();
        //delete(temp);
        StackSize--;
        return value;
    }
}
void LinkedListStack::push(Ocean* sea)
{
    OceanNode* newNode = new OceanNode(sea);
    newNode->setNext(head);
    head = newNode;
    StackSize++;
}
void LinkedListStack::Clear()
{
    while(StackSize != 0)
    {
        delete(pop());
    }
}
