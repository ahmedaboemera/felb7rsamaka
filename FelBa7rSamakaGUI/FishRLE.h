#ifndef FISHRLE_H
#define FISHRLE_H
#include "RunLengthEncoding.h"
#include "CreatureRLE.h"

class FishRLE : public CreatureRLE
{
    public:
        FishRLE(int p, RunLengthEncoding * RLE) : CreatureRLE(p, RLE)
        {
            type = 2;
        }
        void checkSurroundings(int position, RunLengthEncoding * c);
        int gettype();
        int getStarve();
        ~FishRLE();
};

#endif // FISHRLE_H
