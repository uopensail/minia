grammar minia;
options { caseInsensitive=true; }
// antlr4 -Dlanguage=Cpp minia.g4

prog                    : (start SEMI)* start EOF;

start                   : IDENTIFIER T_EQUAL expr;

expr                    : expr T_MOD expr                                                                   # ModExpr
                        | expr T_MUL expr                                                                   # MulExpr
                        | expr T_DIV expr                                                                   # DivExpr
                        | expr T_ADD expr                                                                   # AddExpr
                        | expr T_SUB expr                                                                   # SubExpr
                        | IDENTIFIER '(' ')'                                                                # RuntTimeFuncExpr
                        | IDENTIFIER '(' expr (COMMA expr)* ')'                                             # FuncExpr
                        | IDENTIFIER                                                                        # ColumnExpr
                        | STRING                                                                            # StringExpr
                        | INTEGER                                                                           # IntegerExpr
                        | DECIMAL                                                                           # DecimalExpr
                        | STRING_LIST                                                                       # StringLISTExpr
                        | INTEGER_LIST                                                                      # IntegerLISTExpr
                        | DECIMAL_LIST                                                                      # DecimalLISTExpr
                        | '(' expr ')'                                                                      # PlainExpr
                        ;

DOT                 : '.';
COMMA               : ',';
SEMI                : ';';
QUOTA               : '"';

T_EQUAL             : '=' ;
T_ADD               : '+' ;
T_SUB               : '-' ;
T_MUL               : '*' ;
T_DIV               : '/' ;
T_MOD               : '%' ;

IDENTIFIER              options { caseInsensitive=false; } : [_a-zA-Z][_a-zA-Z0-9]*; // 变量

INTEGER_LIST            : '[' (INTEGER (COMMA WS*)?)* INTEGER WS* ']' ;
INTEGER                 : '-'? '0' | [1-9] [0-9]* ;

DECIMAL_LIST            : '[' (DECIMAL (COMMA WS*)?)* DECIMAL WS* ']' ;
DECIMAL                 : '-'? ('0' | [1-9] [0-9]*) '.' [0-9]* ;

STRING_LIST             : '[' (STRING (COMMA WS*)?)* STRING WS* ']' ;

STRING options { caseInsensitive=false; } : QUOTA (ESC | SAFECODEPOINT)* QUOTA;

fragment ESC: '\\' (["\\/bfnrt] | UNICODE);
fragment UNICODE: 'u' HEX HEX HEX HEX;
fragment HEX options { caseInsensitive=false; }  : [0-9a-fA-F];
fragment SAFECODEPOINT: ~ ["\\\u0000-\u001F];

// Ignore whitespace
WS                      : [ \t\n\r] + -> skip ;
