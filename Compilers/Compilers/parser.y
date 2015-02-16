%{
#include <iostream>
#include <memory>
#include <common.h>
#include <Location.h>
extern "C" int yylex();
using std::make_shared;
using std::shared_ptr;

void yyerror( std::shared_ptr<CProgram>&, int*, const char *);
%}

%code requires { #include <common.h> }

%code requires { #include <memory> }

%parse-param { std::shared_ptr<CProgram>& root }

%parse-param { int* hasError }

%error-verbose

%union{
	int ival;
	char sval[255];
	CProgram* program;
	CMainClass* mainClass;
	CClassDeclList* classDecls;
	CClassDecl* classDecl;
	CStatementList* statements;
	IStatement* statement;
	CVarDeclList* varDecls;
	CVarDecl* varDecl;
	CMethodDeclList* methodDecls;
	CMethodDecl* methodDecl;
	CType* type;
	CFormalList* formalList;
	CExpList* expList;
	IExp* exp;
}

%left '&'

%left '<' '='

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

%type<program> Program

%type<mainClass> MainClass

%type<classDecls> ClassDecls

%type<classDecl> ClassDecl

%type<statements> Statements

%type<statement> Statement

%type<varDecls> VarDecls

%type<varDecl> VarDecl

%type<methodDecls> MethodDecls

%type<methodDecl> MethodDecl

%type<type> Type

%type<formalList> FormalList FormalRest

%type<expList> ExpList ExpRest

%type <exp> Exp

%%
Program: 
	MainClass { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); root = make_shared<CProgram>( $1, nullptr, location ); }
	| MainClass ClassDecls { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); root = make_shared<CProgram>( $1, $2, location ); }
	;
ClassDecls:
	ClassDecl { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CClassDeclList( 0, $1, location ); }
	| ClassDecls ClassDecl { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CClassDeclList( $1, $2, location ); }
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements '}' '}' { CLocation location( @1.first_line, @1.first_column, @17.last_line, @17.last_column ); $$ = new CMainClass( $2, $12, $15, location ); }
	| CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements error '}' '}' { *hasError = 1; std::cout << "Syntax error : incorrect symbols in Main function from " << @16.first_line << ":" << @16.first_column << " to " << @16.last_line << ":" << @16.last_column << std::endl; $$ = 0; }
ClassDecl:
	CLASS ID '{' '}' { CLocation location( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CClassDecl( $2, 0, 0, "", location ); }
	| CLASS ID '{' VarDecls '}' { CLocation location( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CClassDecl( $2, $4, 0, "", location ); }
	| CLASS ID '{' VarDecls MethodDecls '}' { CLocation location( @1.first_line, @1.first_column, @6.last_line, @6.last_column ); $$ = new CClassDecl( $2, $4, $5, "", location ); }
	| CLASS ID '{' MethodDecls '}' { CLocation location( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CClassDecl( $2, 0, $4, "", location ); }
	| CLASS ID EXTENDS ID '{' '}' { CLocation location( @1.first_line, @1.first_column, @6.last_line, @6.last_column ); $$ = new CClassDecl( $2, 0, 0, $4, location ); }
	| CLASS ID EXTENDS ID '{' VarDecls '}' { CLocation location( @1.first_line, @1.first_column, @7.last_line, @7.last_column ); $$ = new CClassDecl( $2, $6, 0, $4, location ); }
	| CLASS ID EXTENDS ID '{' VarDecls MethodDecls '}' { CLocation location( @1.first_line, @1.first_column, @8.last_line, @8.last_column ); $$ = new CClassDecl( $2, $6, $7, $4, location ); }
	| CLASS ID EXTENDS ID '{' MethodDecls '}' { CLocation location( @1.first_line, @1.first_column, @7.last_line, @7.last_column ); $$ = new CClassDecl( $2, 0, $6, $4, location ); }
	;
VarDecls:
	VarDecl { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CVarDeclList( 0, $1, location ); }
	| VarDecls VarDecl { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CVarDeclList( $1, $2, location ); }
	;
VarDecl:
	Type ID ';' { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CVarDecl( $1, $2, location ); }
	| Type error ';' { *hasError = 1; std::cout << "Syntax error : incorrect variable definition from " << @2.first_line << ":" << @2.first_column << " to " << @2.last_line << ":" << @2.last_column << std::endl; $$ = 0; }
	;
MethodDecls:
	MethodDecl { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CMethodDeclList( 0, $1, location ); }
	| MethodDecls MethodDecl { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CMethodDeclList( $1, $2, location ); }
	;
MethodDecl:
	PUBLIC Type ID '(' FormalList ')' '{' RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @11.last_line, @11.last_column ); $$ = new CMethodDecl( $2, $3, $5, 0, 0, $9, location ); }
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @12.last_line, @12.last_column ); $$ = new CMethodDecl( $2, $3, $5, $8, 0, $10, location ); }
	| PUBLIC Type ID '(' FormalList ')' '{' VarDecls Statements RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @13.last_line, @13.last_column ); $$ = new CMethodDecl( $2, $3, $5, $8, $9, $11, location ); }
	| PUBLIC Type ID '(' FormalList ')' '{' Statements RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @12.last_line, @12.last_column ); $$ = new CMethodDecl( $2, $3, $5, 0, $8, $10, location ); }
	| PUBLIC Type ID '(' ')' '{' RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @10.last_line, @10.last_column ); $$ = new CMethodDecl( $2, $3, 0, 0, 0, $8, location ); }
	| PUBLIC Type ID '(' ')' '{' VarDecls RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @11.last_line, @11.last_column ); $$ = new CMethodDecl( $2, $3, 0, $7, 0, $9, location ); }
	| PUBLIC Type ID '(' ')' '{' VarDecls Statements RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @12.last_line, @12.last_column ); $$ = new CMethodDecl( $2, $3, 0, $7, $8, $10, location ); }
	| PUBLIC Type ID '(' ')' '{' Statements RETURN Exp ';' '}' { CLocation location( @1.first_line, @1.first_column, @11.last_line, @11.last_column ); $$ = new CMethodDecl( $2, $3, 0, 0, $7, $9, location ); }
	;
FormalList:
	Type ID { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CFormalList( 0, $1, $2, location ); }
	| Type ID FormalRest { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CFormalList( $3, $1, $2, location ); }
	;
FormalRest:
	',' Type ID { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CFormalList( 0, $2, $3, location ); }
	| FormalRest ',' Type ID { CLocation location( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CFormalList( $1, $3, $4, location ); }
	;
Type:
	INT { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CType( "int", location ); }
	| INT '[' ']' { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CType( "int[]", location ); }
	| BOOLEAN { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CType( "boolean", location ); }
	| ID { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CType( $1, location ); }
	;
Statements:
	Statement { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CStatementList( 0, $1, location ); }
	| Statements Statement { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CStatementList( $1, $2, location ); }
	;
Statement:
	ID '=' Exp ';' { CLocation location( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CAssignStatement( $1, 0, $3, location ); }
	| ID '[' Exp ']' '=' Exp ';' { CLocation location( @1.first_line, @1.first_column, @7.last_line, @7.last_column ); $$ = new CAssignStatement( $1, $3, $6, location ); }
	| SYSTEM_OUT_PRINTLN '(' Exp ')' ';' { CLocation location( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CPrintStatement( $3, location ); }
	| '{' '}' { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CCurlyBraceStatement( 0, location ); }
	| '{' Statements '}' { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CCurlyBraceStatement( $2, location ); }
	| IF '(' Exp ')' Statement ELSE Statement { CLocation location( @1.first_line, @1.first_column, @7.last_line, @7.last_column ); $$ = new CIfStatement( $3, $5, $7, location ); }
	| WHILE '(' Exp ')' Statement { CLocation location( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CWhileStatement( $3, $5, location ); }
	| error ';' { *hasError = 1; std::cout << "Syntax error : incorrect statement from " << @1.first_line << ":" << @1.first_column << " to " << @1.last_line << ":" << @1.last_column << std::endl; $$ = 0; }
	| SYSTEM_OUT_PRINTLN error ';' { *hasError = 1; std::cout << "Syntax error : incorrect Println-statement from " << @2.first_line << ":" << @2.first_column << " to " << @2.last_line << ":" << @2.last_column << std::endl; $$ = 0; }
	;

Exp:
	Exp '*' Exp { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpBinOpExp( $1, '*', $3, location ); }
	| Exp '+' Exp { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpBinOpExp( $1, '+', $3, location ); }
	| Exp '/' Exp { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpBinOpExp( $1, '/', $3, location ); }
	| Exp '-' Exp { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpBinOpExp( $1, '-', $3, location ); }
	| Exp '<' Exp { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpBinOpExp( $1, '<', $3, location ); }
	| Exp '&' Exp { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpBinOpExp( $1, '&', $3, location ); }
	| '-' Exp %prec UMINUS { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CUnMinExp( $2, location ); }
	| Exp '[' Exp ']' { CLocation location( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CExpWithIndex( $1, $3, location ); }
	| Exp '.' LENGTH { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpDotLength( $1, location ); }
	| Exp '.' ID '(' ExpList ')' { CLocation location( @1.first_line, @1.first_column, @6.last_line, @6.last_column ); $$ = new CExpIdExpList( $1, $3, $5, location ); }
	| Exp '.' ID '(' ')' { CLocation location( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CExpIdVoidExpList( $1, $3, location ) ; }
	| INTEGER_LITERAL { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CIntegerLiteral( $1, location ); }
	| TRUE { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CTrue( location ); }
	| FALSE { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CFalse( location ); }
	| ID { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CId( $1, location ); }
	| THIS { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CThis( location ); }
	| NEW INT '[' Exp ']' { CLocation location( @1.first_line, @1.first_column, @5.last_line, @5.last_column ); $$ = new CNewIntExpIndex( $4, location ); }
	| NEW ID '(' ')' { CLocation location( @1.first_line, @1.first_column, @4.last_line, @4.last_column ); $$ = new CNewId( $2, location ); }
	| '!' Exp { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CNotExp( $2, location ); }
	| '(' Exp ')' { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpInBrackets( $2, location ); }
	;
ExpList:
	Exp { CLocation location( @1.first_line, @1.first_column, @1.last_line, @1.last_column ); $$ = new CExpList( 0, $1, location ); }
	| Exp ExpRest { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CExpList( $2, $1, location ); }
	;
ExpRest:
	',' Exp { CLocation location( @1.first_line, @1.first_column, @2.last_line, @2.last_column ); $$ = new CExpList( 0, $2, location ); }
	| ExpRest ',' Exp { CLocation location( @1.first_line, @1.first_column, @3.last_line, @3.last_column ); $$ = new CExpList( $1, $3, location ); }
	;
	
%%

void yyerror( std::shared_ptr<CProgram>&, int*, const char* str )
{
	std::cout << str << std::endl;
}