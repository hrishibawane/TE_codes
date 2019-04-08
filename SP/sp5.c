#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
E -> TE'
E' -> +TE'|e
T -> FT'
T' -> *FT'|e
F -> (E)|id
*/
void E();
void T();
void F();
void Eprime();
void Tprime();

int i=0, err=0;
char ip[20];

int main()
{
    printf("Enter an Arithmetic Equation: ");
    scanf("%s", ip);
    E();
    i==strlen(ip) && !err ? printf("Accepted...!") : printf("Rejected..!");
}

void Eprime()
{
    if(ip[i]=='+')
    {
        i++;
        T();
        Eprime();
    }
}

void Tprime()
{
    if(ip[i]=='*')
    {
        i++;
        F();
        Tprime();
    }
}

void F()
{
    if(isalnum(ip[i])) i++;
    else if(ip[i]=='(')
    {
        i++;
        E();
        if(ip[i]==')') i++;
        else err=1;
    }
    else err=1;
}

void T()
{
    F();
    Tprime();
}

void E()
{
    T();
    Eprime();
}