#include <stdio.h>
int main(int argc, char *argv[]){
    FILE *fp;
    int count = 0;
    char str1[30];
    
    fp = fopen(argv[1], "r");
    while(fscanf(fp, "%s", str1) == 1){
        count++;
    }
    fclose(fp);
    printf("%d\n", count);
    return 0;
}
