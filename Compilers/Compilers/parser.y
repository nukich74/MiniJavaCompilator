%{
#include <iostream>

#define YYSTYPE int

extern "C" int yylex();
extern "C" int yyparse();
void yyerror(const char *);
%}

%union{
	int ival;
}

%left '<' '>' '='

%left '+' '-'

%left '*' '/'

%left UMINUS '!'

%left '.' '[' ']'

%token CLASS

%token PUBLIC

%token STATIC

%token VOID

%token MAIN

%token EXTENDS

%token RETURN

%token ELSE

%token IF

%token WHILE

%token SYSTEM_OUT_PRINTLN

%token LENGTH

%token TRUE

%token FALSE

%token NEW

%token THIS

%token ID

%token INTEGER_LITERAL

%token STRING

%token BOOLEAN

%token <ival> INT


%%
Program: 
	MainClass
	| MainClass ClassDecls
	;
ClassDecls:
	ClassDecl
	| ClassDecls ClassDecl
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statement '}' '}'
ClassDecl:
	CLASS ID '{' '}'
	| CLASS ID '{' VarDecls '}'
	| CLASS ID '{' VarDecls MethodDecls '}'
	| CLASS ID '{' MethodDecls '}'
	;
VarDecls:
	VarDecl
	| VarDecls VarDecl
	;
VarDecl:
	Type ID ';'
	| Type ID error ';'
	;
MethodDecls:
	MethodDecl
	| MethodDecl MethodDecl
	;
MethodDecl:
	PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}'
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls RETURN Exp ';' '}'
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}'
	| PUBLIC Type ID '(' FormalList ')' '{' Statements RETURN Exp ';' '}'
	| PUBLIC Type ID '(' ')' '{' RETURN Exp ';' '}'
	| PUBLIC Type ID '(' ')' '{' VarDecls RETURN Exp ';' '}'
	| PUBLIC Type ID '(' ')' '{' VarDecls Statements RETURN Exp ';' '}'
	| PUBLIC Type ID '(' ')' '{' Statements RETURN Exp ';' '}'

	;
FormalList:
	Type ID
	| Type ID FormalRest
	;
FormalRest:
	',' Type ID
	| FormalRest ',' Type ID
	;
Type:
	INT
	| INT '[' ']'
	| BOOLEAN
	| ID
	;
Statements:
	Statement
	| Statements Statement
	;
Statement:
	ID '=' Exp ';'
	| ID '[' Exp ']' '=' Exp ';'
	| SYSTEM_OUT_PRINTLN '(' Exp ')' ';'
	| '{' '}'
	| '{' Statements '}'
	| IF '(' Exp ')' Statement ELSE Statement
	| WHILE '(' Exp ')' Statement
	| error ';' { std::cout << "Statement error at : " << @1.first_line << ' ' << @1.first_column << std::endl; }
	| '{' error '}' { std::cout << "Statement error at : " << @1.first_line << ' ' << @1.first_column << std::endl; }
	;

Exp:
	Exp '*' Exp
	| Exp '+' Exp
	| Exp '/' Exp
	| Exp '-' Exp
	| '-' Exp %prec UMINUS
	| Exp '[' Exp ']'
	| Exp '.' LENGTH
	| Exp '.' ID '(' ExpList ')'
	| Exp '.' ID '(' ')'
	| INTEGER_LITERAL
	| TRUE
	| FALSE
	| ID
	| THIS
	| NEW INT '[' Exp ']'
	| NEW ID '(' ')'
	| '!' Exp
	| '(' Exp ')'
	;
ExpList:
	Exp
	| Exp ExpRest
	;
ExpRest:
	',' Exp
	| ExpRest ',' Exp
	;
	
%%

void yyerror( const char* str )
{
	std::cout << str << std::endl;
}

int main() {
	while( yyparse() != 0 );
	return 0;
}