#include "zsort.h"
void insertion_sort()
{
    int a[] = {3, 4, 6, 1, 8, 2, 7, 9, 5, 0};
    for(int j=2; j<10; ++j)	{
        int key = a[j];
        int i=j-1;
        while(i>=0 && a[i] > key) {
            a[i+1] = a[i];	
            i--;
        }

        a[i+1] = key;
    }

    for(int i=0; i<10; ++i) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}


void bubble_sort()
{
    int a[] = {3, 4, 6, 1, 8, 2, 7, 9, 5, 0};
    for(int i=0; i<10; ++i) {
        int flag = a[i];
        for(int j=9; j>=i; --j) {
            if(flag<a[j]){
                a[i] = a[j];
                a[j] = flag;
                flag = a[i];	
            }		
        }
    }

    for(int i=0; i<10; ++i) {
        printf("%d\t", a[i]);
    }
    printf("\n");
}


void zsort(int a[], int i, int j)
{
    int start = i;
    int end = j;
    int flag = a[i];	

    while(i<j) {
        while(i<j && flag < a[j]) {
            j--;			
        }

        if(i<j)	
            a[i] = a[j];

        while(i<j && flag > a[i]) {
            i++;
        }

        if(i<j)
            a[j] = a[i];	
    }

    a[j]=flag;	

    if(start<j) zsort(a, start, j-1);	
    if(i<end) zsort(a,  i+1, end);	
}

int partition(int a[], int i, int j)
{
    int value = a[i];
    i--;
    j++;

    while(1) {
        do{
            j--;
        } while(a[j]>value);

        do{
            i++;
        }while(a[i]<value);

        if(i>=j) {
            break;
        } else {
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        } 
    }

    return j;
}

void zqsort(int a[], int i, int j)
{
    int k; 
    while(i<j) {
        k = partition(a, i, j);
        zqsort(a, i, k); 
        i=k+1;
    }
}

