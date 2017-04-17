%{
	#include <iostream>
	#include <list>
	using namespace std;
	
	list<string> operands;
	string operators;
	int stack = 0;
	bool valid = true;
%}
%%

"(" { stack++; }
")" { stack--; }
[a-zA-Z0-9]+ {operands.push_back(string(yytext));}
[+\-*/] {operators += string(yytext);}
[. \n] ;
%%

int main(int argc, char* argv[])
{
	yyin = fopen(argv[1],"r");
	yylex();

	if(valid && (operands.size()-operators.size())==1 && !stack)
		cout<<"Valid"<<endl;
	else
		cout<<"Invalid\n";
	return 0;
}
