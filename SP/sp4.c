#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *kw[] = {"int", "main", "float", "void", "return", "double","NULL"};
char *op[] = {"+", "-", "*", "/", "=", "^", "NULL"};
char *tr[] = {"(", ")", ";", ",", "{", "}", "NULL"};

int search(char *arr[], char buff[])
{
    int i=0;
    while(strcmp(arr[i], "NULL")!=0)
    {
        if(strcmp(arr[i], buff) == 0) return 1;
        i++;
    }
 
    return -1;
}

int main()
{
    FILE *fp = fopen("lexinput.txt", "r+");
    char buff[10];
    while(fscanf(fp, "%s", buff) == 1)
    {
        if(search(kw, buff) != -1) printf("%s \t keyword \n", buff);
        else if(search(op, buff) != -1) printf("%s \t operator \n", buff);
        else if(search(tr, buff) != -1) printf("%s \t terminal \n", buff);
        else printf("%s \t identifier \n", buff);
    }
}
