%{
    #include <stdio.h>
    #include <math.h>
%}

%token NUM

%%
Exp: e
{
    printf("\nResult = %d\n", $$);
    return 0;
}

e:  e'+'e   {$$=$1+$3;}
    |e'-'e  {$$=$1-$3;}
    |e'*'e  {$$=$1*$3;}
    |e'/'e  {$$=$1/$3;}
    |e'%'e  {$$=$1%$3;}
    |'('e')'    {$$=$2;}
    |NUM    {$$=$1;}
%%

void yyerror()
{
    printf("%s", stderr);
}

int main()
{
    printf("Enter expression: ");
    yyparse();
    return 0;
}

// hrishib@hrishib-mr-zion:~/Desktop/SP$ yacc -d sp6.y
// sp6.y: warning: 25 shift/reduce conflicts [-Wconflicts-sr]
// hrishib@hrishib-mr-zion:~/Desktop/SP$ lex sp6.l
// hrishib@hrishib-mr-zion:~/Desktop/SP$ gcc lex.yy.c y.tab.c -o sp6 -w