#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

struct litpair
{
    char lit[5];
    int addr;
};

struct litpair lp[MAX];
char buff[MAX];
int symtab[10], littab[10];

int main()
{
    FILE *fp1, *fp2, *fp3, *fp4;
    fp1 = fopen("ic.txt", "r+");
    fp2 = fopen("target.txt", "w+");
    fp3 = fopen("symtab.txt", "r+");
    fp4 = fopen("littab.txt", "r+");

    fgets(buff,MAX,fp3);
    while(fgets(buff, MAX, fp3))
    {
        int idx = buff[0]-'0';
        int addr = (buff[4]=='-') ? -1 : ((buff[4]-'0')*100) + ((buff[5]-'0')*10) + ((buff[6]-'0'));
        //printf("%d:%d\n", idx, addr);
        symtab[idx] = addr;
    }

    fgets(buff,MAX,fp4);
    while(fgets(buff, MAX, fp4))
    {
        int idx = buff[0]-'0';
        int addr = ((buff[7]-'0')*100) + ((buff[8]-'0')*10) + ((buff[9]-'0'));
        //printf("%d %d\n", idx, addr);
        littab[idx] = addr;
    }

    while(fgets(buff, MAX, fp1))
    {
        printf("%s", buff);
        char *token = strtok(buff, "()\n");
        while(token)
        {
            //printf("%s\n", token);
            int len = strlen(token);
            if(token[0]=='S')
            {
                fprintf(fp2, "%d ", symtab[token[len-1]-'0']);
            }
            else if(token[0]=='L')
            {
                fprintf(fp2, "%d ", littab[token[len-1]-'0']);
            }
            else if(token[0]!='C' && isdigit(token[strlen(token)-1]))
            {
                fprintf(fp2, "0%c ", token[strlen(token)-1]);
            }

            token = strtok(NULL, " ()\n");
        }
        fprintf(fp2, "\n");
    }

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}