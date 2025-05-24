#include <stdio.h>


int main(void)
{
    int note = 1;
    switch (note) {
    case 1:
        printf("ausgezeichnet!\n");
    case 2:
        printf("gut!\n");
        break;
    default:
        printf("nicht so gut!\n");
        break;
    }
    return 0;
}