#ifndef EMPTYRLE_H
#define EMPTYRLE_H
#include "RunLengthEncoding.h"
#include "CreatureRLE.h"

class EmptyRLE : public CreatureRLE
{
    public:
        EmptyRLE(int p, RunLengthEncoding* RLE) : CreatureRLE(p, RLE)
        {
            type = 0;
        }
        int gettype();
        void checkSurroundings(int position, RunLengthEncoding *c);
        int getStarve();
        ~EmptyRLE();
};

#endif // EMPTYRLE_H
