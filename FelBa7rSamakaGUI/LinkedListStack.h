#ifndef LINKEDLISTSTACK_H
#define LINKEDLISTSTACK_H
#include "OceanNode.h"
class OceanNode;

class LinkedListStack
{
    public:
        LinkedListStack();
        ~LinkedListStack();
        int GetStackSize();
        OceanNode* GetHead();
        bool isEmpty();
        Ocean* peek();
        Ocean* pop();
        void push(Ocean*);
        void Clear();
    protected:
    private:
        OceanNode* head;
        int StackSize;
};

#endif // LINKEDLISTSTACK_H
