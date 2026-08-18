%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tempCount = 1;
char temp[10];

int yylex();
int yyerror(char *s);
%}

%union {
    char *str;
}

%token <str> ID NUM
%type <str> expr

%left '+' '-'
%left '*' '/'

%%

stmt:
    ID '=' expr {
        printf("%s = %s\n", $1, $3);
    }
    ;

expr:
      expr '+' expr {
          sprintf(temp, "t%d", tempCount++);
          printf("%s = %s + %s\n", temp, $1, $3);
          $$ = strdup(temp);
      }

    | expr '-' expr {
          sprintf(temp, "t%d", tempCount++);
          printf("%s = %s - %s\n", temp, $1, $3);
          $$ = strdup(temp);
      }

    | expr '*' expr {
          sprintf(temp, "t%d", tempCount++);
          printf("%s = %s * %s\n", temp, $1, $3);
          $$ = strdup(temp);
      }

    | expr '/' expr {
          sprintf(temp, "t%d", tempCount++);
          printf("%s = %s / %s\n", temp, $1, $3);
          $$ = strdup(temp);
      }

    | ID {
          $$ = $1;
      }

    | NUM {
          $$ = $1;
      }
    ;

%%

int main()
{
    printf("Enter the expression:\n");
    yyparse();
    return 0;
}

int yyerror(char *s)
{
    printf("Error: %s\n", s);
    return 0;
}