#ifndef RLENODE_H
#define RLENODE_H
#include "RunLengthEncoding.h"
class RunLengthEncoding;

class RLENode
{
    public:
        RLENode(RunLengthEncoding*);
        void setRunLengthEncoding(RunLengthEncoding*);
        void setNext(RLENode*);
        RunLengthEncoding* getRunLengthEncoding();
        RLENode* getNext();
        ~RLENode();
    private:
        RunLengthEncoding* sea;
        RLENode* next;
};

#endif // RLENODE_H
