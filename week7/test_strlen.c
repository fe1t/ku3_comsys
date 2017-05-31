#include<stdio.h>
#include<strings.h>

int main(){
    char buf[1000] = { 0 };
    FILE *fp = fopen("hello_test.txt", "rb");
    size_t nread = fread(buf, sizeof(char), 5, fp);
    fseek(fp, -5, SEEK_CUR);
    printf("%c\n", fgetc(fp));
    printf("%c\n", fgetc(fp));
    printf("%c\n", fgetc(fp));

    return 0;
}
