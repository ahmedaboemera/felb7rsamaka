#ifndef OCEANNODE_H
#define OCEANNODE_H
#include "Ocean.h"
class Ocean;

class OceanNode
{
    public:
        OceanNode();
        OceanNode(Ocean*);
        void setOcean(Ocean*);
        void setNext(OceanNode*);
        Ocean* getOcean();
        OceanNode* getNext();
        ~OceanNode();
    private:
        Ocean* sea;
        OceanNode* next;
};

#endif // OCEANNODE_H
