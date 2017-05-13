#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
using namespace std;

ifstream code;
ofstream output;
unordered_map<string,string> Namtab,Argtab;
bool expanding = false;
string x0,x1,x2,a1,a2;

void define()
{
	ofstream deftab(x0);
	Namtab[x0];
	deftab << (x0+" "+x2) <<endl;
	code >> x0 >> x1 >> x2;
	while(x1 != "MEND")
	{
		if(x1 == "MACRO")
			define();
		if(x1 != "MEND")
			deftab << (x1+" "+x2) <<endl;
		code >> x0 >> x1 >> x2;	
	}
	deftab << "MEND"<< endl;
}


void expand()
{
	output << (". "+x1+" "+x2) <<endl;
	ifstream deftab(x1);
	deftab >> a1 >> a2;
	Argtab[a2] = x2;
	deftab >> a1 >> a2;
	while(a1 != "MEND")
	{
		if(Argtab.find(a2) != Argtab.end())
			a2 = Argtab[a2];
		output << ("- "+a1+" "+a2) <<endl;
		deftab >> a1 >> a2;
	}
}

void processLine()
{
	if(Namtab.find(x1) != Namtab.end())
		expand();
	else if (x1 == "MACRO")
		define();
	else
		output << (x0+" "+x1+" "+x2) << endl; 
}


int main()
{
	code.open("code.txt");
	output.open("output.txt");
	code >> x0 >> x1 >> x2;

	while(x1 != "END")
	{
		processLine();
		code >> x0 >> x1 >> x2;
	}

	return 0;
}