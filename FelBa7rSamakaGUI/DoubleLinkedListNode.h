#ifndef DOUBLELINKEDLISTNODE_H
#define DOUBLELINKEDLISTNODE_H
#include <stdio.h>
#include "CreatureRLE.h"

class CreatureRLE;
class DoubleLinkedListNode
{
    public:
        DoubleLinkedListNode(CreatureRLE* k, int num);
        CreatureRLE* getCreatureRLE();
        void setNumber(int num);
        DoubleLinkedListNode* getNext();
        DoubleLinkedListNode* getPrevious();
        void setNext(DoubleLinkedListNode* n);
        void setPrevious(DoubleLinkedListNode* p);
        int getNumber();
    private:
        CreatureRLE* kind;
        int number;
        DoubleLinkedListNode* next;
        DoubleLinkedListNode* previous;
};

#endif // DOUBLELINKEDLISTNODE_H
