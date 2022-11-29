#ifndef DATA_H
#define DATA_H
const unsigned SIZEA = 50000;
struct Data{
    int arrayPart = 0;
    int numberOfThreads = 4;
    int mergeArray[SIZEA];
};
extern Data myData;
#endif