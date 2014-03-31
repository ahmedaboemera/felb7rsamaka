#include "Ocean.h"
#include "Creature.h"
#include "Empty.h"
#include "Shark.h"
#include "Fish.h"
#include <stdio.h>
#include <iostream>
using namespace std;
Ocean* bestOcean;
//Default Empty Constructor
Ocean::Ocean()
{
    width = 50;                              // Default ocean width
    height = 25;                            // Default ocean height
    starveTime = 3;                // Default shark starvation time
}

//Main Constructor
/**
*  Ocean() is a constructor that creates an empty ocean having width i and
*  height j, in which sharks starve after starveTime timesteps.
*  @param i is the width of the ocean.
*  @param j is the height of the ocean.
*  @param starveTime is the number of timesteps sharks survive without food.
*/
Ocean::Ocean(int i, int j, int time)
{
    width = i;                              // Input ocean width
    height = j;                            // Input ocean height
    starveTime = time;                // Input shark starvation time
    oceanContents = new Creature**[height];
    for(int h = 0; h < height; h++)
    {
        oceanContents[h] = new Creature*[width];
    }
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            Ocean* tosend = this;
            oceanContents[h][w] = new Empty(w, h, tosend);
            oceanContents[h][w]->gettype();
        }
    }
}

//Destructor
Ocean::~Ocean()
{
    for(int h = 0; h < height; h++)
    {
        for(int w = 0; w < width; w++)
        {
            delete(oceanContents[h][w]);
        }
        delete(oceanContents[h]);
    }
    delete(oceanContents);
}

/**
*  width() returns the width of an Ocean object.
*  @return the width of the ocean.
*/
int Ocean::getWidth()
{
    return width;
}

/**
*  height() returns the height of an Ocean object.
*  @return the height of the ocean.
*/
int Ocean::getHeight()
{
    return height;
}

/**
*  starveTime() returns the number of timesteps sharks survive without food.
*  @return the number of timesteps sharks survive without food.
*/
int Ocean::getStarveTime()
{
    return starveTime;
}

/**
 *  addFish() places a fish in cell (x, y) if the cell is empty.  If the
 *  cell is already occupied, leave the cell as it is.
 *  @param x is the x-coordinate of the cell to place a fish in.
 *  @param y is the y-coordinate of the cell to place a fish in.
 */
void Ocean::addFish(int x, int y)
{
    newXY(&x, &y);
    if(oceanContents[y][x]->gettype() == this->EMPTY)//EMPTY
    {
        delete(oceanContents[y][x]);
        oceanContents[y][x] = new Fish(x, y, this);
    }
    else
    {
        cout<<"invalid index to add at"<<endl;
        return;
    }
}

/**
 *  addShark() (with two parameters) places a newborn shark in cell (x, y) if
 *  the cell is empty.  A "newborn" shark is equivalent to a shark that has
 *  just eaten.  If the cell is already occupied, leave the cell as it is.
 *  @param x is the x-coordinate of the cell to place a shark in.
 *  @param y is the y-coordinate of the cell to place a shark in.
 */
void Ocean::addShark(int x, int y)
{
    newXY(&x, &y);
    if(oceanContents[y][x]->gettype() == this->EMPTY)//EMPTY
    {
        delete(oceanContents[y][x]);
        oceanContents[y][x] = new Shark(x, y, this);
    }
    else
    {
        cout<<"invalid index to add at"<<endl;
        return;
    }
}

/**
 *  cellContents() returns EMPTY if cell (x, y) is empty, FISH if it contains
 *  a fish, and SHARK if it contains a shark.
 *  @param x is the x-coordinate of the cell whose contents are queried.
 *  @param y is the y-coordinate of the cell whose contents are queried.
 */
int Ocean::cellContents(int x, int y)
{
    newXY(&x, &y);
    return oceanContents[y][x]->gettype();
}

/**
 *  timeStep() performs a simulation timestep as described in README.
 *  @return an ocean representing the elapse of one timestep.
 */
Ocean* Ocean::timeStep()
{
    int h, w;
    Ocean *newOcean = new Ocean (width, height, starveTime);
    for(h=0; h<height; h++)
    {
        for(w=0; w<width; w++)
        {
            oceanContents[h][w]->checkSurroundings(newOcean);
        }
    }
    return newOcean;
}

/**
 *  addShark() (with three parameters) places a shark in cell (x, y) if the
 *  cell is empty.  The shark's hunger is represented by the third parameter.
 *  If the cell is already occupied, leave the cell as it is.  You will need
 *  this method to help convert run-length encodings to Oceans.
 *  @param x is the x-coordinate of the cell to place a shark in.
 *  @param y is the y-coordinate of the cell to place a shark in.
 *  @param feeding is an integer that indicates the shark's hunger.  You may
 *         encode it any way you want; for instance, "feeding" may be the
 *         last timestep the shark was fed, or the amount of time that has
 *         passed since the shark was last fed, or the amount of time left
 *         before the shark will starve.  It's up to you, but be consistent.
 **/

void Ocean::addShark(int x, int y, int feeding)
{
    newXY(&x, &y);
    if(oceanContents[y][x]->gettype() == this->EMPTY)//EMPTY
    {
        delete(oceanContents[y][x]);
        oceanContents[y][x] = new Shark(x, y, feeding, this);
    }
    else
    {
        cout<<"invalid index to add at"<<endl;
        return;
    }
}

/**
 *  sharkFeeding() returns an integer that indicates the hunger of the shark
 *  in cell (x, y), using the same "feeding" representation as the parameter
 *  to addShark() described above.  If cell (x, y) does not contain a shark,
 *  then its return value is undefined--that is, anything you want.
 *  Normally, this method should not be called if cell (x, y) does not
 *  contain a shark.  You will need this method to help convert Oceans to
 *  run-length encodings.
 *  @param x is the x-coordinate of the cell whose contents are queried.
 *  @param y is the y-coordinate of the cell whose contents are queried.
 */

int Ocean::sharkFeeding(int x, int y)
{
    newXY(&x, &y);
    return oceanContents[y][x]->getStarve();
}

void Ocean::newXY(int* x, int* y)
{
    if(*x >= 0)
        *x = *x % width;
    else
    {
        while(*x < 0)
            *x = *x + width;
        *x = *x % width;
    }
    if(*y >= 0)
        *y = *y % height;
    else
    {
        while(*y < 0)
            *y = *y + height;
        *y = *y % height;
    }
}

Ocean* Ocean::minimax()
{
    bestOcean = new Ocean(width, height, starveTime);
    int** oldFishPosition = new int*[width*height];
    for(int i=0; i<width*height; i++)
        oldFishPosition[i] = new int[2];
    int fishNumber = 0;
    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(cellContents(j, i) == FISH)
            {
                oldFishPosition[fishNumber][0] = i;
                oldFishPosition[fishNumber][1] = j;
                fishNumber++;
            }
        }
    }
    int** newFishPosition = new int*[fishNumber];
    for(int i=0; i<fishNumber; i++)
        newFishPosition[i] = new int[2];
    int maxFishN = 0, newSharkN = width*height;
    bestMove(0, oldFishPosition, newFishPosition, &maxFishN, &newSharkN, fishNumber);
    //NEW OCEAN
    delete(oldFishPosition);
    delete(newFishPosition);
    return bestOcean;
}

void Ocean::bestMove(int fishIndex, int** oldFishPosition, int** newFishPosition, int* maxFishN, int* newSharkN, int fishNumber)
{
    if(fishIndex == fishNumber)
    {
        Ocean* tryOcean = new Ocean(width, height, starveTime);
        int N = 0, i, j, fishN = 0, sharkN = 0;
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                if(cellContents(j, i) == FISH)
                {
                    if(oldFishPosition[N][0] != i || oldFishPosition[N][1] != j)
                        printf("7omar\n");
                    else
                    {
                        tryOcean->addFish(newFishPosition[N][1], newFishPosition[N][0]);
                    }
                    N++;
                }

                else if(cellContents(j, i) == SHARK)
                {
                    tryOcean->addShark(j, i, oceanContents[i][j]->getStarve());
                }

                if(N > fishNumber)
                    printf("7omar\n");
            }
        }
        Ocean* tryOceanTimeStep = tryOcean->timeStep();
        for(i = 0; i < height; i++)
        {
            for(j = 0; j < width; j++)
            {
                if(tryOceanTimeStep->cellContents(j, i) == FISH)
                    fishN++;

                else if(tryOceanTimeStep->cellContents(j, i) == SHARK)
                    sharkN++;
            }
        }

        if(fishN > *maxFishN)
        {
            *maxFishN = fishN;
            *newSharkN = sharkN;
            delete(bestOcean);
            bestOcean = tryOcean->copyOcean();
            delete(tryOcean);
            delete(tryOceanTimeStep);
        }
        else if(fishN == *maxFishN && sharkN < *newSharkN)
        {
            *maxFishN = fishN;
            *newSharkN = sharkN;
            delete(bestOcean);
            bestOcean = tryOcean->copyOcean();
            delete(tryOcean);
            delete(tryOceanTimeStep);
        }
        else
        {
            delete(tryOcean);
        }
        return;
    }
    int a, b;
    for(a = -1; a <= 1; a++)
    {
        for(b = -1; b <= 1; b++)
        {
            int isTaken = 0;
            newFishPosition[fishIndex][0] = oldFishPosition[fishIndex][0] + a;
            newFishPosition[fishIndex][1] = oldFishPosition[fishIndex][1] + b;
            newXY(&newFishPosition[fishIndex][1], &newFishPosition[fishIndex][0]);
            if(cellContents(newFishPosition[fishIndex][1], newFishPosition[fishIndex][0]) == EMPTY)
            {
                for(int k=0; k<fishIndex && isTaken==0; k++)
                {
                    if(newFishPosition[k][0] == newFishPosition[fishIndex][0] && newFishPosition[k][1] == newFishPosition[fishIndex][1])
                        isTaken = 1;
                }
                if(isTaken == 0)
                    bestMove(fishIndex+1, oldFishPosition, newFishPosition, maxFishN, newSharkN, fishNumber);
            }
        }
    }
}
Ocean* Ocean::copyOcean()
{
    Ocean *newer = new Ocean(this->getWidth(), this->getHeight(), this->getStarveTime());
    for(int i = 0; i<this->getHeight(); i++)
    {
        for(int j = 0; j<this->getWidth(); j++)
        {
            switch(this->cellContents(j , i))
            {
            case 0:
                break;
            case 1:
                newer->addShark(j, i, this->oceanContents[i][j]->getStarve());
                break;
            case 2:
                newer->addFish(j, i);
                break;
            }
        }
    }
    return newer;
}

