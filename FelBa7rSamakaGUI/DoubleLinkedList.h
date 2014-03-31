#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "DoubleLinkedListNode.h"
#include "CreatureRLE.h"

class DoubleLinkedListNode;
class CreatureRLE;
class DoubleLinkedList
{
    public:
        DoubleLinkedList();
        ~DoubleLinkedList();
        void add(CreatureRLE* k, int num);
        void add(CreatureRLE* k, int num, int index);
        DoubleLinkedListNode* getNode(int index);
        DoubleLinkedListNode* getTail();
        DoubleLinkedListNode* getHead();
        int getSize();
        void removeNode(int index);
        void clearList();
        void print();
    protected:
        DoubleLinkedListNode* tail;
        DoubleLinkedListNode* head;
        int Size;
};

#endif // DOUBLELINKEDLIST_H
