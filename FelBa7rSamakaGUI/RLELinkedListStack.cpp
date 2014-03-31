#include "RLELinkedListStack.h"

RLELinkedListStack::RLELinkedListStack()
{
    StackSize = 0;
    head = NULL;
}
RLELinkedListStack::~RLELinkedListStack()
{
    Clear();
    printf("Deleted Successfully\n");
}
int RLELinkedListStack::GetStackSize()
{
    return StackSize;
}
RLENode* RLELinkedListStack::GetHead()
{
    return head;
}
bool RLELinkedListStack::isEmpty()
{
    if(StackSize == 0)
        return true;
    else
        return false;
}
RunLengthEncoding* RLELinkedListStack::peek()
{
    if(StackSize == 0)
        throw 0; //0 Error Stack is Empty (underflow)
    return head->getRunLengthEncoding();
}
RunLengthEncoding* RLELinkedListStack::pop()
{
    if(StackSize == 0)
        throw 0; //0 Error Stack is Empty (underflow)
    else
    {
        RunLengthEncoding* value = head->getRunLengthEncoding();
        head = head->getNext();
        //delete(temp);
        StackSize--;
        return value;
    }
}
void RLELinkedListStack::push(RunLengthEncoding* sea)
{
    RLENode* newNode = new RLENode(sea);
    newNode->setNext(head);
    head = newNode;
    StackSize++;
}
void RLELinkedListStack::Clear()
{
    while(StackSize != 0)
    {
        delete(pop());
    }
}
