#include<stdio.h>
#include<stdlib.h>

#define FILENAME "data1d-100000"
#define ARR_SIZE 100000

int arr[ARR_SIZE] = {0};

void insertion(){
    FILE *fp = fopen(FILENAME, "rb");
    size_t nread = fread((void *)arr, sizeof(int), ARR_SIZE, fp);
    int c, d, t;
    for(c = 1 ; c <= ARR_SIZE - 1; c++){
        d = c;
        while(d > 0 && arr[d] < arr[d-1]){
            t = arr[d];
            arr[d] = arr[d-1];
            arr[d-1] = t;
            d--;
        }
    }
}

int main(){
    insertion();
    
    int i;
    for(i = 0 ; i < ARR_SIZE ; i++) printf("%d\n", arr[i]);
    
    return 0;
}
