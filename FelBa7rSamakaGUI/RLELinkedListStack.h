#ifndef RLELINKEDLISTSTACK_H
#define RLELINKEDLISTSTACK_H
#include "RLENode.h"
class RLENode;

class RLELinkedListStack
{
    public:
        RLELinkedListStack();
        ~RLELinkedListStack();
        int GetStackSize();
        RLENode* GetHead();
        bool isEmpty();
        RunLengthEncoding* peek();
        RunLengthEncoding* pop();
        void push(RunLengthEncoding*);
        void Clear();
    protected:
    private:
        RLENode* head;
        int StackSize;
};

#endif // RLELINKEDLISTSTACK_H
