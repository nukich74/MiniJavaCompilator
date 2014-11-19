%{
#include <iostream>
#include <common.h>

extern "C" int yylex();
void yyerror( void**, int*, const char *);

%}

%parse-param {void** root}

%parse-param {int* hasError}

%error-verbose

%union{
	int ival;
	char sval[255];
	void* pval;
}

%left '&'

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

%token <sval> ID

%token <ival> INTEGER_LITERAL

%token STRING

%token BOOLEAN

%token INT

%type<pval> Program MainClass ClassDecls ClassDecl Statements Statement VarDecls VarDecl MethodDecls MethodDecl Type
			FormalList Exp FormalRest ExpList ExpRest
%%

Program: 
	MainClass { *root = new CProgram( static_cast<CMainClass*>( $1 ), 0 ); }
	| MainClass ClassDecls { *root = new CProgram( static_cast<CMainClass*>( $1 ), static_cast<CClassDeclList*>( $2 ) ); }
	;
ClassDecls:
	ClassDecl { $$ = new CClassDeclList( 0, static_cast<CClassDecl*>( $1 ) ); }
	| ClassDecls ClassDecl { $$ = new CClassDeclList( static_cast<CClassDeclList*>( $1 ), static_cast<CClassDecl*>( $2 ) ); }
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements '}' '}' { $$ = new CMainClass( $2, $12, static_cast<CStatementList*>( $15 ) ); }
	| CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements error '}' '}' { *hasError = 1; std::cout << "Syntax error : incorrect symbols in Main function in line : " << @16.first_line << std::endl; }
ClassDecl:
	CLASS ID '{' '}' { $$ = new CClassDecl( $2, 0, 0, "" ); }
	| CLASS ID '{' VarDecls '}' { $$ = new CClassDecl( $2, static_cast<CVarDeclList*>( $4 ), 0, "" ); }
	| CLASS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl( $2, static_cast<CVarDeclList*>$4, static_cast<CMethodDeclList*>( $5 ), "" ); }
	| CLASS ID '{' MethodDecls '}' { $$ = new CClassDecl( $2, 0, static_cast<CMethodDeclList*>( $4 ), "" ); }
	| CLASS ID EXTENDS ID '{' '}' { $$ = new CClassDecl( $2, 0, 0, $4 ); }
	| CLASS ID EXTENDS ID '{' VarDecls '}' { $$ = new CClassDecl( $2, static_cast<CVarDeclList*>( $6 ), 0, $4 ); }
	| CLASS ID EXTENDS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl( $2, static_cast<CVarDeclList*>( $6 ), static_cast<CMethodDeclList*>( $7 ), $4 ); }
	| CLASS ID EXTENDS ID '{' MethodDecls '}' { $$ = new CClassDecl( $2, 0, static_cast<CMethodDeclList*>( $6 ), $4 ); }
	;
VarDecls:
	VarDecl { $$ = new CVarDeclList( 0, static_cast<CVarDecl*>( $1 ) ); }
	| VarDecls VarDecl { $$ = new CVarDeclList( static_cast<CVarDeclList*>( $1 ) , static_cast<CVarDecl*>( $2 ) ); }
	;
VarDecl:
	Type ID ';' { $$ = new CVarDecl( static_cast<CType*>( $1 ), $2 ); }
	| Type error ';' { *hasError = 1; std::cout << "Syntax error : incorrect variable definition in line : " << @2.first_line << std::endl; }
	;
MethodDecls:
	MethodDecl { $$ = new CMethodDeclList( 0, static_cast<CMethodDecl*>( $1 ) ); }
	| MethodDecls MethodDecl { $$ = new CMethodDeclList( static_cast<CMethodDeclList*>( $1 ), static_cast<CMethodDecl*>( $2 ) ); }
	;
MethodDecl:
	PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, static_cast<CFormalList*>( $5 ), 0, 0, static_cast<IExp*>( $9 ) ); }
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, static_cast<CFormalList*>( $5 ), static_cast<CVarDeclList*>( $8 ), 0, static_cast<IExp*>( $10 ) ); }
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, static_cast<CFormalList*>( $5 ), static_cast<CVarDeclList*>( $8 ), static_cast<CStatementList*>( $9 ), static_cast<IExp*>( $11 ) ); }
	| PUBLIC Type ID '(' FormalList ')' '{' Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, static_cast<CFormalList*>( $5 ), 0, static_cast<CStatementList*>( $8 ), static_cast<IExp*>( $10 ) ); }
	| PUBLIC Type ID '(' ')' '{' RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, 0, 0, 0, static_cast<IExp*>( $8 ) ); }
	| PUBLIC Type ID '(' ')' '{' VarDecls RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, 0, static_cast<CVarDeclList*>( $7 ), 0, static_cast<IExp*>( $9 ) ); }
	| PUBLIC Type ID '(' ')' '{' VarDecls Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, 0, static_cast<CVarDeclList*>( $7 ), static_cast<CStatementList*>( $8 ), static_cast<IExp*>( $10 ) ); }
	| PUBLIC Type ID '(' ')' '{' Statements RETURN Exp ';' '}' { $$ = new CMethodDecl( static_cast<CType*>( $2 ), $3, 0, 0, static_cast<CStatementList*>( $7 ), static_cast<IExp*>( $9 ) ); }
	;
FormalList:
	Type ID { $$ = new CFormalList( 0, static_cast<CType*>( $1 ), $2 ); }
	| Type ID FormalRest { $$ = new CFormalList( static_cast<CFormalList*>( $3 ), static_cast<CType*>( $1 ), $2 ); }
	;
FormalRest:
	',' Type ID { $$ = new CFormalList( 0, static_cast<CType*>( $2 ), $3 ); }
	| FormalRest ',' Type ID { $$ = new CFormalList( static_cast<CFormalList*>( $1 ), static_cast<CType*>( $3 ), $4 ); }
	;
Type:
	INT { $$ = new CType( "int" ); }
	| INT '[' ']' { $$ = new CType( "int[]" ); }
	| BOOLEAN { $$ = new CType( "boolean" ); }
	| ID { $$ = new CType( $1 ); }
	;
Statements:
	Statement { $$ = new CStatementList( 0, static_cast<IStatement*>( $1 ) ); }
	| Statements Statement { $$ = new CStatementList( static_cast<CStatementList*>( $1 ), static_cast<IStatement*>( $2 ) ); }
	;
Statement:
	ID '=' Exp ';' { $$ = new CAssignStatement( $1, 0, static_cast<IExp*>( $3 ) ); }
	| ID '[' Exp ']' '=' Exp ';' { $$ = new CAssignStatement( $1, static_cast<IExp*>( $3 ), static_cast<IExp*>( $6 ) ); }
	| SYSTEM_OUT_PRINTLN '(' Exp ')' ';' { $$ = new CPrintStatement( static_cast<IExp*>( $3 ) ); }
	| '{' '}' { $$ = new CCurlyBraceStatement( 0 ); }
	| '{' Statements '}' { $$ = new CCurlyBraceStatement( static_cast<IStatementList*>( $2 ) ); }
	| IF '(' Exp ')' Statement ELSE Statement { $$ = new CIfStatement( static_cast<IExp*>( $3 ), static_cast<IStatement*>( $5 ), static_cast<IStatement*>( $7 ) ); }
	| WHILE '(' Exp ')' Statement { $$ = new CWhileStatement( static_cast<IExp*>( $3 ), static_cast<IStatement*>( $5 ) ); }
	| error ';' { *hasError = 1; std::cout << "Syntax error : incorrect statement in line :" << @1.first_line << std::endl; }
	| SYSTEM_OUT_PRINTLN error ';' { *hasError = 1; std::cout << "Syntax error : incorrect Println-statement in line : " << @2.first_line << std::endl; }
	;

Exp:
	Exp '*' Exp { $$ = new CExpBinOpExp( static_cast<IExp*>( $1 ), '*', static_cast<IExp*>( $3 ) ); }
	| Exp '+' Exp { $$ = new CExpBinOpExp( static_cast<IExp*>( $1 ), '+', static_cast<IExp*>( $3 ) ); }
	| Exp '/' Exp { $$ = new CExpBinOpExp( static_cast<IExp*>( $1 ), '/', static_cast<IExp*>( $3 ) ); }
	| Exp '-' Exp { $$ = new CExpBinOpExp( static_cast<IExp*>( $1 ), '-', static_cast<IExp*>( $3 ) ); }
	| Exp '<' Exp { $$ = new CExpBinOpExp( static_cast<IExp*>( $1 ), '<', static_cast<IExp*>( $3 ) ); }
	| Exp '&' Exp { $$ = new CExpBinOpExp( static_cast<IExp*>( $1 ), '&', static_cast<IExp*>( $3 ) ); }
	| '-' Exp %prec UMINUS { $$ = new CUnMinExp( static_cast<IExp*>( $2 ) ); }
	| Exp '[' Exp ']' { $$ = new CExpWithIndex( static_cast<IExp*>( $1 ), static_cast<IExp*>( $3 ) ); }
	| Exp '.' LENGTH { $$ = new CExpDotLength( static_cast<IExp*>( $1 ) ); }
	| Exp '.' ID '(' ExpList ')' { $$ = new CExpIdExpList( static_cast<IExp*>( $1 ), $3, static_cast<IExpList*>( $5 ) ); }
	| Exp '.' ID '(' ')' { $$ = new CExpIdVoidExpList( static_cast<IExp*>( $1 ), $3 ) ; }
	| INTEGER_LITERAL { $$ = new CIntegerLiteral( $1 ); }
	| TRUE { $$ = new CTrue(); }
	| FALSE { $$ = new CFalse(); }
	| ID { $$ = new CId( $1 ); }
	| THIS { $$ = new CThis(); }
	| NEW INT '[' Exp ']' { $$ = new CNewIntExpIndex( static_cast<IExp*>( $4 ) ); }
	| NEW ID '(' ')' { $$ = new CNewId( $2 ); }
	| '!' Exp { $$ = new CNotExp( static_cast<IExp*>( $2 ) ); }
	| '(' Exp ')' { $$ = new CExpInBrackets( static_cast<IExp*>( $2 ) ); }
	;
ExpList:
	Exp { $$ = new CExpList( 0, static_cast<IExp*>( $1 ) ); }
	| Exp ExpRest { $$ = new CExpList( static_cast<CExpList*>( $2 ), static_cast<IExp*>( $1 ) ); }
	;
ExpRest:
	',' Exp { $$ = new CExpList( 0, static_cast<IExp*>( $2 ) ); }
	| ExpRest ',' Exp { $$ = new CExpList( static_cast<CExpList*>( $1 ), static_cast<IExp*>( $3 ) ); }
	;
	
%%

void yyerror( void**, int*, const char* str )
{
	std::cout << str << std::endl;
}