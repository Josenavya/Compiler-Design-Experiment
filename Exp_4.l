%{
#include<stdio.h>
#include "valvar.tab.h"
%}

%%

[a-zA-Z]     { return LET; }
[0-9]        { return DIG; }
[ \t]        ;
\n           { return 0; }

%%

int yywrap()
{
    return 1;
}