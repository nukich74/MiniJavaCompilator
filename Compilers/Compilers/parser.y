%{
#include <iostream>
extern "C" int yylex();
void yyerror( void**, int*, const char *);

%}

%code requires { #include <common.h> }

%parse-param {void** root}

%parse-param {int* hasError}

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
	MainClass { *root = new CProgram( $1, 0 ); }
	| MainClass ClassDecls { *root = new CProgram( $1, $2 ); }
	;
ClassDecls:
	ClassDecl { $$ = new CClassDeclList( 0, $1 ); }
	| ClassDecls ClassDecl { $$ = new CClassDeclList( $1, $2 ); }
	;
MainClass:
	CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements '}' '}' { $$ = new CMainClass( $2, $12, $15 ); }
	| CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRING '[' ']' ID ')' '{' Statements error '}' '}' { *hasError = 1; std::cout << "Syntax error : incorrect symbols in Main function from " << @16.first_line << ":" << @16.first_column << " to " << @16.last_line << ":" << @16.last_column << std::endl; }
ClassDecl:
	CLASS ID '{' '}' { $$ = new CClassDecl( $2, 0, 0, "" ); }
	| CLASS ID '{' VarDecls '}' { $$ = new CClassDecl( $2, $4, 0, "" ); }
	| CLASS ID '{' VarDecls MethodDecls '}' { $$ = new CClassDecl( $2, $4, $5, "" ); }
	| CLASS ID '{' MethodDecls '}' { $$ = new CClassDecl( $2, 0, $4, "" ); }
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
	| Type error ';' { *hasError = 1; std::cout << "Syntax error : incorrect variable definition from " << @2.first_line << ":" << @2.first_column << " to " << @2.last_line << ":" << @2.last_column << std::endl; }
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
	INT { $$ = new CType( "int" ); }
	| INT '[' ']' { $$ = new CType( "int[]" ); }
	| BOOLEAN { $$ = new CType( "boolean" ); }
	| ID { $$ = new CType( $1 ); }
	;
Statements:
	Statement { $$ = new CStatementList( 0, $1 ); }
	| Statements Statement { $$ = new CStatementList( $1, $2 ); }
	;
Statement:
	ID '=' Exp ';' { $$ = new CAssignStatement( $1, 0, $3 ); }
	| ID '[' Exp ']' '=' Exp ';' { $$ = new CAssignStatement( $1, $3, $6 ); }
	| SYSTEM_OUT_PRINTLN '(' Exp ')' ';' { $$ = new CPrintStatement( $3 ); }
	| '{' '}' { $$ = new CCurlyBraceStatement( 0 ); }
	| '{' Statements '}' { $$ = new CCurlyBraceStatement( $2 ); }
	| IF '(' Exp ')' Statement ELSE Statement { $$ = new CIfStatement( $3, $5, $7 ); }
	| WHILE '(' Exp ')' Statement { $$ = new CWhileStatement( $3, $5 ); }
	| error ';' { *hasError = 1; std::cout << "Syntax error : incorrect statement from " << @1.first_line << ":" << @1.first_column << " to " << @1.last_line << ":" << @1.last_column << std::endl; }
	| SYSTEM_OUT_PRINTLN error ';' { *hasError = 1; std::cout << "Syntax error : incorrect Println-statement from " << @2.first_line << ":" << @2.first_column << " to " << @2.last_line << ":" << @2.last_column << std::endl; }
	;

Exp:
	Exp '*' Exp { $$ = new CExpBinOpExp( $1, '*', $3 ); }
	| Exp '+' Exp { $$ = new CExpBinOpExp( $1, '+', $3 ); }
	| Exp '/' Exp { $$ = new CExpBinOpExp( $1, '/', $3 ); }
	| Exp '-' Exp { $$ = new CExpBinOpExp( $1, '-', $3 ); }
	| Exp '<' Exp { $$ = new CExpBinOpExp( $1, '<', $3 ); }
	| Exp '&' Exp { $$ = new CExpBinOpExp( $1, '&', $3 ); }
	| '-' Exp %prec UMINUS { $$ = new CUnMinExp( $2 ); }
	| Exp '[' Exp ']' { $$ = new CExpWithIndex( $1, $3 ); }
	| Exp '.' LENGTH { $$ = new CExpDotLength( $1 ); }
	| Exp '.' ID '(' ExpList ')' { $$ = new CExpIdExpList( $1, $3, $5 ); }
	| Exp '.' ID '(' ')' { $$ = new CExpIdVoidExpList( $1, $3 ) ; }
	| INTEGER_LITERAL { $$ = new CIntegerLiteral( $1 ); }
	| TRUE { $$ = new CTrue(); }
	| FALSE { $$ = new CFalse(); }
	| ID { $$ = new CId( $1 ); }
	| THIS { $$ = new CThis(); }
	| NEW INT '[' Exp ']' { $$ = new CNewIntExpIndex( $4 ); }
	| NEW ID '(' ')' { $$ = new CNewId( $2 ); }
	| '!' Exp { $$ = new CNotExp( $2 ); }
	| '(' Exp ')' { $$ = new CExpInBrackets( $2 ); }
	;
ExpList:
	Exp { $$ = new CExpList( 0, $1 ); }
	| Exp ExpRest { $$ = new CExpList( $2, $1 ); }
	;
ExpRest:
	',' Exp { $$ = new CExpList( 0, $2 ); }
	| ExpRest ',' Exp { $$ = new CExpList( $1, $3 ); }
	;
	
%%

void yyerror( void**, int*, const char* str )
{
	std::cout << str << std::endl;
}