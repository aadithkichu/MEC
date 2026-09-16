%{
#include "y.tab.h"
%}

%%
"for"       { return FOR; }
"++"        { return INC; }
"--"        { return DEC; }

"<="        { return LE; }
">="        { return GE; }
"=="        { return EQ; }
"!="        { return NE; }

[a-zA-Z]    { return ID; }
[0-9]+      { return NUM; }

[ \t]       ;
\n          { return '\n'; }
.           { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}