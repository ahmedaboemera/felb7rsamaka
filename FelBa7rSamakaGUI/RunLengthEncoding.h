#ifndef RUNLENGTHENCODING_H
#define RUNLENGTHENCODING_H
#include "Ocean.h"
#include "DoubleLinkedList.h"
#include "DoubleLinkedListNode.h"

class Ocean;
class DoubleLinkedList;
class DoubleLinkedListNode;
class RunLengthEncoding
{
public:
    RunLengthEncoding(int i, int j, int feeding);
    RunLengthEncoding(int i, int j, int feeding, int* runTypes, int runTypesSize, int* runLengths, int runLengthsSize);
    RunLengthEncoding(Ocean* sea);
    ~RunLengthEncoding();
    void restartRuns();
    void nextRun(int* result, int* size);
    void nextRun2(int* result, int* size, int* feeding);
    Ocean* toOcean();
    void view();
    int getWidth();
    int getHeight();
    int getStarveTime();
    void addFish(int x, int y);
    void addFishComplicated(int x, int y);
    void nodeSurroundingsContents(int coordinates[8][2], int* emptyCount, int* sharkCount, int* fishCount);
    void addShark(int x, int y);
    void addShark(int x, int y, int feeding);
    void checkDuplicates();
    RunLengthEncoding* timeStep();
    void newXY(int* x, int* y);
    DoubleLinkedList* getRLEocean();
protected:
private:
    int width;
    int height;
    int starveTime;
    DoubleLinkedListNode* moving;
    DoubleLinkedList* RLEocean;
    void check();
    /*
     *  Define any variables associated with a RunLengthEncoding object here.
     *  These variables MUST be private.
     */
};

#endif // RUNLENGTHENCODING_H
