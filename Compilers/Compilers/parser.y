%{
#include <iostream>
#include <common.h>

extern "C" int yylex();
extern "C" int yyparse();
void yyerror(const char *);
%}

%error-verbose

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
	MainClass { $$ = new CProgram( $1, 0 ); }
	| MainClass ClassDecls { $$ = new CProgram( $1, $2 ); }
	;
ClassDecls:
	ClassDecl { $$ = new CClassDeclList( 0, $1 ); }
	| ClassDecls ClassDecl { $$ = new CClassDeclList( $1, $2 ); }
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements '}' '}' { $$ = new CMainClass( $2, $12, $15 ); }
	| CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements error '}' '}' { std::cout << "Syntax error : incorrect symbols in Main function in line : " << @16.first_line << std::endl; }
ClassDecl:
	CLASS ID '{' '}' { $$ = new CClassDecl( $2, 0, 0, 0 ); }
	| CLASS ID '{' VarDecls '}' { $$ = new CClassDecl( $2, $4, 0, 0 ); }
	| CLASS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl( $2, $4, $5, 0 ); }
	| CLASS ID '{' MethodDecls '}' { $$ = new CClassDecl( $2, 0, $4, 0 ); }
	| CLASS ID EXTENDS ID '{' '}' { $$ = new CClassDecl( $2, 0, 0, $4 ); }
	| CLASS ID EXTENDS ID '{' VarDecls '}' { $$ = new CClassDecl( $2, $6, 0, $4 ); }
	| CLASS ID EXTENDS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl( $2, $6, $7, $4 ); }
	| CLASS ID EXTENDS ID '{' MethodDecls '}' { $$ = new CClassDecl( $2, 0, $6, $4 ); }
	;
VarDecls:
	VarDecl { $$ = new CVarDeclList( 0, $1 ); }
	| VarDecls VarDecl { $$ = new CVarDeclList( $1, $2 ); }
	;
VarDecl:
	Type ID ';' { $$ = new CVarDecl( $1, $2 ); }
	| Type error ';' { std::cout << "Syntax error : incorrect variable definition in line : " << @2.first_line << std::endl; }
	;
MethodDecls:
	MethodDecl { $$ = new CMethodDeclList( 0, $1 ); }
	| MethodDecls MethodDecl { $$ = new CMethodDeclList( $1, $2 ); }
	;
MethodDecl:
	PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, 0, 0, $9 ); }
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, $8, 0, $10 ); }
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, $8, $9, $11 ); }
	| PUBLIC Type ID '(' FormalList ')' '{' Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, $5, 0, $8, $10 ); }
	| PUBLIC Type ID '(' ')' '{' RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, 0, 0, 0, $8 ); }
	| PUBLIC Type ID '(' ')' '{' VarDecls RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, 0, $7, 0, $9 ); }
	| PUBLIC Type ID '(' ')' '{' VarDecls Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, 0, $7, $8, $10 ); }
	| PUBLIC Type ID '(' ')' '{' Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( $2, $3, 0, 0, $7, $9 ); }
	;
FormalList:
	Type ID { $$ = new CFormalList( 0, $1, $2 ); }
	| Type ID FormalRest { $$ = new CFormalList( $3, $1, $2 ); }
	;
FormalRest:
	',' Type ID { $$ = new CFormalList( 0, $2, $3 ); }
	| FormalRest ',' Type ID { $$ = new CFormalList( $1, $3, $4 ); }
	;
Type:
	INT { $$ = new CType( "int", 0 ); }
	| INT '[' ']' { $$ = new CType( "int[]", 0 ); }
	| BOOLEAN { $$ = new CType( "bool", 0 ); }
	| ID { $$ = new CType( $1 ); }
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
	| error ';' { std::cout << "Syntax error : incorrect statement in line :" << @1.first_line << std::endl; }
	| SYSTEM_OUT_PRINTLN error ';' { std::cout << "Syntax error : incorrect Println-statement in line : " << @2.first_line << std::endl; }
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