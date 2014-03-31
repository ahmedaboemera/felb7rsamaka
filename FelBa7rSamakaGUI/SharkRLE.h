#ifndef SHARKRLE_H
#define SHARKRLE_H
#include "RunLengthEncoding.h"
#include "CreatureRLE.h"

class SharkRLE : public CreatureRLE
{
    public:
        SharkRLE(int p, RunLengthEncoding * RLE) : CreatureRLE(p, RLE)
        {
            type = 1;
            starveTime = RLE->getStarveTime();
        }
        SharkRLE(int p, int feeding, RunLengthEncoding * RLE) : CreatureRLE(p, RLE)
        {
            type = 1;
            starveTime = feeding;
        }
        void checkSurroundings(int position, RunLengthEncoding * c);
        int gettype();
        int getStarve();
        ~SharkRLE();
    private:
        int starveTime;
};

#endif // SHARKRLE_H
