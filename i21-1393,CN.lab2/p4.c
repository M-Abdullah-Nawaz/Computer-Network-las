// Muhammad Abdullah Nawaz

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
unsigned int num = 0x3412;
unsigned char *ptr = (unsigned char *)&num;
 if (*ptr == 0x78) {
   printf("ordering is  little endian\n");
    } 
    else if (*ptr == 0x12) {
        printf("ordering: big endian\n");
    } 
    else {
        printf("Unknown byte ordering\n");
    }

    printf("Individual bytes are showm as :\n");
    for (int i = 0; i < sizeof(num); i++) {
        printf("Byte %d: 0x%x\n",i+1, *(ptr+i));
    }

    return 0;
}

