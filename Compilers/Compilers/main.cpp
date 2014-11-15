extern "C" int yyparse();

int main() {
	while( yyparse() != 0 );
	return 0;
}