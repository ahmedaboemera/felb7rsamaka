#ifndef CREATURE_H
#define CREATURE_H
#include "Ocean.h"

class Ocean;
class Creature
{
    public:
        Creature(int a, int b, Ocean* c);
        virtual int gettype();
        virtual void checkSurroundings(Ocean *c);
        virtual int getStarve();
        virtual ~Creature();
    protected:
        int type;
        int iPos;
        int jPos;
        Ocean *homeOcean;
};

#endif // CREATURE_H
