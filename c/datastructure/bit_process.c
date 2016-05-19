#include <stdio.h>
#include <stdlib.h>

void set_bit(char *c, int bit_pos, int value)
{
    char tmp=0x1;
    tmp = tmp<<bit_pos;

    if(value) {
        *c |= tmp;      
    } else {
        tmp = ~tmp;     
        *c &= tmp;
    }
}

int get_bit(char c, int bit_pos)
{
    char ret = c;           
    ret = ret>>bit_pos;
    ret = ret<<7;
    if(ret) return 1;
    return 0;
}

void printf_bit(const char a[], int len) 
{
    for(int i=0; i<len; ++i) {
        for(int j=7; j>=0; --j) {
            printf("%d", get_bit(a[i], j));
        }   
        printf("\t");
    } 
}
/*
int main()
{
    unsigned int i=1;
    printf_bit(&i, sizeof(i));
    printf("\n");

    char a[] = {'0', '1', 'a', 'A'};
    printf_bit(a, sizeof(a));
    printf("\n");

    char b[] = {'a'};
    printf_bit(b, sizeof(b));
    printf("\n");

    set_bit(&b[0], 1, 1);
    printf_bit(b, sizeof(b));
    printf("\n");

    set_bit(&b[0], 1, 0);
    printf_bit(b, sizeof(b));
    printf("\n");

    return 0;
}
*/
