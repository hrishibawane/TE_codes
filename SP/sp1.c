#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 50

// general variables
char buff[MAX];
int lc = 0, sym = 0, lit = 1;
int symHash[30];

//flags
int potf=0, motf=0, regf=0, conf=0, litf=0, symf=0;

//statement types
char* pot[] = {"START", "END", "NULL"};
char* mot[] = {"MOVER", "MOVEM", "STOP", "READ", "PRINT", "ADD", "SUB", "NULL"};
char* reg[] = {"AREG", "BREG", "CREG", "DREG", "NULL"};

int search(char* arr[], char t[])
{
    int i=0;
    while(!strcmp(arr[i], "NULL")==0)
    {
        if(strcmp(arr[i], t)==0) return i;
        i++;
    }
    
    return -1;
}

int main()
{
    FILE *fp1, *fp2, *fp3, *fp4;
    fp1 = fopen("input.txt", "r+");
    fp2 = fopen("ic.txt", "w+");
    fp3 = fopen("symtab.txt", "w+");
    fp4 = fopen("littab.txt", "w+");

    fprintf(fp3, "No.\tSymbol\tAddress\n");
    fprintf(fp4, "No.\tLiteral\tAddress\n");
    
    while(fgets(buff, 50, fp1))
    {
        printf("%s", buff);
        char *token = strtok(buff, " ,\n");

        while(token!=NULL)
        {
            //printf("%s\n", token);
            if(search(pot, token)!=-1)
            {
                int idx = search(pot, token);
                if(idx==0) fprintf(fp2, "(AD,%d)", idx);
                else fprintf(fp2, "%d: (AD,%d)", lc, idx);

                potf=1, motf=0, regf=0, conf=0, litf=0, symf=0;
            }
            else if(search(mot, token)!=-1)
            {
                if(potf) fprintf(fp2, "\n");
                fprintf(fp2, "%d: (IS,%d)", lc, search(mot, token));
                potf=0, motf=1, regf=0, conf=0, litf=0, symf=0;
            }
            else if(search(reg, token)!=-1)
            {
                fprintf(fp2, "(REG,%d)", search(reg, token));
                if(regf||conf||symf) fprintf(fp2, "\n"), lc++;
                potf=0, motf=0, regf=1, conf=0, litf=0, symf=0;
            }
            else if(isdigit(token[0]))
            {
                if(potf) sscanf(token, "%d", &lc), lc--;
                fprintf(fp2, "(C,%s)", token);
                if(potf||regf) fprintf(fp2, "\n"), lc++;
                potf=0, motf=0, regf=0, conf=1, litf=0, symf=0;
            }
            else
            {
                if(strlen(token)==4)
                {
                    fprintf(fp4, "%d\t%s\t%d\n", lit, token, lc);
                    fprintf(fp2, "(L,%d)\n", lit);
                    lc++, lit++;
                    potf=0, motf=0, regf=0, conf=0, litf=1, symf=0;
                }
                else
                {
                    char c = token[0];
                    if(token[1]==':')
                    {
                        symHash[c-'A'] = lc;
                        sym++;
                    }
                    else
                    {
                        if(!symHash[c-'A'])
                            symHash[c-'A'] = -1;
                        fprintf(fp2, "(S,%d)", sym);
                    }

                    //fprintf(fp3, "%d\t%c\t%d\n", sym, c, lc);
                    
                    if(regf) fprintf(fp2,"\n"), lc++;
                    potf=0, motf=0, regf=0, conf=0, litf=0, symf=1;
                }
            }
            token = strtok(NULL, " ,\n");
        }
    }

    int k=1;
    for(int i=0; i<30; i++)
    {
        if(symHash[i]!=0)
            fprintf(fp3, "%d\t%c\t%d\n", k, (char)(i+65), symHash[i]),
            k++;
    }
    
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
}