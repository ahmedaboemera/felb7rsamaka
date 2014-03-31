#include "FishRLE.h"

int FishRLE :: gettype()
{
    return 2;
}
int FishRLE :: getStarve()
{
    return -1;
}
void FishRLE::checkSurroundings(int position, RunLengthEncoding* c)
{
    int i,j;
    i = position%homeRLE->getWidth();
    j = position/homeRLE->getWidth();
    int tosend[8][2];
    int count = 0;
    for(int a = -1; a <=1 ; a ++)
    {
        for(int b = -1; b <= 1 ; b++)
        {
            if(a != 0 || b != 0)
            {
               tosend[count][0] = (i+a);
               tosend[count][1] = (j+b);
               count++;
            }
        }
    }
    int emptyCount = 0;
    int sharkCount = 0;
    int fishCount = 0;
    homeRLE->nodeSurroundingsContents(tosend, &emptyCount, &sharkCount, &fishCount);
    if(sharkCount == 0)
    {
        c->addFish(i, j);
    }
    else if(sharkCount >= 2)
    {
        c->addShark(i, j);
    }
    return;
}
FishRLE::~FishRLE()
{
    //destructor
}
