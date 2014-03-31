#include "RunLengthEncoding.h"
#include "Ocean.h"
#include "CreatureRLE.h"
#include "EmptyRLE.h"
#include "FishRLE.h"
#include "SharkRLE.h"
#include <iostream>
#include <stdio.h>
using namespace std;

class DoubleLinkedList;

/**
 *  RunLengthEncoding() (with three parameters) is a constructor that creates
 *  a run-length encoding of an empty ocean having width i and height j,
 *  in which sharks starve after starveTime timesteps.
 *  @param i is the width of the ocean.
 *  @param j is the height of the ocean.
 *  @param starveTime is the number of timesteps sharks survive without food.
 */

RunLengthEncoding::RunLengthEncoding(int i, int j, int feeding)
{
    RLEocean = new DoubleLinkedList();
    CreatureRLE* first;
    first = new EmptyRLE(0, this);
    RLEocean->add(first, (i*j));
    width = i;
    height = j;
    starveTime = feeding;
    moving = RLEocean->getHead();
}
/**
 *  RunLengthEncoding() (with five parameters) is a constructor that creates
 *  a run-length encoding of an ocean having width i and height j, in which
 *  sharks starve after starveTime timesteps.  The runs of the run-length
 *  encoding are taken from two input arrays.  Run i has length runLengths[i]
 *  and species runTypes[i].
 *  @param i is the width of the ocean.
 *  @param j is the height of the ocean.
 *  @param starveTime is the number of timesteps sharks survive without food.
 *  @param runTypes is an array that represents the species represented by
 *         each run.  Each element of runTypes is Ocean.EMPTY, Ocean.FISH,
 *         or Ocean.SHARK.  Any run of sharks is treated as a run of newborn
 *         sharks (which are equivalent to sharks that have just eaten).
 *  @param runLengths is an array that represents the length of each run.
 *         The sum of all elements of the runLengths array should be i * j.
 */

RunLengthEncoding::RunLengthEncoding(int i, int j, int feeding, int* runTypes, int runTypesSize, int* runLengths, int runLengthsSize)
{
    int counter = runLengths[0];
    int typeBefore = runTypes[0];
    for(int l=1; l<runTypesSize; l++)
    {
        counter += runLengths[l];
        if(runTypes[l] == typeBefore)
        {
            printf("Invalid Input!\n");
            throw 0;
        }
        typeBefore = runTypes[l];
    }
    if(counter != i*j)
    {
        printf("Invalid Input!\n");
        throw 0;
    }
    int initialPos = 0;
    RLEocean = new DoubleLinkedList();
    width = i;
    height = j;
    starveTime = feeding;
    for(int l = 0; l < runTypesSize; l++)
    {
        switch(runTypes[l])
        {
        case 0:
        {
            RLEocean->add(new EmptyRLE(initialPos, this), runLengths[l]);
            break;
        }
        case 1:
        {
            RLEocean->add(new SharkRLE(initialPos, starveTime, this), runLengths[l]);
            break;
        }
        case 2:
        {
            RLEocean->add(new FishRLE(initialPos, this), runLengths[l]);
            break;
        }
        }
        initialPos += runLengths[l];
    }
    moving = RLEocean->getHead();
}
// Destructor
RunLengthEncoding::~RunLengthEncoding()
{
    delete(RLEocean);
}
/**
 *  restartRuns() and nextRun() are two methods that work together to return
 *  all the runs in the run-length encoding, one by one.  Each time
 *  nextRun() is invoked, it returns a different run (represented as an
 *  array of two ints), until every run has been returned.  The first time
 *  nextRun() is invoked, it returns the first run in the encoding, which
 *  contains cell (0, 0).  After every run has been returned, nextRun()
 *  returns null, which lets the calling program know that there are no more
 *  runs in the encoding.
 *
 *  The restartRuns() method resets the enumeration, so that nextRun() will
 *  once again enumerate all the runs as if nextRun() were being invoked for
 *  the first time.
 *
 *  (Note:  Don't worry about what might happen if nextRun() is interleaved
 *  with addFish() or addShark(); it won't happen.)
 */
/**
 *  restartRuns() resets the enumeration as described above, so that
 *  nextRun() will enumerate all the runs from the beginning.
 */
void RunLengthEncoding::restartRuns()
{
    moving = RLEocean->getHead();
}

/**
 *  nextRun() returns the next run in the enumeration, as described above.
 *  If the runs have been exhausted, it returns null.  The return value is
 *  an array of two ints (constructed here), representing the type and the
 *  sizesize of the run, in that order.
 *  @return the next run in the enumeration, represented by an array of
 *          two ints.  The int at index zero indicates the run type
 *          (Ocean.EMPTY, Ocean.SHARK, or Ocean.FISH).  The int at index one
 *          indicates the run length (which must be at least 1).
 */
void RunLengthEncoding::nextRun(int* result, int* size)
{
    if(moving != NULL)
    {
        *result = moving->getCreatureRLE()->gettype();
        *size = moving->getNumber();
        moving = moving->getNext();
    }
    else
    {
        cout<<"please perform restartRuns functions because you have reached the end ofthe list"<<"\n";
        result = NULL;
        size = NULL;
        throw 0;
        return;
    }
}
void RunLengthEncoding::nextRun2(int* result, int* size, int* feeding)
{
    if(moving != NULL)
    {
        *result = moving->getCreatureRLE()->gettype();
        *size = moving->getNumber();
        *feeding = moving->getCreatureRLE()->getStarve();
        moving = moving->getNext();
    }
    else
    {
        cout<<"please perform restartRuns functions because you have reached the end ofthe list"<<"\n";
        result = NULL;
        size = NULL;
        feeding = NULL;
        throw 0;
        return;
    }
}
/**
 *  toOcean() converts a run-length encoding of an ocean into an Ocean
 *  object.  You will need to implement the three-parameter addShark method
 *  in the Ocean class for this method's use.
 *  @return the Ocean represented by a run-length encoding.
 */

Ocean* RunLengthEncoding::toOcean()
{
    Ocean* newOcean = new Ocean(this->getWidth(), this->getHeight(), this->getStarveTime());
    DoubleLinkedListNode* current = RLEocean->getHead();
    //int pos = 0;
    while (current != NULL)
    {
        int number = current->getNumber();
        int initiali, initialj;
        for(int count = 0 ; count < number ; count++ )
        {
            int pos = current->getCreatureRLE()->getPosition();
            pos = pos+count;
            initiali = pos%this->getWidth();
            initialj = pos/this->getWidth();
            switch(current->getCreatureRLE()->gettype())
            {
            case 1:
            {
                newOcean->addShark(initiali, initialj, current->getCreatureRLE()->getStarve());
                break;
            }
            case 2:
            {
                newOcean->addFish(initiali, initialj);
                break;
            }
            }
            //pos++;
        }
        current = current->getNext();
    }
    return newOcean;
}
/**
 *  RunLengthEncoding() (with one parameter) is a constructor that creates
 *  a run-length encoding of an input Ocean.  You will need to implement
 *  the sharkFeeding method in the Ocean class for this constructor's use.
 *  @param sea is the ocean to encode.
 */
RunLengthEncoding::RunLengthEncoding(Ocean* sea)
{
    RLEocean = new DoubleLinkedList();
    width = sea->getWidth();
    height = sea->getHeight();
    starveTime = sea->getStarveTime();
    int beforeContents = sea->cellContents(0, 0);
    CreatureRLE* first;
    int initialPos = 0;
    switch(beforeContents)
    {
    case 0:
        first = new EmptyRLE(initialPos, this);
        break;
    case 1:
        first = new SharkRLE(initialPos, sea->sharkFeeding(0, 0), this);
        break;
    case 2:
        first = new FishRLE(initialPos, this);
        break;
    }
    initialPos ++;
    RLEocean->add(first, 1);
    DoubleLinkedListNode* before = RLEocean->getTail();
    CreatureRLE* toAdd;
    for(int j = 0; j < sea->getHeight(); j++)
    {
        if(before->getCreatureRLE()->gettype() == -1)
        {
            cout<<"ana 7omar\n";
        }
        for(int i = (j==0)?1:0 ; i < sea->getWidth(); i++)
        {
            int contents = sea->cellContents(i, j);
            if(contents == beforeContents)
            {
                if(contents == 0 || contents == 2)
                {
                    before->setNumber(before->getNumber()+1);
                }
                else
                {
                    if(sea->sharkFeeding(i,j) == before->getCreatureRLE()->getStarve())
                    {
                        before->setNumber(before->getNumber()+1);
                    }
                    else
                    {
                        toAdd = new SharkRLE(initialPos, sea->sharkFeeding(i,j), this);
                        RLEocean->add(toAdd, 1);
                        before = RLEocean->getTail();
                    }
                }
            }
            else
            {
                beforeContents = contents;
                switch(contents)
                {
                case 0:
                    toAdd = new EmptyRLE(initialPos, this);
                    break;
                case 1:
                    toAdd = new SharkRLE(initialPos, sea->sharkFeeding(i,j), this);
                    break;
                case 2:
                    toAdd = new FishRLE(initialPos, this);
                    break;
                }
                RLEocean->add(toAdd, 1);
                before = RLEocean->getTail();
            }
            initialPos ++;
        }
    }
    moving = RLEocean->getHead();
    check();
}
int RunLengthEncoding::getStarveTime()
{
    return starveTime;
}
int RunLengthEncoding::getWidth()
{
    return width;
}
int RunLengthEncoding::getHeight()
{
    return height;
}
void RunLengthEncoding::nodeSurroundingsContents(int coordinates[8][2], int* emptyCount, int* sharkCount, int* fishCount)
{
    int positions[8];
    int a, b, minIndex, temp, rowIndex, columnIndex;
    for(a=0; a<8; a++)
    {
        rowIndex = coordinates[a][1];
        columnIndex = coordinates[a][0];
        newXY(&columnIndex, &rowIndex);
        positions[a] = rowIndex * width + columnIndex;
    }
    for(a=0; a<8; a++)
    {
        minIndex = a;
        for(b=a+1; b<8; b++)
        {
            if(positions[b] < positions[minIndex])
                minIndex = b;
        }
        temp = positions[minIndex];
        positions[minIndex] = positions[a];
        positions[a] = temp;
    }
    DoubleLinkedListNode* current = RLEocean->getHead();
    int index = 0;
    while(current != NULL && index < 8)
    {
        if(current->getCreatureRLE()->getPosition() < positions[index])
        {
            current = current->getNext();
        }
        else if(current->getCreatureRLE()->getPosition() == positions[index])
        {
            switch(current->getCreatureRLE()->gettype())
            {
            case 0:
            {
                (*emptyCount)++;
                break;
            }
            case 1:
            {
                (*sharkCount)++;
                break;
            }
            case 2:
            {
                (*fishCount)++;
                break;
            }
            }
            index++;
        }
        else
        {
            switch(current->getPrevious()->getCreatureRLE()->gettype())
            {
            case 0:
                (*emptyCount)++;
                break;
            case 1:
                (*sharkCount)++;
                break;
            case 2:
                (*fishCount)++;
                break;
            }
            index++;
        }
    }
    while(index < 8)
    {
        switch(RLEocean->getTail()->getCreatureRLE()->gettype())
        {
        case 0:
            (*emptyCount)++;
            break;
        case 1:
            (*sharkCount)++;
            break;
        case 2:
            (*fishCount)++;
            break;
        }
        index++;
    }
}
/**
 *  addFish() places a fish in cell (x, y) if the cell is empty.  If the
 *  cell is already occupied, leave the cell as it is.  The final run-length
 *  encoding should be compressed as much as possible; there should not be
 *  two consecutive runs of sharks with the same degree of hunger.
 *  @param x is the x-coordinate of the cell to place a fish in.
 *  @param y is the y-coordinate of the cell to place a fish in.
 */
void RunLengthEncoding::addFish(int x, int y)
{
    newXY(&x, &y);
    int pos = (y*this->getWidth()) + x;
    DoubleLinkedListNode* current = RLEocean->getHead();
    if(pos >= (this->getHeight()*this->getWidth()))
    {
        cout<<"invalid index to add at"<<endl;
        return;
    }
    int index = 0;
    while(current != NULL)
    {
        if(current->getCreatureRLE()->getPosition() < pos)
        {
            current = current->getNext();
            index++;
        }
        else if(current->getCreatureRLE()->getPosition() > pos)
        {
            if(current->getPrevious()->getCreatureRLE()->gettype() == 0)
            {
                int nextPos = current->getCreatureRLE()->getPosition();
                current = current->getPrevious();
                int firstPos = current->getCreatureRLE()->getPosition();
                current->setNumber(pos - firstPos);
                CreatureRLE* FishtoAdd = new FishRLE(pos, this);
                RLEocean->add(FishtoAdd, 1, index);
                CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
                RLEocean->add(EmptytoAdd, nextPos-pos-1, index + 1);
                checkDuplicates();
                moving = RLEocean->getHead();
                check();
                return;
            }
            else
            {
                cout<<"index already occupied"<<endl;
                return;
            }
        }
        else
        {
            if(current->getCreatureRLE()->gettype() == 0)
            {
                current->setNumber(current->getNumber() - 1);
                current->getCreatureRLE()->setPosition(pos + 1);
                CreatureRLE* fishToAdd = new FishRLE(pos, this);
                RLEocean->add(fishToAdd, 1, index);
                checkDuplicates();
                moving = RLEocean->getHead();
                check();
                return;
            }
            else
            {
                cout<<"index already occupied"<<endl;
                return;
            }
        }
    }
    current = RLEocean->getTail();
    //printf("%d ha %d",RLEocean->getTail()->getCreatureRLE()->getPosition(), current->getCreatureRLE()->getPosition());
    if(current->getCreatureRLE()->gettype() == 0)
    {
        int firstPos = current->getCreatureRLE()->getPosition();
        current->setNumber(pos - firstPos);
        CreatureRLE* FishtoAdd = new FishRLE(pos, this);
        RLEocean->add(FishtoAdd, 1);
        CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
        RLEocean->add(EmptytoAdd, this->getHeight()*this->getWidth()-pos-1);
        checkDuplicates();
        moving = RLEocean->getHead();
        check();
        return;
    }
    else
    {
        cout<<"index already occupied"<<endl;
        return;
    }
}
void RunLengthEncoding::addFishComplicated(int x, int y)
{
    newXY(&x, &y);
    int pos = (y*this->getWidth()) + x;
    DoubleLinkedListNode* current = RLEocean->getHead();
    if(pos >= (this->getHeight()*this->getWidth()))
    {
        cout<<"invalid index to add at"<<endl;
        return;
    }
    if(pos == 0)
    {
        if(current->getCreatureRLE()->gettype() == 0)
        {
            if(current->getNumber() != 1)
            {
                CreatureRLE* fishToAdd = new FishRLE(0, this);
                current->getCreatureRLE()->setPosition(1);
                current->setNumber(current->getNumber()-1);
                RLEocean->add(fishToAdd, 1, 0);
                //this->checkDuplicates();
            }
            else
            {
                if(current->getNext() != NULL && current->getNext()->getCreatureRLE()->gettype() == 2)
                {
                    current->getNext()->setNumber(current->getNext()->getNumber()+1);
                    current->getNext()->getCreatureRLE()->setPosition(0);
                    RLEocean->removeNode(0);
                }
                else
                {
                    RLEocean->removeNode(0);
                    CreatureRLE* fishToAdd = new FishRLE(0, this);
                    RLEocean->add(fishToAdd,1 ,0);
                    //this->checkDuplicates();
                }
            }
            moving = RLEocean->getHead();
            check();
            return;
        }
        else
        {
            cout<<"index already occupied"<<endl;
            return;
        }
    }
    int index = 0;
    while(current != NULL)
    {
        if(current->getCreatureRLE()->getPosition() < pos)
        {
            current = current->getNext();
            index++;
        }
        else if(current->getCreatureRLE()->getPosition() > pos)
        {
            if(current->getPrevious()->getCreatureRLE()->gettype() == 0)
            {
                if(current->getCreatureRLE()->getPosition()-1 == pos)
                {
                    if(current->getCreatureRLE()->gettype() == 2)
                    {
                        current->setNumber(current->getNumber()+1);
                        current->getCreatureRLE()->setPosition(pos);
                        current->getPrevious()->setNumber(current->getPrevious()->getNumber()-1);
                        //this->checkDuplicates();
                    }
                    else
                    {
                        CreatureRLE* fishToadd = new FishRLE(pos, this);
                        current->getPrevious()->setNumber(current->getPrevious()->getNumber()-1);
                        RLEocean->add(fishToadd, 1, index);
                        //this->checkDuplicates();
                    }
                }
                else
                {
                    int nextPos = current->getCreatureRLE()->getPosition();
                    current = current->getPrevious();
                    int firstPos = current->getCreatureRLE()->getPosition();
                    current->setNumber(pos - firstPos);
                    CreatureRLE* FishtoAdd = new FishRLE(pos, this);
                    RLEocean->add(FishtoAdd, 1, index);
                    CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
                    RLEocean->add(EmptytoAdd, nextPos-pos-1, index + 1);
                    //this->checkDuplicates();
                }
                moving = RLEocean->getHead();
                check();
                return;
            }
            else
            {
                cout<<"index already occupied"<<endl;
                return;
            }
        }
        else
        {
            if(current->getCreatureRLE()->gettype() != 0)
            {
                cout<<"index already occupied"<<endl;
                return;
            }
            else
            {
                if(current->getPrevious()->getCreatureRLE()->gettype() == 2)
                {
                    if(current->getNumber() != 1)
                    {
                        current->getPrevious()->setNumber(current->getPrevious()->getNumber()+1);
                        current->getCreatureRLE()->setPosition(pos+1);
                        current->setNumber(current->getNumber()-1);
                        //this->checkDuplicates();
                    }
                    else
                    {
                        if(current->getNext() != NULL && current->getNext()->getCreatureRLE()->gettype() == 2)
                        {
                            current->getPrevious()->setNumber(current->getPrevious()->getNumber() + 1 + current->getNext()->getNumber());
                            RLEocean->removeNode(index);
                            RLEocean->removeNode(index);
                        }
                        else
                        {
                            RLEocean->removeNode(index);
                            current->getPrevious()->setNumber(current->getPrevious()->getNumber()+1);
                            //   this->checkDuplicates();
                        }
                    }
                }
                else
                {
                    if(current->getNumber() != 1)
                    {
                        CreatureRLE* fishToadd = new FishRLE(pos, this);
                        RLEocean->add(fishToadd, 1, index);
                        current->setNumber(current->getNumber()-1);
                        current->getCreatureRLE()->setPosition(pos+1);
                        //this->checkDuplicates();
                    }
                    else
                    {
                        if(current->getNext() != NULL && current->getNext()->getCreatureRLE()->gettype() == 2)
                        {
                            current->getNext()->setNumber(current->getNext()->getNumber()+1);
                            current->getNext()->getCreatureRLE()->setPosition(pos);
                            RLEocean->removeNode(index);
                        }
                        else
                        {
                            RLEocean->removeNode(index);
                            CreatureRLE* fishToadd = new FishRLE(pos, this);
                            RLEocean->add(fishToadd, 1, index);
                        }
                        //this->checkDuplicates();
                    }
                }
                moving = RLEocean->getHead();
                check();
                return;
            }
        }
    }
    current = RLEocean->getTail();
    if(current->getCreatureRLE()->gettype() == 0)
    {
        if(pos == (this->getHeight() * this->getWidth() - 1))
        {
            CreatureRLE* fish = new FishRLE(pos, this);
            RLEocean->add(fish, 1);
            current->setNumber(current->getNumber()-1);
            //this->checkDuplicates();
        }
        else
        {
            int firstPos = current->getCreatureRLE()->getPosition();
            current->setNumber(pos - firstPos);
            CreatureRLE* FishtoAdd = new FishRLE(pos, this);
            RLEocean->add(FishtoAdd, 1);
            CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
            RLEocean->add(EmptytoAdd, (this->getHeight() * this->getWidth())-pos-1);
            //this->checkDuplicates();
        }
        moving = RLEocean->getHead();
        check();
        return;
    }
    else
    {
        cout<<"index already occupied"<<endl;
        return;
    }
}
/**
 *  addShark() (with two parameters) places a newborn shark in cell (x, y) if
 *  the cell is empty.  A "newborn" shark is equivalent to a shark that has
 *  just eaten.  If the cell is already occupied, leave the cell as it is.
 *  The final run-length encoding should be compressed as much as possible;
 *  there should not be two consecutive runs of sharks with the same degree
 *  of hunger.
 *  @param x is the x-coordinate of the cell to place a shark in.
 *  @param y is the y-coordinate of the cell to place a shark in.
 */
void RunLengthEncoding::addShark(int x, int y)
{
    newXY(&x, &y);
    int pos = (y*this->getWidth()) + x;
    DoubleLinkedListNode* current = RLEocean->getHead();
    if(pos >= (this->getHeight()*this->getWidth()))
    {
        cout<<"invalid index to add at"<<endl;
        return;
    }
    int index = 0;
    while(current != NULL)
    {
        if(current->getCreatureRLE()->getPosition() < pos)
        {
            current = current->getNext();
            index++;
        }
        else if(current->getCreatureRLE()->getPosition() > pos)
        {
            if(current->getPrevious()->getCreatureRLE()->gettype() == 0)
            {
                int nextPos = current->getCreatureRLE()->getPosition();
                current = current->getPrevious();
                int firstPos = current->getCreatureRLE()->getPosition();
                current->setNumber(pos - firstPos);
                CreatureRLE* SharktoAdd = new SharkRLE(pos, this);
                RLEocean->add(SharktoAdd, 1, index);
                CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
                RLEocean->add(EmptytoAdd, nextPos-pos-1, index + 1);
                checkDuplicates();
                moving = RLEocean->getHead();
                check();
                return;
            }
            else
            {
                cout<<"index already occupied"<<endl;
                return;
            }
        }
        else
        {
            if(current->getCreatureRLE()->gettype() == 0)
            {
                current->setNumber(current->getNumber() - 1);
                current->getCreatureRLE()->setPosition(pos + 1);
                CreatureRLE* SharkToAdd = new SharkRLE(pos, this);
                RLEocean->add(SharkToAdd, 1, index);
                checkDuplicates();
                moving = RLEocean->getHead();
                check();
                return;
            }
            else
            {
                cout<<"index already occupied"<<endl;
                return;
            }
        }
    }
    current = RLEocean->getTail();
    //printf("%d ha %d",RLEocean->getTail()->getCreatureRLE()->getPosition(), current->getCreatureRLE()->getPosition());
    if(current->getCreatureRLE()->gettype() == 0)
    {
        int firstPos = current->getCreatureRLE()->getPosition();
        current->setNumber(pos - firstPos);
        CreatureRLE* SharktoAdd = new SharkRLE(pos, this);
        RLEocean->add(SharktoAdd, 1);
        CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
        RLEocean->add(EmptytoAdd, this->getHeight()*this->getWidth()-pos-1);
        checkDuplicates();
        moving = RLEocean->getHead();
        check();
        return;
    }
    else
    {
        cout<<"index already occupied"<<endl;
        return;
    }
}

void RunLengthEncoding::addShark(int x, int y, int feeding)
{
    newXY(&x, &y);
    int pos = (y*this->getWidth()) + x;
    DoubleLinkedListNode* current = RLEocean->getHead();
    if(pos >= (this->getHeight()*this->getWidth()))
    {
        cout<<"invalid index to add at"<<endl;
        return;
    }
    int index = 0;
    while(current != NULL)
    {
        if(current->getCreatureRLE()->getPosition() < pos)
        {
            current = current->getNext();
            index++;
        }
        else if(current->getCreatureRLE()->getPosition() > pos)
        {
            if(current->getPrevious()->getCreatureRLE()->gettype() == 0)
            {
                int nextPos = current->getCreatureRLE()->getPosition();
                current = current->getPrevious();
                int firstPos = current->getCreatureRLE()->getPosition();
                current->setNumber(pos - firstPos);
                CreatureRLE* SharktoAdd = new SharkRLE(pos, feeding, this);
                RLEocean->add(SharktoAdd, 1, index);
                CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
                RLEocean->add(EmptytoAdd, nextPos-pos-1, index + 1);
                checkDuplicates();
                moving = RLEocean->getHead();
                check();
                return;
            }
            else
            {
                cout<<"index already occupied"<<endl;
                return;
            }
        }
        else
        {
            if(current->getCreatureRLE()->gettype() == 0)
            {
                current->setNumber(current->getNumber() - 1);
                current->getCreatureRLE()->setPosition(pos + 1);
                CreatureRLE* SharkToAdd = new SharkRLE(pos, feeding, this);
                RLEocean->add(SharkToAdd, 1, index);
                checkDuplicates();
                moving = RLEocean->getHead();
                check();
                return;
            }
            else
            {
                cout<<"index already occupied"<<endl;
                return;
            }
        }
    }
    current = RLEocean->getTail();
    //printf("%d ha %d",RLEocean->getTail()->getCreatureRLE()->getPosition(), current->getCreatureRLE()->getPosition());
    if(current->getCreatureRLE()->gettype() == 0)
    {
        int firstPos = current->getCreatureRLE()->getPosition();
        current->setNumber(pos - firstPos);
        CreatureRLE* SharktoAdd = new SharkRLE(pos, feeding, this);
        RLEocean->add(SharktoAdd, 1);
        CreatureRLE* EmptytoAdd = new EmptyRLE(pos+1, this);
        RLEocean->add(EmptytoAdd, this->getHeight()*this->getWidth()-pos-1);
        checkDuplicates();
        moving = RLEocean->getHead();
        check();
        return;
    }
    else
    {
        cout<<"index already occupied"<<endl;
        return;
    }
}
/**
 *  check() walks through the run-length encoding and prints an error message
 *  if two consecutive runs have the same contents, or if the sum of all run
 *  lengths does not equal the number of cells in the ocean.
 */

void RunLengthEncoding::check()
{
    DoubleLinkedListNode* current = RLEocean->getHead();
    int typeBefore = current->getCreatureRLE()->gettype();
    int starveBefore = current->getCreatureRLE()->getStarve();
    int counter = current->getNumber();
    current = current->getNext();
    while(current != NULL)
    {
        if(current->getCreatureRLE()->gettype() == typeBefore && typeBefore != 1)
        {
            printf("ERROR in RLE !!! Similar Types\n");
            return;
        }
        if(typeBefore == 1 && current->getCreatureRLE()->gettype() == 1 && current->getCreatureRLE()->getStarve() == starveBefore)
        {
            printf("ERROR in RLE !!! Similar Starve Time\n");
            return;
        }
        if(current->getNumber() <= 0 )
        {
            printf("ERROR in RLE !!! Zero Number\n");
            return;
        }
        counter = counter + current->getNumber();
        typeBefore = current->getCreatureRLE()->gettype();
        starveBefore = current->getCreatureRLE()->getStarve();
        current = current->getNext();
    }
    if(counter != this->getWidth()*this->getHeight())
    {
        printf("ERROR in RLE !!! Missing Inputs\n");
        return;
    }
}

void RunLengthEncoding::view()
{
    RLEocean->print();
}
void RunLengthEncoding::checkDuplicates()
{
    DoubleLinkedListNode* current = RLEocean->getHead();
    if(current != NULL)
    {
        DoubleLinkedListNode* next = RLEocean->getHead()->getNext();
        int index = 0;
        while(next != NULL)
        {
            int currentContents = current->getCreatureRLE()->gettype();
            int nextContents = next->getCreatureRLE()->gettype();
            if(current->getNumber() == 0)
            {
                RLEocean->removeNode(index);
                current = next->getPrevious();
                index--;
            }
            else if(currentContents == nextContents && currentContents != 1)
            {
                current->setNumber(current->getNumber()+next->getNumber());
                RLEocean->removeNode(index+1);
                next = current->getNext();
            }
            else if(currentContents == nextContents && currentContents == 1)
            {
                if(current->getCreatureRLE()->getStarve() == next->getCreatureRLE()->getStarve())
                {
                    current->setNumber(current->getNumber()+next->getNumber());
                    RLEocean->removeNode(index+1);
                    next = current->getNext();
                }
                else
                {
                    index++;
                    current = next;
                    next = next->getNext();
                }
            }
            else
            {
                index++;
                current = next;
                next = next->getNext();
            }
        }
        if(current->getNumber() == 0)
        {
            //printf("%d",RLEocean->getSize());
            RLEocean->removeNode(index);
        }
    }
}
RunLengthEncoding* RunLengthEncoding :: timeStep()
{
    RunLengthEncoding* sea = new RunLengthEncoding(width, height, starveTime);
    DoubleLinkedListNode* current = RLEocean->getHead();
    while(current != NULL)
    {
        for(int i=0; i<current->getNumber(); i++)
        {
            current->getCreatureRLE()->checkSurroundings(current->getCreatureRLE()->getPosition() + i, sea);
        }
        current = current->getNext();
    }
    return sea;
}

void RunLengthEncoding::newXY(int* x, int* y)
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
DoubleLinkedList* RunLengthEncoding::getRLEocean()
{
    return RLEocean;
}
