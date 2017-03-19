#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <unordered_map>
#include <iomanip>

using namespace std;

ostream &adj(ostream &out,int a)      //don't merge these overloads
{
  out  <<  setfill('0')  <<  setw(a)  << hex;
  return(out);
}
ostream &adj(ostream &out)
{
  out  <<  setfill('0')  <<  setw(6)  << hex;
  return(out);
}


int main() {

	unordered_map<string,int> Optab({{"LDA",0},{"STA",0x0C},{"JSUB",0x48}});
	unordered_map<string,int> Symtab({{"Beta",0x1009},{"Alpha",0x1006}});


	ifstream code("code.txt");
	string x0,x1,x2;
	int start_address=0;
	code >> x0 >> x1 >> x2;

	ofstream object("object.txt");

	if(x1 == "START")
	{
		start_address = stoi(x2,nullptr,16);
		object << "H^" + x0 + "  ^";
		object << adj << start_address << "^";
		object << adj << 0xc << endl;
		code >> x0 >> x1 >> x2;
	}

	int locctr = start_address;


	while(x1!="END")
  	{
		int t;

	 	if(x1 == "RESW")
	  		t = 3 * stoi(x2,nullptr,16);
	  	else if(x1 == "RESB")
	  		t = stoi(x2,nullptr,16);
	  	else if(x1 == "BYTE")
	  		t = x2.length()/2;
	  	else
	  		t = 3;

	  	if(!(x1=="RESW" || x1 == "RESB"))
	  	{
	 	 	object << "T^" << adj << locctr << "^";
	 	 	adj(object,2) << t << "^";

	 	 	if(x1 == "WORD")
	 	 		object << adj << x2 << endl;
	 	 	else if(x1 == "BYTE")
	 	 		object << x2 << endl;
	 	 	else
	 	 	{
	 	 		adj(object,2) << Optab[x1];
	 	 		adj(object,4) << Symtab[x2] << endl;
	 	 	}
	 	}

	locctr+=t;
	code >> x0 >> x1 >> x2;
	}


  return 0;
}
