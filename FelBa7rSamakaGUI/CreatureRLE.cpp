#include "CreatureRLE.h"
#include "FishRLE.h"
#include "SharkRLE.h"
#include "EmptyRLE.h"

CreatureRLE::CreatureRLE(int p, RunLengthEncoding* RLE)
{
    pos = p;
    homeRLE = RLE;
}
void CreatureRLE::checkSurroundings(int position, RunLengthEncoding * RLE)
{
    return;
}
int CreatureRLE :: gettype()
{
    return -1;
}
int CreatureRLE :: getStarve()
{
    return -1;
}
int CreatureRLE :: getPosition()
{
    return pos;
}
void CreatureRLE :: setPosition(int p)
{
    pos = p;
}
CreatureRLE::~CreatureRLE()
{
    //dtor
}
