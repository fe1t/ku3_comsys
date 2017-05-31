#include<stdio.h>

int main(){
    int arr[100] = {0};
    int length;
    // printf("Enter length(up to 100): ");
    scanf("%d", &length);
    
    for(int i = 0 ; i < length ; i++) scanf("%d", &arr[i]);

    for(int i = 0 ; i < length ; i++){
        int mem_pos = i;
        for(int j = i + 1 ; j < length ; j++){
            if(arr[j] < arr[i] && arr[j] < arr[mem_pos]) mem_pos = j;
        }
        int temp = arr[i];
        arr[i] = arr[mem_pos];
        arr[mem_pos] = temp;
    }

    for(int i = 0 ; i < length ; i++) printf("%d ", arr[i]);

    return 0;
}
