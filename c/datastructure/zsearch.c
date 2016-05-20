#include "zsearch.h"
int zbinary_search(int a[], int value, int start, int end)
{
    int middle;

    do{
        middle = (start+end)/2; 
        if(a[middle] == value) {
            return middle; 
        } 

        //no find
        if(middle == start || middle == end)
            break;

        if(a[middle] > value) {
            end = middle; 
        } else {
            start = middle; 
        }
    }while(start<end);

    return -1;
}
