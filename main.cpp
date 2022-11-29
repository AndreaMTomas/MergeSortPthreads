#include <iostream>
#include <random>
#include <pthread.h>
#include "Timer.h"
#include "MergeSort.h"
#include "Struct.h"
#include "MergeSortThreaded.h"
// Note: SIZEA and mergeArray are in the Struct.h file

int main() {
    Timer mergeTimer, andreaTimer;
    srand(42);
    
    for(unsigned i = 0; i < SIZEA; i++) {
        myData.mergeArray[i] = rand() % 100;
    }
    mergeTimer.start();
    mergeSort(myData.mergeArray, &(myData.mergeArray[SIZEA]));
    mergeTimer.stop();
    std::cout << "It took " << mergeTimer.elapsed() << " seconds to sort an int array with " 
              << SIZEA << " random values." << std::endl;
    std::cout << "MergeSort() Array is sorted: " << (isSorted(myData.mergeArray, &(myData.mergeArray[SIZEA])) ? "True" : "False") << std::endl;
    
    // Assign random values
    for(unsigned i = 0; i < SIZEA; i++) {
        myData.mergeArray[i] = rand() % 100;
    }

    // Create an array of n pthreads
    pthread_t threads[myData.numberOfThreads];
    andreaTimer.start();
    for (int i = 0; i < myData.numberOfThreads; i++)
        pthread_create(&threads[i], NULL, mergeSortThreaded, (void*)NULL);
 
    // Join all threads
    for (int i = 0; i < myData.numberOfThreads; i++)
        pthread_join(threads[i], NULL);

    andreaTimer.stop();   
    std::cout << "It took " << andreaTimer.elapsed() << " seconds to sort an int array with " 
              << SIZEA << " random values by using " << myData.numberOfThreads << " pthreads." << std::endl;
    std::cout << "MergeSortThreaded() Array is sorted: " << (isSorted(myData.mergeArray, &(myData.mergeArray[SIZEA])) ? "True" : "False") << std::endl;

    return 0;
}