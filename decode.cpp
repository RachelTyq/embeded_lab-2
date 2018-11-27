#include <math.h>
#include <iostream>
#include <string>
using namespace std;
string inverted_seq(string a)
{
  string opstr="";
	for (int i = str.length()-1; i >= 0; i--)
	{
		opstr += str[i];
	}
  return opstr;
}
int bin_to_dec(){string str,int len}
{
	int output=0;
	for (int i = 0; i < len; i++)
	{
		if (str[i]=='1')
		output +=  pow(2, i);
	}
	return output;
}
void decode_ldrstr(string a){}
void decode_operate(string a)
{
  string opcode="";
	string rn = "";
	string rd = "";
	string op2 = "";

	for (int i = 0; i < 4;i++)
	{
		opcode += a[i + 21];
		rn += a[i + 16];
		rd += a[i + 12];
	}
	int rnintex = transcode(rn, 4);
	for (int i = 0; i < 12; i++)
	{
		op2 += a[i];
	}
	if (opcode == "0000")
		cout << "AND  ";
	if (opcode == "0010")
		cout << "ADD  ";
	if (opcode == "0101")
		cout << "CMP  ";
	if (opcode == "1011")
		cout << "MOV  ";
	if (opcode == "0011")
		cout << "ORR  ";
	cout << "R" << transcode(rd, 4) << ",";
	if (rnintex!=0)
	cout<<"R"<< rnintex << ",";
	if (a[25] == '1')
	{
		cout << "#" << transcode(op2, 12);
	}
	else
	{
		cout << "R" << transcode(op2, 12);
	}
}
void decode_mul(string a){}
void decode_mrs(string a){}
void decode_swi(string a){}
void decode_branche(string a){}
void classification(string line){}
void openfiles()
{
  ifstream in("arm.txt");
	string str;
	while (!in.eof())
	{
		getline(in, str);
		classification(str);
		cout << endl;
	}
	in.close();
}
int main()
{
  return 0;
}
