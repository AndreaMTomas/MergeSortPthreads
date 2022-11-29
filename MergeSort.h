#ifndef MERGESORT_H_
#define MERGESORT_H_

template<class T> void mergeSort(T* begin, T* end);
template<class T> void merge(T* begin, T* mid, T* end);
template<class T> bool isSorted(T* begin, T* end);

unsigned valuesSorted = 0;

template<class T>
void mergeSort(T* begin, T* end) {
    // If we have 0 or 1 value we are done
    if((end - begin) <= 1) {
        valuesSorted++;
        return;
    }
    else {
        // Count the number of items
        auto numItems = (end - begin);
        // Define mid as number of items / 2 + begining
        T* mid = begin + (numItems/2);

        // Sort Left Sub Array
        mergeSort(begin, mid);
        // Sort Right Sub Array
        mergeSort(mid, end);
        // Merge Left & Right Sub Arrays
        merge(begin,mid,end);
    }
}

template<class T>
void merge(T* begin, T* mid, T* end) {
    // Set the beginning for our right subArray
    T* secondBegin = mid;

    // While our each of our beginning don't reach their ends
    while( begin != mid && secondBegin != end ) {
        // Using the idea that both sub-arrays are now sorted we
        // cycle through our left sub array looking for a space 
        // for the values in-place
        if(*begin <= *secondBegin)
            begin++;
        else {
            // If we reach a value on the left that is bigger than
            // those on the right we will try to shift everything
            // to the right by one and place the value at the beginning
            T val = *secondBegin;
            T* place = secondBegin;

            // Right shift every value
            while(place != begin){
                *place = *(place - 1);
                place--;
            }
            *begin = val;

            // Move our left begin, left end, and right begin forward
            begin++;
            mid++;
            secondBegin++;
        }
    }

}

template<class T>
bool isSorted(T* begin, T* end) {
    T* current = begin;
    bool returnVal = true;
    while(current != (end-1) && returnVal) {
        if(*current <= *(current+1))
            current++;
        else
            returnVal = false;
    }

    return returnVal;
}

#endif