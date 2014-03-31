#ifndef CREATURERLE_H
#define CREATURERLE_H
#include "RunLengthEncoding.h"

class RunLengthEncoding;
class CreatureRLE
{
    public:
        CreatureRLE(int p, RunLengthEncoding* RLE);
        virtual int gettype();
        virtual void checkSurroundings(int position, RunLengthEncoding *c);
        virtual int getStarve();
        virtual ~CreatureRLE();
        int getPosition();
        void setPosition(int p);
    protected:
        int type;
        int pos;
        RunLengthEncoding* homeRLE;
};

#endif // CREATURERLE_H
