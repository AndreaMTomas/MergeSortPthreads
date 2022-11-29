#include <iostream>
#include "Struct.h"
#ifndef MERGESORTTHREADED_H_
#define MERGESORTTHREADED_H_

void mergeThreaded(int a[], int leftBegin, int leftEnd, int rightBegin, int rigthEnd);
void mergeSort(int a[], int begin, int end);
void* mergeSortThreaded(void* arg);
void mergeParts(int a[]);
Data myData;

/**
 * @brief       Merge sort algorithm.
 *
 * @detailed    This function sorts an array by implementing the Merge sort algorithm,
 *              it was addapted to make it work with pthreads for this program.
 *
 * @param        parameter1     Array to be sorted
 * @param        parameter2     Begining of left sub array
 * @param        parameter3     End of left sub array 
 * @param        parameter4     Begining of right sub array
 * @param        parameter5     End of right sub array
 *
**/

void mergeThreaded(int a[], int leftBegin, int leftEnd, int rightBegin, int rigthEnd){ 
    int length = rigthEnd-leftBegin+1;
    int* temp = new int[length];
    int left = leftBegin;
    int right = rightBegin;
    for (int i = 0; i < length; ++i) { 
        if (left > leftEnd)
            temp[i] = a[right++];
        else if (right > rigthEnd)
            temp[i] = a[left++];
        else if (a[left] <= a[right])
            temp[i] = a[left++];
        else
            temp[i] = a[right++]; 
    }
    
    for (int i=0; i< length; ++i) 
        a[leftBegin++] = temp[i];
    
    delete[] temp;
}

/**
 * @brief       Merge sort algorithm.
 *
 * @detailed    This function calculates the middle part of a given array and
 *              calls the mergeThreaded function to merge the sorted sections of the array.
 *
 * @param        parameter1     Array to be sorted
 * @param        parameter2     Begining of array
 * @param        parameter2     End of sub array
 *
**/

void mergeSort(int a[], int begin, int end){
    if (begin >= end){
        return;
    }     
    else {
        // Let mid be:
      int mid = (begin + end)/2;     
      // Sort first part from begining to mid
      mergeSort(a, begin, mid);       
      // Sort second part from mid to end
      mergeSort(a, mid+1, end);  
      // Merge those parts   
      mergeThreaded(a, begin, mid, mid+1,end);
    }
}
 
/**
 * @brief       Merge sort algorithm used for pthreads.
 *
 * @detailed    This function divides the array into n parts to be sorted by n number 
 *              of threads. If the part that is being sorted equals to the number
 *              of threads, it will call the function mergeSort to merge all the parts
 *              that were sorted by each thread.
 *
 * @param        parameter1     arguments passed from the pthread creation.
 *
**/

void* mergeSortThreaded(void* arg){
    if(myData.arrayPart == myData.numberOfThreads){
        mergeSort(myData.mergeArray, 0 , SIZEA-1);
    }
    
    int begin = myData.arrayPart * (SIZEA / myData.numberOfThreads);
    int end = (myData.arrayPart + 1) * (SIZEA / myData.numberOfThreads) - 1;
    myData.arrayPart++;
    if(myData.arrayPart == myData.numberOfThreads){
        mergeSort(myData.mergeArray, 0 , SIZEA-1);
    }
    // evaluating mid point
    int mid = begin + (end - begin) / 2;
    if (begin < end) {
        mergeSort(myData.mergeArray,begin, mid);
        mergeSort(myData.mergeArray,mid + 1, end);
        mergeThreaded(myData.mergeArray,begin, mid, mid+1 ,end);

    }
    return 0;
}

/**
 * @brief       Used to merge all the parts of the array one last time.
 *
 * @detailed    This function is called in main after joining the threads, this 
 *              function helps to join all the sorted parts.
 *
 * @param        parameter1     Array to be sorted
 *
**/
void mergeParts(int a[]){
    mergeSort(a, 0, SIZEA - 1);
}
#endif